// GPL

#include "TanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "TankPlayerController.h"
#include "TanksGameInstance.h"
#include "TankAIController.h"
#include <algorithm>    // std::min

//shortcut for setting timers
#define SET_TIMER(method,seconds) FTimerHandle handle; GetWorld()->GetTimerManager().SetTimer(handle, this, method, seconds, false)

//corresponds to selected index 0,1,2 on the join players screen
enum PlayerModes {
	Human, Computer, None
};

void ATanksGameMode::EndGame()
{
	//find the max score
	ATank* maxScoreTank = AllTanks[0];
	for (const auto& a : AllTanks) {
		if (a->points > maxScoreTank->points) {
			maxScoreTank = a;
		}
	}
	ClearViewport();
	DisplayHeaderText(FString(TEXT("Game Winner: <Noteworthy>")) + ActiveTanks[0]->GetName() + FString(TEXT("</>")));
	DisplayScores(GetScoreString());

	//also display the go back to the menu button
	SET_TIMER(&ATanksGameMode::Return, 3);
}

void ATanksGameMode::RoundComplete()
{
	SetActorTickEnabled(false);

	++round;

	//one winner?
	if (ActiveTanks.Num() == 1) {
		//show winner name
		ActiveTanks[0]->points++;
		DisplayHeaderText(FString(TEXT("Winner: <Noteworthy>")) + ActiveTanks[0]->GetName() + FString(TEXT("</>")));
	}
	//tie?
	else {
		//show winner name
		DisplayHeaderText(FString::Printf(TEXT("It's a tie!")));
	}
	
	//number of points reached?
	bool gameOver = false;
	for (const auto& a : AllTanks) {
		if (a->points >= pointsToWin) {
			gameOver = true;
			break;
		}
	}

	if (!gameOver) {
		SET_TIMER(&ATanksGameMode::SetupRound, 3);
	}
	else {
		SET_TIMER(&ATanksGameMode::EndGame, 3);
	}

	//disable the tanks
	for (const auto& a : AllTanks) {
		a->controlEnabled = false;
	}

	DisplayScores(GetScoreString());
}

void ATanksGameMode::SetupRound()
{
	ClearViewport();
	//reset all the tanks
	for (const auto& a : AllTanks) {
		a->SetupTank();
	}

	//move the tanks to the spawnpoints
	for (int i = 0; i < std::min(AllTanks.Num(),playerStarts.Num()); ++i) {
		AllTanks[i]->SetActorLocation(playerStarts[i]->GetActorLocation());
	}

	//display Round header
	DisplayHeaderText(FString::Printf(TEXT("<Emphasis>Round %d</>"),round));

	UpdateActiveTanks();

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


void ATanksGameMode::StartPlay()
{
	Super::StartPlay();

	//reset static counts for numbering
	ATankPlayerController::ResetStaticCount();
	ATankAIController::ResetStaticCount();

	//remove the first controller and its pawn - this will be managed later
	UGameplayStatics::RemovePlayer(GetWorld()->GetFirstPlayerController(),true);

	//get the game instance to know what players to spawn
	auto gameinstance = Cast<UTanksGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	//get points needed to win game
	pointsToWin = gameinstance->pointsToWin;

	//get all the player starts
	UGameplayStatics::GetAllActorsOfClass(Cast<UObject>(GetWorld()),APlayerStart::StaticClass(),playerStarts);

	int numPCs = 0;
	//For the max number of players, or until all of the playerStarts have been filled
	for (int i = 0; i < std::min(maxPlayerCount, playerStarts.Num()); ++i) {

		//if none, do not create a player or a AI
		//the first 2 comboboxes are set to not allow None to be set
		if (gameinstance->joinedPlayerStatus[i] != PlayerModes::None) {
			FActorSpawnParameters params;
			params.bNoFail = true;
			auto spawned = GetWorld()->SpawnActor<ATank>(APlayerActorClass, playerStarts[i]->GetActorTransform(), params);

			//set tank color
			spawned->SetColor(tankColors[i]);

			if (gameinstance->joinedPlayerStatus[i] == PlayerModes::Human) {
				++numPCs;
				//Attempt to create a player
				//the gamemode default pawn is set to None on purpose. This ensures
				//that the create player does not try to also create a pawn
				//which prevents player creation from failing
				UGameplayStatics::CreatePlayer(GetWorld())->Possess(spawned);
			}
			else {
				//spawn an AI controller and possess the tank with it
				auto ai = GetWorld()->SpawnActor<ATankAIController>(ATankAIController::StaticClass(), playerStarts[i]->GetActorTransform(), params);
				ai->Possess(spawned);
			}
		}
	}

	//if all AI battle, spawn one dummy player controller for the camera
	if (numPCs == 0) {
		UGameplayStatics::CreatePlayer(GetWorld());
	}

	{
		auto firstPlayer = GetWorld()->GetFirstPlayerController();
		if (firstPlayer != nullptr) {
			firstPlayer->bShowMouseCursor = false;
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
	UpdateActiveTanks();

	if (ActiveTanks.Num() <= 1) {
		RoundComplete();
	}
}

/**
 * Update the list of active tanks.
 */
void ATanksGameMode::UpdateActiveTanks() {
	ActiveTanks.Empty();
	for (auto t : AllTanks) {
		if (t->IsAlive) {
			ActiveTanks.Add(t);
		}
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

/**
Create a formatted score string to display in the viewport
*/
FString ATanksGameMode::GetScoreString()
{
	FString str("");
	for (const auto& t : AllTanks) {
		str += FString::Printf(TEXT("%s: %d\n"), *(t->GetName()), t->points);
	}
	return str;
}

/**
 * Return to the menu
 */
void ATanksGameMode::Return() {
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}