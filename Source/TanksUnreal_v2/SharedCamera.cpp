// GPL


#include "SharedCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASharedCamera::ASharedCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springarm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	springarm->SetupAttachment(RootComponent);
	springarm->bEnableCameraLag = true;
	springarm->bEnableCameraRotationLag = true;
	springarm->CameraLagSpeed = 1;

	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->SetupAttachment(springarm);
}

// Called when the game starts or when spawned
void ASharedCamera::BeginPlay()
{
	Super::BeginPlay();

	origZ = GetActorLocation().Z;

	gamemode = Cast<ATanksGameMode>((GetWorld()->GetAuthGameMode()));

	//set view targets for player controllers
	TArray<AActor*> playerControllers;
	UGameplayStatics::GetAllActorsOfClass(Cast<UObject>(GetWorld()), APlayerController::StaticClass(), playerControllers);
	for (auto a : playerControllers) {
		Cast<APlayerController>(a)->SetViewTargetWithBlend(this);
	}
}

// Called every frame
void ASharedCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//auto newPos = GetAverageLocation(gamemode->Players);

	//TODO: don't do this, instead use the gamemanager's list
	auto tanks = gamemode->GetActiveTanks();

	//set center
	auto newPos = GetAverageLocation(tanks);
	newPos.Z = origZ;

	//set zoom
	double dist = MaxDistance(tanks) * 1.5;
	dist = FMath::Clamp(dist,(double)minMaxDistance.X,(double)minMaxDistance.Y);
	springarm->TargetArmLength = dist;

	//newPos.X -= UKismetMathLibrary::MapRangeClamped(dist, minMaxDistance.X, minMaxDistance.Y, 0, 2000);
	SetActorLocation(newPos);


	// set angle
	SetActorRotation(FQuat::MakeFromEuler(FVector(0, UKismetMathLibrary::MapRangeClamped(dist,minMaxDistance.X,minMaxDistance.Y,-30,-80),0)));
}



/*Calculates the maximum distance to the camera given an array of tanks
* @param (std::vector<FVector>) &vectors: a vector of FVectors to calculate the maximum distance
* @return (double): the distance between the camera root and the furthest object
*/
double ASharedCamera::MaxDistance(TArray<ATank*>& vectors) {
	double maxDist = 0;
	for (auto v : vectors) {
		double dist = FVector::Dist(v->GetActorLocation(), GetActorLocation());
		if (dist > maxDist) {
			maxDist = dist;
		}	
	}
	return maxDist;
}

/* Calculates the average distance between the tanks
* @param (std::vector<FVector>) &vectors: a vector of FVectors to calculate the average distance
* @return (FVector): FVector representing the average x, y, and z coordinates of the FVectors
*/
FVector ASharedCamera::GetAverageLocation(TArray<ATank*>& vectors) {
	FVector average = FVector();
	for (auto a : vectors) {
		auto v = a->GetActorLocation();
		average.X += v.X;
		average.Y += v.Y;
		average.Z += v.Z;
	}
	average.X /= vectors.Num();
	average.Y /= vectors.Num();
	average.Z /= vectors.Num();
	return average;
}