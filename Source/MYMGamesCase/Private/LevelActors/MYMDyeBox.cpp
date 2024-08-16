#include "LevelActors/MYMDyeBox.h"

#include "Core/Characters/MYMPlayer.h"
#include "LevelActors/MYMCreatedObject.h"

AMYMDyeBox::AMYMDyeBox()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
}

void AMYMDyeBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMYMDyeBox::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!InstigatorPawn)
	{
		return;
	}

	const AMYMPlayer* Character = Cast<AMYMPlayer>(InstigatorPawn);

	if (!Character && !Character->CreatedObject && !Character->CreatedObject->DynamicMaterialInstance)
	{
		return;
	}
	
	Character->CreatedObject->DynamicMaterialInstance->SetVectorParameterValue("CreatedObjectColor", Color);

	UE_LOG(LogTemp, Warning, TEXT("Interacted with dye box!!!"))
}
