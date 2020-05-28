// GPL

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TanksGameMode.h"
#include "SharedCamera.generated.h"

UCLASS()
class TANKSUNREAL_V2_API ASharedCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASharedCamera();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D minMaxDistance = FVector2D(1000,6000);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* springarm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* camera;

	ATanksGameMode* gamemode;

	float origZ;

	double MaxDistance(TArray<AActor*>& vectors);

	FVector GetAverageLocation(TArray<AActor*>& vectors);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
