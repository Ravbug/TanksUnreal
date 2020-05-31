// GPL

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.h"
#include "TankPlayerController.generated.h"

/**
 * This class is automatically assigned as the playercontroller in BP_TanksGameMode blueprint
 */
UCLASS()
class TANKSUNREAL_V2_API ATankPlayerController : public APlayerController, public ITankController
{
	GENERATED_BODY()

public:
	ATankPlayerController();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FString GetName();
	virtual FString GetName_Implementation() override;

	static void ResetStaticCount() {
		staticPlayerNum = 0;
	}

protected:
	static uint8 staticPlayerNum;
	uint8 playerNum;
};
