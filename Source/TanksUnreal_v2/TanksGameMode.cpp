// GPL

#include "TanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include <algorithm>    // std::min

//shortcut for setting timers
#define SET_TIMER(method,seconds) FTimerHandle handle; GetWorld()->GetTimerManager().SetTimer(handle, this, method, seconds, false)

void ATanksGameMode::EndGame()
{

}

void ATanksGameMode::RoundComplete()
{
	SetActorTickEnabled(false);

	if (round < numRounds) {
		SET_TIMER(&ATanksGameMode::SetupRound, 3);
	}
	else {
		EndGame();
		return;
	}
	++round;

	//one winner?
	if (ActiveTanks.Num() == 1) {
		//show winner name
		ActiveTanks[0]->points++;
	}
	//tie?
	else {
		//show winner name
	}
	
	//disable the tanks
	for (const auto& a : AllTanks) {
		a->controlEnabled = false;
	}
}

void ATanksGameMode::SetupRound()
{
	//reset all the tanks
	for (const auto& a : AllTanks) {
		a->SetupTank();
	}

	//move the tanks to the spawnpoints
	for (int i = 0; i < std::min(AllTanks.Num(),playerStarts.Num()); ++i) {
		AllTanks[i]->SetActorLocation(playerStarts[i]->GetActorLocation());
	}

	//display Round header
	DisplayRoundStarting(FString::Printf(TEXT("<Emphasis>Round %d</>"),round));

	//timer to start beginround
	SET_TIMER(&ATanksGameMode::BeginRound, 3);
}

void ATanksGameMode::BeginRound() {
	//enable control on all the tanks
	for (const auto& a : AllTanks) {
		a->controlEnabled = true;
	}

	//hide round header
	ClearViewport();

	//start ticking
	SetActorTickEnabled(true);
}


void ATanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	//adapted from https://www.youtube.com/watch?v=3lN2eZIgAQ0 (local shared-screen multiplayer game in blueprint)

	//get all the player starts
	UGameplayStatics::GetAllActorsOfClass(Cast<UObject>(GetWorld()),APlayerStart::StaticClass(),playerStarts);

	//For the max number of players
	for (int i = 0; i < maxPlayerCount; ++i) {
		//locate the player start that can spawn this player (using PlayerStartTag, configurable in inspector)
		//spawn if this is a valid playerstart
		auto pstart = Cast<APlayerStart>(playerStarts[i]);
		if (pstart != nullptr) {

			//attempt to create a controller
			auto controller = UGameplayStatics::CreatePlayer(GetWorld());
			if (controller == nullptr) {
				continue;
			}

			//attempt to spawn the actor
			FActorSpawnParameters params;
			params.bNoFail = true;
			auto spawned = GetWorld()->SpawnActor<ATank>(APlayerActorClass,pstart->GetActorTransform(),params);
			if (spawned != nullptr) {
				controller->Possess(spawned);
			}
			else {
				UGameplayStatics::RemovePlayer(controller,false);
			}
		}
	}
	//load tanks into the array
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(Cast<UObject>(GetWorld()), ATank::StaticClass(), temp);

	//copy as tank into the alltanks array
	for (const auto& t : temp) {
		AllTanks.Add(Cast<ATank>(t));
	}

	SetupRound();
}

void ATanksGameMode::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	//update active tanks
	ActiveTanks.Empty();
	for (auto t : AllTanks) {
		if (t->IsAlive) {
			ActiveTanks.Add(t);
		}
	}

	if (ActiveTanks.Num() <= 1) {
		RoundComplete();
	}
}

/**
 * Get all the active tanks during this tick. A tank is active if it is alive.
 * @returns a TArray of the pointers to the active tanks
 */
const TArray<ATank*>& ATanksGameMode::GetActiveTanks()
{
	return ActiveTanks;
}