#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MYMWorldUserWidget.generated.h"

class UHorizontalBox;

UCLASS()
class MYMGAMESCASE_API UMYMWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(ExposeOnSpawn = "true"))
	AActor* AttachedActor;

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	FVector WorldOffset;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* ParentHorizontalBox;
};
