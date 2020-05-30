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

protected:

	TArray<ATank*> AllTanks;
	TArray<ATank*> ActiveTanks;
	TArray<AActor*> playerStarts;

	int numRounds = 3;
	int round = 1;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "UMG")
		TSubclassOf<UUserWidget> LevelStartingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "UMG")
		UUserWidget* RoundCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "UMG")
		UUserWidget* GameCompleteWidget;

	UFUNCTION(BlueprintImplementableEvent)
		void DisplayScores(const FString& str);

	UFUNCTION(BlueprintImplementableEvent)
		void DisplayHeaderText(const FString& str);

	UFUNCTION(BlueprintImplementableEvent)
		void ClearViewport();

private:
	void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadonly, meta = (AllowPrivateAccess = "true"), Category = "Levels")
		TArray<FString> Levels;
};
