#include "Components/MYMInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/MYMGameplayInterface.h"
#include "Widgets/MYMWorldUserWidget.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteractions(TEXT("rd.DebugDrawInteractions"),
                                                            false,
                                                            TEXT("Enable Debug Drawing For Interactions"),
                                                            ECVF_Cheat);

void UMYMInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::FindBestInteractableActor, CheckInteractableInterval, true);
}

void UMYMInteractionComponent::FindBestInteractableActor()
{
	const bool bIsDebugDrawingEnabled = CVarDebugDrawInteractions.GetValueOnGameThread();
	const AActor* Owner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	const FVector EndLocation = EyeLocation + EyeRotation.Vector() * EndDistance;

	TArray<FHitResult> HitResults;
	const bool bIsHit = PerformSweepTest(EyeLocation, EndLocation, HitResults);

	FocusedActor = FindFirstInteractableActor(HitResults);

	UpdateInteractionWidget();

	if (bIsDebugDrawingEnabled)
	{
		DrawDebugElements(EyeLocation, EndLocation, HitResults, bIsHit);
	}
}

bool UMYMInteractionComponent::PerformSweepTest(const FVector& Start, const FVector& End,
	TArray<FHitResult>& OutHitResults) const
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(ShapeRadius);

	return GetWorld()->SweepMultiByObjectType(OutHitResults, Start, End, FQuat::Identity, ObjectQueryParams, CollisionShape);
}

AActor* UMYMInteractionComponent::FindFirstInteractableActor(const TArray<FHitResult>& HitResults) const
{
	for (const FHitResult& HitResult : HitResults)
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor && HitActor->Implements<UMYMGameplayInterface>())
		{
			return HitActor;
		}
	}

	return nullptr;
}

void UMYMInteractionComponent::UpdateInteractionWidget()
{
	if (FocusedActor)
	{
		if (!InteractionWidget && ensure(InteractionWidgetClass))
		{
			InteractionWidget = CreateWidget<UMYMWorldUserWidget>(GetWorld(), InteractionWidgetClass);
		}

		if (InteractionWidget)
		{
			InteractionWidget->AttachedActor = FocusedActor;

			if (!InteractionWidget->IsInViewport())
			{
				InteractionWidget->AddToViewport();
			}
		}
	}

	else if (InteractionWidget)
	{
		InteractionWidget->RemoveFromParent();
	}
}

void UMYMInteractionComponent::DrawDebugElements(const FVector& Start, const FVector& End,
                                                 const TArray<FHitResult>& HitResults, bool bIsHit)
{
	const FColor DebugColor = bIsHit ? FColor::Green : FColor::Red;

	for (const FHitResult& HitResult : HitResults)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, ShapeRadius, 32, DebugColor, false, 2.f);
	}

	DrawDebugLine(GetWorld(), Start, End, DebugColor, false, 2.f, 0.f, 2.f);
}

void UMYMInteractionComponent::Interact()
{
	if (FocusedActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "There is no focus actor for interaction");

		return;
	}

	APawn* Pawn = Cast<APawn>(GetOwner());
	IMYMGameplayInterface::Execute_Interact(FocusedActor, Pawn);
}

