// GPL


#include "TankAIController.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "TanksGameMode.h"

#define SET_TIMER(method,seconds) FTimerHandle handle; GetWorld()->GetTimerManager().SetTimer(handle, this, method, seconds, false)

uint8 ATankAIController::staticPlayerNum = 0;

//constructor - set the number
ATankAIController::ATankAIController() {
	playerNum = ++staticPlayerNum;
}

//interface - get the player name
FString ATankAIController::GetName_Implementation() {
	return FString::Printf(TEXT("COM %d"), playerNum);
}

//track the pawn that this controller controls
void ATankAIController::OnPossess(APawn* other)
{
	pawn = Cast<ATank>(other);
}
void ATankAIController::OnUnPossess()
{
	pawn = nullptr;
}

/**
 Tick the decision making of this AI. Runs on a timer.
 */
void ATankAIController::AITick()
{
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
		auto distance = FVector::Distance(pawn->GetActorLocation(),t->GetActorLocation());
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
	FVector a = closest->GetActorLocation();
	FVector b = closest->GetActorLocation();
	//float angle = FMath::Acos((a - b) / (a.Size() * b.Size()));
}

void ATankAIController::Tick(float deltaTime) {
	//don't run if no pawn is attached
	if (pawn == nullptr) {
		return;
	}

	switch (state) {
	case State::Fleeing:
		//drive towards the chassis target pos
		break;
	case State::Fighting:
		//rotate to face the closest player
		break;
	}

	//if angled at another tank, shoot at it

	pawn->Move(0.2);
	//GLog->Log("AIcontroller");
}
