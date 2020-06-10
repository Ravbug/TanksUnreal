#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlatformFunctions.generated.h"

/**
 * Exposes some C++ platform functions to BluePrint
 * @author Mosel3y - https://forums.unrealengine.com/development-discussion/blueprint-visual-scripting/62093-can-i-get-the-gpu-and-cpu-name-in-bp
 */
UCLASS()
class TANKSUNREAL_V2_API UPlatformFunctions : public UBlueprintFunctionLibrary //add your project name
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get CPU Brand Name", Keywords = "CPU brand"), Category = Game) //Set your category
		static FString GetCPUBrandName();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get CPU Vendor Name", Keywords = "CPU vendor"), Category = Game)
		static FString GetCPUVendorName();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get GPU Brand Name", Keywords = "GPU brand"), Category = Game)
		static FString GetGPUBrandName();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Number of CPU Cores", Keywords = "CPU cores"), Category = Game)
		static int32 GetCPUCores();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get OS Version", Keywords = "OS version"), Category = Game)
		static FString GetOSVersion();
};