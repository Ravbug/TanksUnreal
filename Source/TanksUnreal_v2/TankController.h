// GPL

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TankController.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTankController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TANKSUNREAL_V2_API ITankController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * Get the name of this controller. Used when printing the name of the Tank.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FString GetName();
};
