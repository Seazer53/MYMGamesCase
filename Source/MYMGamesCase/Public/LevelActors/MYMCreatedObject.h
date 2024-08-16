#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/MYMGameplayInterface.h"
#include "MYMCreatedObject.generated.h"

UCLASS()
class MYMGAMESCASE_API AMYMCreatedObject : public AActor, public IMYMGameplayInterface
{
	GENERATED_BODY()
	
public:
	AMYMCreatedObject();

	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* DynamicMaterialInstance;

protected:
	virtual void PostInitializeComponents() override;
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(BlueprintReadOnly)
	bool bIsInteracted { false };
};
