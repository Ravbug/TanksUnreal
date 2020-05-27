// GPL

#pragma once

#include "CoreMinimal.h"
#include "TanksUnreal_v2GameModeBase.h"
#include "Blueprint/UserWidget.h"
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

	}
	void EndGame();
	void RoundComplete();

protected:


	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "UMG")
		TSubclassOf<UUserWidget> DefaultLevelCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "UMG")
		UUserWidget* RoundCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "UMG")
		UUserWidget* GameCompleteWidget;

private:
	void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadonly, meta = (AllowPrivateAccess = "true"), Category = "Levels")
		TArray<FString> Levels;
};
