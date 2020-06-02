// GPL


#include "TankAIController.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystemTypes.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "TanksGameMode.h"

#define SET_TIMER(method,seconds) GetWorld()->GetTimerManager().SetTimer(handle, this, method, seconds, false)

uint8 ATankAIController::staticPlayerNum = 0;

//constructor - set the number
ATankAIController::ATankAIController() {
	playerNum = ++staticPlayerNum;
	PrimaryActorTick.bCanEverTick = true;
}

//interface - get the player name
FString ATankAIController::GetName_Implementation() {
	return FString::Printf(TEXT("COM %d"), playerNum);
}

//track the pawn that this controller controls
void ATankAIController::OnPossess(APawn* other)
{
	tank = Cast<ATank>(other);
	AITick();
}
void ATankAIController::OnUnPossess()
{
	tank = nullptr;

	//cancel the timer
	handle.Invalidate();
}

/**
 * Calculate the angle between two FVectors in 2D space (X and Y)
 * @param a First vector
 * @param b Second vector
 * @returns the angle between a and b
 */
float ATankAIController::AngleBetweenDirections(FVector& a, FVector& b)
{
	a.Normalize();
	b.Normalize();

	return FMath::Acos(FVector::DotProduct(a,b));
}

void ATankAIController::RotateToFacePos(const FVector& b)
{
	FVector a = tank->GetActorLocation();
	FVector dir = a - b;
	FVector tdir = tank->GetActorForwardVector();

	auto angle = AngleBetweenDirections(tdir, dir) - PI / 2;

	//turn in the appropriate direction
	//TODO: change the amount based on the angle
	if (angle > 0) {
		tank->Turn(-1);
	}
	else {
		tank->Turn(1);
	}
}

/**
 Tick the decision making of this AI. Runs on a timer.
 */
void ATankAIController::AITick()
{
	GLog->Logf(TEXT("%s"), AController::GetPawn());

	//choose a new place to drive
	chassisTargetPos = FVector(FMath::RandRange(-4000,4000), FMath::RandRange(-4000, 4000),0);

	//invert state
	state = state == State::Fleeing ? State::Fighting : State::Fleeing;

	SET_TIMER(&ATankAIController::AITick, FMath::RandRange(5,10));
}

/**
 * Find the closest tank on the board
 * @returns a pointer to the tank closest to this tank
 */
ATank* ATankAIController::GetClosestTank()
{
	auto gamemode = Cast<ATanksGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ATank* closest = nullptr;
	float closestDist = 10000;
	for (const auto& t : gamemode->GetActiveTanks()) {
		if (t == tank) {
			continue;
		}
		auto distance = FVector::Distance(tank->GetActorLocation(),t->GetActorLocation());
		if (distance < closestDist) {
			closest = t;
		}
	}

	return closest;
}

/**
 * Angles the tank to face the closest tank on the board
 */
void ATankAIController::DefenseTick()
{
	auto closest = GetClosestTank();
	if (closest == nullptr) {
		return;
	}
	
	//figure out what side of the pawn the target is on
	RotateToFacePos(closest->GetActorLocation());
}

void ATankAIController::DriveTick()
{
	// configure navigation request
	auto navsys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	auto navdata = navsys->GetNavDataForProps(GetNavAgentPropertiesRef());
	FPathFindingQuery query(this,*navdata,tank->GetActorLocation(),chassisTargetPos);

	//perform navigation calculation
	auto result = navsys->FindPathSync(query, EPathFindingMode::Regular);

	//if failed, go into fighting mode
	if (result.Result != ENavigationQueryResult::Success) {
		state = State::Fighting;
		return;
	}

	auto path = result.Path->GetPathPoints();
	if (path.Num() > 1) {
		//drive towards path[1]
		RotateToFacePos(path[1]);
		tank->Move(0.2);
	}

	for (int i = 0; i < path.Num() - 1; i++) {
		DrawDebugLine(GetWorld(), path[i], path[i + 1], FColor::Green, 0.0f, 0.0f, 5);
	}
}

void ATankAIController::Tick(float deltaTime) {

	//don't run if no pawn is attached
	if (tank == nullptr) {
		return;
	}

	switch (state) {
	case State::Fleeing:
		//drive towards the chassis target pos
		DriveTick();
		break;
	case State::Fighting:
		DefenseTick();
		break;
	}

	//if angled at another tank, shoot at it
}
