#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MYMInteractionComponent.generated.h"


class UMYMWorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYMGAMESCASE_API UMYMInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void Interact();

protected:
	virtual void BeginPlay() override;

	void FindBestInteractableActor();

	bool PerformSweepTest(const FVector& Start, const FVector& End, TArray<FHitResult>& OutHitResults) const;

	AActor* FindFirstInteractableActor(const TArray<FHitResult>& HitResults) const;

	void UpdateInteractionWidget();

	void DrawDebugElements(const FVector& Start, const FVector& End, const TArray<FHitResult>& HitResults, bool bIsHit);

	UPROPERTY(EditDefaultsOnly)
	uint16 EndDistance {750};

	UPROPERTY(EditDefaultsOnly)
	float ShapeRadius {30.f};

	UPROPERTY(EditDefaultsOnly)
	float CheckInteractableInterval {.5f};

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> CollisionChannel {ECC_WorldDynamic};

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMYMWorldUserWidget> InteractionWidgetClass;

	UPROPERTY()
	UMYMWorldUserWidget* InteractionWidget;

	UPROPERTY()
	AActor* FocusedActor;
};
