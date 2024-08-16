#include "Core/Frameworks/MYMGameStateBase.h"

#include "LevelActors/MYMCreatedObject.h"
#include "Net/UnrealNetwork.h"

void AMYMGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMYMGameStateBase, Money);
}

void AMYMGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::AddNewOrder, NewOrderInterval, true);
}

void AMYMGameStateBase::CheckOrder(AMYMCreatedObject* CreatedObject)
{
	if (CreatedObject)
	{
		CreatedObject->DynamicMaterialInstance->GetLinearColorParameterValue(MaterialParameterInfo, CreatedObjectColor);

		if (CurrentOrderColor.Equals(CreatedObjectColor))
		{
			bIsColorCorrect = true;
			
			if (CreatedObject->GetFName().IsEqual(OrderList[0], ENameCase::IgnoreCase))
			{
				bIsObjectCorrect = true;
			}
		}
	}

	OnMoneyUpdate();
	CreatedObject->SetLifeSpan(2.f);
}

void AMYMGameStateBase::AddNewOrder()
{
	if (OrderList.Num() < 10)
	{
		FString Order = ShapeList[FMath::RandRange(0, 2)];
		CurrentOrderColor = ColorList[FMath::RandRange(0, 2)];
		
		OrderList.Add(FName(Order));

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("New Order Added: ") + Order);
	}
}

void AMYMGameStateBase::OnRep_Money()
{
	OnMoneyUpdate();
}

float AMYMGameStateBase::OnMoneyUpdate()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		if (bIsObjectCorrect && !bIsColorCorrect)
		{
			Money += CorrectOrderReward / 2;
		}

		else if (bIsObjectCorrect && bIsColorCorrect)
		{
			Money += CorrectOrderReward;
		}

		bIsColorCorrect = false;
		bIsObjectCorrect = false;
	}

	return Money;
}
