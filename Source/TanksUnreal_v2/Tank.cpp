// GPL


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	const int boxextent = 80;

	CollisionRoot = CreateDefaultSubobject<UBoxComponent>("Root");
	RootComponent = CollisionRoot;
	CollisionRoot->SetBoxExtent(FVector(boxextent, boxextent, boxextent));
	CollisionRoot->SetRelativeLocation(FVector(0,0, boxextent/2.0));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	//enable physics
	CollisionRoot->SetSimulatePhysics(true);
	CollisionRoot->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionRoot->SetEnableGravity(true);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	deltaTime = DeltaTime;
	Super::Tick(DeltaTime);

	velocity -= velocity * 0.05 * deltaTime / evalNormal;
	//move the tank forward based on velocity
	FVector v = GetActorForwardVector().RotateAngleAxis(90, FVector::UpVector);
	v *= velocity;
	SetActorLocation(GetActorLocation() + v);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move",this,&ATank::Move);
	PlayerInputComponent->BindAxis("Turn",this,&ATank::Turn);
}

void ATank::Move(float amount)
{
	if (controlEnabled) {
		if (abs(velocity) < maxSpeed * deltaTime / evalNormal) {
			velocity += amount * deltaTime / evalNormal;
		}
	}
}

void ATank::Turn(float amount)
{
	if (controlEnabled) {
		//scale for deltaTime
		amount *= deltaTime / evalNormal;
		SetActorRotation(GetActorRotation().Add(0, amount, 0));
	}
}

