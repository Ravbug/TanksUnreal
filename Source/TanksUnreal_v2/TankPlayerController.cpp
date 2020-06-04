// GPL


#include "TankPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TanksGameMode.h"

uint8 ATankPlayerController::staticPlayerNum = 0;

ATankPlayerController::ATankPlayerController() {
	//assign number
	playerNum = ++staticPlayerNum;
}

FString ATankPlayerController::GetName_Implementation()
{
	return FString::Printf(TEXT("Player %d"), playerNum);
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAction("PauseGame", IE_Released,this, &ATankPlayerController::OnPause);

	InputComponent->BindAxis("Move", this, &ATankPlayerController::Move);
	InputComponent->BindAxis("Turn", this, &ATankPlayerController::Turn);
	InputComponent->BindAxis("ChargeShot", this, &ATankPlayerController::ChargeShot);
	InputComponent->BindAction("Fire", IE_Released, this, &ATankPlayerController::Fire);
	InputComponent->BindAction("TouchActivate", IE_Pressed, this, &ATankPlayerController::OnTouch);
}

//call the gamemode to pause the game
void ATankPlayerController::OnPause()
{
	auto gamemode = Cast<ATanksGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gamemode) {
		gamemode->PauseGame();
	}
}

// Draw the touch widget on screen
void ATankPlayerController::OnTouch()
{
	if (!touchActivated) {
		touchActivated = true;

		//add the touch UI to the viewport
		ShowTouchControls();
	}
}

void ATankPlayerController::OnPossess(APawn* other)
{
	Super::OnPossess(other);
	tank = Cast<ATank>(other);
}

void ATankPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	tank = nullptr;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Move(float amount)
{
	if (tank) {
		tank->Move(amount);
	}
}

void ATankPlayerController::Turn(float amount)
{
	if (tank) {
		tank->Turn(amount);
	}
}

void ATankPlayerController::ChargeShot(float speed)
{
	if (tank) {
		tank->ChargeShot(speed);
	}
}

void ATankPlayerController::Fire()
{
	if (tank) {
		tank->Fire();
	}
}

