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
	//get all the player starts
	TArray<AActor*> playerStarts;
	UGameplayStatics::GetAllActorsOfClass(Cast<UObject>(GetWorld()),APlayerStart::StaticClass(),playerStarts);
}