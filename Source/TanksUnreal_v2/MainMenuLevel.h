// GPL

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Camera/CameraActor.h"
#include "MainMenuLevel.generated.h"

/**
 * This class is the "level blueprint" for the Main Menu.
 * This is set in [main toolbar]->Blueprints->Open Level Blueprint->Class Settings->Parent Class
 */
UCLASS()
class TANKSUNREAL_V2_API AMainMenuLevel : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
};
