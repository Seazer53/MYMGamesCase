#include "LevelActors/MYMCreatedObject.h"

#include "Core/Characters/MYMPlayer.h"

AMYMCreatedObject::AMYMCreatedObject()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
}

void AMYMCreatedObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	DynamicMaterialInstance = BaseMesh->CreateDynamicMaterialInstance(0);
}

void AMYMCreatedObject::Interact_Implementation(APawn* InstigatorPawn)
{
	bIsInteracted = !bIsInteracted;

	const AMYMPlayer* Character = Cast<AMYMPlayer>(InstigatorPawn);

	if (!Character && !Character->CreatedObject)
	{
		return;
	}

	if (Character->CreatedObject == nullptr)
	{
		Character->CreatedObject = this;
	}

	const FVector& InteractLocation = Character->GetMesh()->GetSocketLocation("WhipAimRotation");
	
	if (bIsInteracted)
	{
		SetInstigator(InstigatorPawn);

		if (ensure(BaseMesh))
		{
			BaseMesh->SetSimulatePhysics(false);	
		}
		
		AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WhipAimRotation");
		SetActorLocation(InteractLocation);
	}

	else
	{
		SetInstigator(nullptr);
		BaseMesh->SetSimulatePhysics(true);
		DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	}
}
