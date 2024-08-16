#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "MYMPlayer.generated.h"

class AMYMCreatedObject;
class UMYMInteractionComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MYMGAMESCASE_API AMYMPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AMYMPlayer();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	mutable AMYMCreatedObject* CreatedObject;

protected:
	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void Move(const FInputActionInstance& Instance);

	UFUNCTION()
	void LookMouse(const FInputActionInstance& Value);

	UFUNCTION()
	void Interact();
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UMYMInteractionComponent* InteractionComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Input_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Input_LookMouse;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Input_Interact;
};
