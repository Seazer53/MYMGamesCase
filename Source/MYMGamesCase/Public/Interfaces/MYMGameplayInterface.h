#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MYMGameplayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMYMGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

class MYMGAMESCASE_API IMYMGameplayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(APawn* InstigatorPawn);
};
