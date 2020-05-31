// GPL

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TanksGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TANKSUNREAL_V2_API UTanksGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int> joinedPlayerStatus;
};
