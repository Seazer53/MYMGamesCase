#include "LevelActors/MYMOrderDelivery.h"

#include "Core/Frameworks/MYMGameStateBase.h"
#include "LevelActors/MYMCreatedObject.h"

AMYMOrderDelivery::AMYMOrderDelivery()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	BaseMesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::Delivery);
}

void AMYMOrderDelivery::Delivery(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	AMYMCreatedObject* DeliveredObject = Cast<AMYMCreatedObject>(OtherActor);

	if (DeliveredObject)
	{
		AMYMGameStateBase* GameState = Cast<AMYMGameStateBase>(DeliveredObject->GetInstigator()->GetWorld()->GetGameState());

		if (GameState)
		{
			GameState->CheckOrder(DeliveredObject);
		}
	}
}


