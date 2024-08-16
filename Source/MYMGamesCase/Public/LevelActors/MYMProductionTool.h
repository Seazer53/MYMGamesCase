#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/MYMGameplayInterface.h"
#include "MYMProductionTool.generated.h"

class UMYMWorldUserWidget;
class UWidgetComponent;

UCLASS()
class MYMGAMESCASE_API AMYMProductionTool : public AActor, public IMYMGameplayInterface
{
	GENERATED_BODY()
	
public:	
	AMYMProductionTool();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMYMWorldUserWidget> InteractionWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	UMYMWorldUserWidget* InteractionWidget;
};
