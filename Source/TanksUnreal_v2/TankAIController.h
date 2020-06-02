// GPL

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankController.h"
#include "Tank.h"
#include "Misc/DateTime.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKSUNREAL_V2_API ATankAIController : public AAIController, public ITankController
{
	GENERATED_BODY()

public:
	ATankAIController();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		FString GetName();
	virtual FString GetName_Implementation() override;

protected:
	ATank* tank = nullptr;

	void OnPossess(APawn* other) override;
	void OnUnPossess() override;

	float AngleBetweenDirections(FVector& A, FVector& B);
	bool RotateToFacePos(const FVector& pos);

	enum State {
		Fleeing, Fighting
	};

	State state = State::Fighting;
	bool pursueInDriving = false;
	FVector chassisTargetPos = FVector(0, 0, 0);
	float LastShotTime = 0;
	float minShotDelay = 0.75;	

	FVector2D distanceToPower = FVector2D(200,6000);

	void AITick();
	ATank* GetClosestTank();

	void Fire(const FVector& pos);

private:
	void Tick(float deltaTime) override;

	void DefenseTick();
	void DriveTick();

	FTimerHandle handle;

	static uint8 staticPlayerNum;
	uint8 playerNum;
};
