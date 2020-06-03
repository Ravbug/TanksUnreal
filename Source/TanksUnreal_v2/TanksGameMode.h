// GPL

#pragma once

#include "CoreMinimal.h"
#include "TanksUnreal_v2GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Tank.h"
#include "Delegates/DelegateInstancesImpl.h"
#include "TanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TANKSUNREAL_V2_API ATanksGameMode : public ATanksUnreal_v2GameModeBase
{
	GENERATED_BODY()
	
public:
	ATanksGameMode() {
		PrimaryActorTick.bCanEverTick = true;
	}
	void EndGame();
	void RoundComplete();
	void SetupRound();
	void BeginRound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxPlayerCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATank> APlayerActorClass;


	void Tick(float deltaTime) override;

	const TArray<ATank*>& GetActiveTanks();

	FString GetScoreString();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int numRounds = 3;

	UFUNCTION(BlueprintImplementableEvent)
		void PauseGame();

protected:

	TArray<ATank*> AllTanks;
	TArray<ATank*> ActiveTanks;
	TArray<AActor*> playerStarts;

	//the current round
	int round = 1;

	int pointsToWin = 3;

	void UpdateActiveTanks();

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "UMG")
		TSubclassOf<UUserWidget> LevelStartingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "UMG")
		TSubclassOf<UUserWidget> RoundCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "UMG")
		TSubclassOf<UUserWidget> GameCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "UMG")
		TSubclassOf<UUserWidget> PauseGameWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Colors")
		TArray<FColor> tankColors;

	UFUNCTION(BlueprintImplementableEvent)
		void DisplayScores(const FString& str);

	UFUNCTION(BlueprintImplementableEvent)
		void DisplayHeaderText(const FString& str);

	UFUNCTION(BlueprintImplementableEvent)
		void ClearViewport();

	void Return();

private:
	void StartPlay() override;
};
