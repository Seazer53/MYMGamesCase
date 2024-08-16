#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MYMOrderDelivery.generated.h"

UCLASS()
class MYMGAMESCASE_API AMYMOrderDelivery : public AActor
{
	GENERATED_BODY()
	
public:	
	AMYMOrderDelivery();

protected:
	UFUNCTION()
	void Delivery(UPrimitiveComponent* OverlappedComponent,
				  AActor* OtherActor,
				  UPrimitiveComponent* OtherComp,
				  int32 OtherBodyIndex,
				  bool bFromSweep,
				  const FHitResult & SweepResult);
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
};
