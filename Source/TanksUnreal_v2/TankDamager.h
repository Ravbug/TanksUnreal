// GPL

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankDamager.generated.h"

UCLASS()
class TANKSUNREAL_V2_API ATankDamager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankDamager();

	//these can be overridden in subclasses or in blueprints
	UPROPERTY(BlueprintReadWrite)
		float damageMultiplier = 1.0;

	UPROPERTY(BlueprintReadWrite)
		float knockbackStrength = 1000;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
