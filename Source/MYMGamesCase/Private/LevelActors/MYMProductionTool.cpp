#include "LevelActors/MYMProductionTool.h"

#include "Widgets/MYMWorldUserWidget.h"

AMYMProductionTool::AMYMProductionTool()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
}

void AMYMProductionTool::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!InteractionWidget && ensure(InteractionWidgetClass))
	{
		InteractionWidget = CreateWidget<UMYMWorldUserWidget>(GetWorld(), InteractionWidgetClass);
	}

	if (InteractionWidget)
	{
		InteractionWidget->AttachedActor = this;
		InteractionWidget->SetOwningPlayer(Cast<APlayerController>(InstigatorPawn));

		if (!InteractionWidget->IsInViewport())
		{
			InteractionWidget->AddToViewport();
		}
	}
}
