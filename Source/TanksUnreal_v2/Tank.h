// GPL

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/WidgetComponent.h"
#include "TankDamager.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/UObjectBaseUtility.h"
#include "Tank.generated.h"

UCLASS()
class TANKSUNREAL_V2_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	bool controlEnabled = false;
	bool IsAlive = true;

	int points = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* BulletSpawnpoint;

	UPROPERTY(BlueprintReadWrite)
		FVector2D minMaxBulletSpeed = FVector2D(200,4000);

	void SetupTank();

protected:
	float velocity;
	bool isMoving = false;

	UPROPERTY(BlueprintReadWrite)
	int maxSpeed = 6;

	float deltaTime = 0;					//deltatime stored from Tick()
	const float evalNormal = 1.0 / 120;     //1 / the "normal" tick speed. Values in this game assume 120hz is the normal tick speed. To scale, multiply the value by deltaTime/evalNormal

	float currentPercent = 0;
	float chargeRate = 0.01;

	//this is % of health
	float currentHealth = 1;
	UPROPERTY()
		FVector2D damageDistMinMax = FVector2D(0,300);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void SetNameInHUD(const FString& str);

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

	FString GetName();
	void UpdateName() {
		SetNameInHUD(GetName());
	}

	//gameplay methods
	void Move(float amount);
	void Turn(float amount);
	void ChargeShot(float speed);
	void Fire();
	void Die();
	void SetColor(const FColor& color);


	//for blueprint
	UFUNCTION(BlueprintImplementableEvent)
		void SetChargeBar(float amount);

	UFUNCTION(BlueprintImplementableEvent)
		void SetHealthBar(float amount);

	UFUNCTION(BlueprintImplementableEvent)
		void SapwnBullet(float amount);

	UFUNCTION(BlueprintCallable)
		void Damage(ATankDamager* damagingActor);

	UFUNCTION(BlueprintImplementableEvent)
		void DieEffect();

	UFUNCTION(BlueprintImplementableEvent)
		void MovingAction();

	UFUNCTION(BlueprintImplementableEvent)
		void StopMovingAction();

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
};
