// GPL

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/WidgetComponent.h"
#include "Tank.generated.h"

UCLASS()
class TANKSUNREAL_V2_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	bool controlEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATank> BulletClass;

protected:
	float velocity;
	int maxSpeed = 10;

	float deltaTime = 0;					//deltatime stored from Tick()
	const float evalNormal = 1.0 / 120;     //1 / the "normal" tick speed. Values in this game assume 120hz is the normal tick speed. To scale, multiply the value by deltaTime/evalNormal

	float currentPercent = 0;
	float chargeRate = 0.01;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UBoxComponent* CollisionRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UWidgetComponent* ChargeShotBar;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UWidgetComponent* HealthInfoHUD;

	//gameplay methods
	void Move(float amount);
	void Turn(float amount);
	void ChargeShot(float speed);
	void Fire();

	//for blueprint
	UFUNCTION(BlueprintImplementableEvent)
		void SetChargeBar(float amount);
};
