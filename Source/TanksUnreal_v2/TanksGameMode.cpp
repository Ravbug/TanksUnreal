// GPL

#include "TanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

void ATanksGameMode::EndGame()
{
}

void ATanksGameMode::RoundComplete()
{
}


void ATanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	//adapted from https://www.youtube.com/watch?v=3lN2eZIgAQ0 (local shared-screen multiplayer game in blueprint)

	//get all the player starts
	TArray<AActor*> playerStarts;
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
}

void ATanksGameMode::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

/**
 * Get all the active tanks during this tick. A tank is active if it is alive.
 * @returns a TArray of the pointers to the active tanks
 */
TArray<ATank*> ATanksGameMode::GetActiveTanks()
{
	TArray<ATank*> temp;
	for (auto t : AllTanks) {
		if (t->IsAlive) {
			temp.Add(t);
		}
	}
	return temp;
}