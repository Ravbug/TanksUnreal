// GPL


#include "TanksGameInstance.h"

UTanksGameInstance::UTanksGameInstance() {
	//creates 4 human players if the game map is loaded directly
	joinedPlayerStatus.SetNum(4);
}