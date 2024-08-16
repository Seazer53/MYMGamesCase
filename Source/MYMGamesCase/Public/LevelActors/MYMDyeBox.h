#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/MYMGameplayInterface.h"

#include "MYMDyeBox.generated.h"

class AMYMCreatedObject;

UCLASS()
class MYMGAMESCASE_API AMYMDyeBox : public AActor, public IMYMGameplayInterface
{
	GENERATED_BODY()
	
public:	
	AMYMDyeBox();

protected:
	virtual void PostInitializeComponents() override;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category = "Color")
	FLinearColor Color;
};
