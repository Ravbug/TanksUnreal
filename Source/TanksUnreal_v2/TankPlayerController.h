// GPL

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.h"
#include "Tank.h"
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

	//called to bind functionality to input
	virtual void SetupInputComponent() override;

	void OnPause();

	void OnPossess(APawn* other) override;
	void OnUnPossess() override;

	//control methods
	void Move(float amount);
	void Turn(float amount);
	void ChargeShot(float speed);
	void Fire();

protected:
	ATank* tank;

private:
	static uint8 staticPlayerNum;
	uint8 playerNum;
};
