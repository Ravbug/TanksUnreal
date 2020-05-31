// GPL


#include "MainMenuLevel.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuLevel::BeginPlay() {
	// For this task (assigning the camera to one in the scene),
	// it is probably more efficient to use the level blueprint directly.

	//get the camera actor
	auto camera = UGameplayStatics::GetActorOfClass(Cast<UObject>(GetWorld()),ACameraActor::StaticClass());

	//set the first player controller's camera to the camera
	GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(camera);
}