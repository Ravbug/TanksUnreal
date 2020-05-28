// GPL


#include "Tank.h"
#include "Kismet/KismetMathLibrary.h"

#define FPSSCALE deltaTime / evalNormal

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

	ChargeShotBar = CreateDefaultSubobject<UWidgetComponent>("ChargeShot");
	ChargeShotBar->SetupAttachment(CollisionRoot);
	ChargeShotBar->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0,90,180)));
	ChargeShotBar->SetRelativeLocation(FVector(0,100,-60));

	//heath HUD will always face the camera
	HealthInfoHUD = CreateDefaultSubobject<UWidgetComponent>("Info HUD");
	HealthInfoHUD->SetupAttachment(CollisionRoot);
	HealthInfoHUD->SetWidgetSpace(EWidgetSpace::Screen);
	HealthInfoHUD->SetRelativeLocation(FVector(0,0,100));

	BulletSpawnpoint = CreateDefaultSubobject<UChildActorComponent>("Bullet Spawnpoint");
	BulletSpawnpoint->SetupAttachment(CollisionRoot);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	//hide shot bar
	ChargeShotBar->SetVisibility(false);

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
	PlayerInputComponent->BindAxis("ChargeShot", this, &ATank::ChargeShot);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATank::Fire);
}

void ATank::Move(float amount)
{
	if (controlEnabled) {
		if (abs(velocity) < maxSpeed * FPSSCALE) {
			velocity += amount * FPSSCALE;
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

void ATank::ChargeShot(float speed)
{
	if (speed > 0.1) {
		ChargeShotBar->SetVisibility(true);
		currentPercent += speed * chargeRate * FPSSCALE;
		//update progress bar
		if (currentPercent >= 1) {
			Fire();
		}
		SetChargeBar(currentPercent);
	}
}

void ATank::Fire()
{
	SapwnBullet(UKismetMathLibrary::MapRangeClamped(currentPercent,0,1,minMaxBulletSpeed.X,minMaxBulletSpeed.Y));

	//reset charge bar
	SetChargeBar(currentPercent = 0);
	ChargeShotBar->SetVisibility(false);
}
