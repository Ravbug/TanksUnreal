// GPL


#include "TankPlayerController.h"

uint8 ATankPlayerController::staticPlayerNum = 0;

ATankPlayerController::ATankPlayerController() {
	//assign number
	playerNum = ++staticPlayerNum;
}

FString ATankPlayerController::GetName_Implementation()
{
	return FString::Printf(TEXT("Player %d"), playerNum);
}
