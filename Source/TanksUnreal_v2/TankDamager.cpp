// GPL


#include "TankDamager.h"

// Sets default values
ATankDamager::ATankDamager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATankDamager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankDamager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

