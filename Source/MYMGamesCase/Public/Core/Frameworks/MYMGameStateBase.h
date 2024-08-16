#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LevelActors/MYMCreatedObject.h"
#include "MYMGameStateBase.generated.h"

class UMYMWorldUserWidget;
class AMYMCreatedObject;

UCLASS()
class MYMGAMESCASE_API AMYMGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	void CheckOrder(AMYMCreatedObject* CreatedObject);

	UFUNCTION(BlueprintCallable)
	float OnMoneyUpdate();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void AddNewOrder();
	
	UFUNCTION()
	void OnRep_Money();
	
	UPROPERTY(ReplicatedUsing="OnRep_Money", BlueprintReadWrite, Category = "Money")
	float Money {100.f};

	UPROPERTY(EditDefaultsOnly, Category = "Money")
	float CorrectOrderReward { 100.f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FName> OrderList;

	UPROPERTY()
	FLinearColor CurrentOrderColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FString> ShapeList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FLinearColor> ColorList;

	UPROPERTY(EditDefaultsOnly)
	float NewOrderInterval { 30.0f };

	UPROPERTY()
	FLinearColor CreatedObjectColor;
	
	FHashedMaterialParameterInfo MaterialParameterInfo { "CreatedObjectColor" };

	UPROPERTY(BlueprintReadOnly)
	bool bIsObjectCorrect;

	UPROPERTY(BlueprintReadOnly)
	bool bIsColorCorrect;
};
