#include "MYMGamesCase/Public/Core/Characters/MYMPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/MYMInteractionComponent.h"

AMYMPlayer::AMYMPlayer()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractionComponent = CreateDefaultSubobject<UMYMInteractionComponent>("InteractionComponent");

	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

void AMYMPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMYMPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = GetController<APlayerController>();
	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	if (!LocalPlayerSubsystem)
	{
		return;
	}

	LocalPlayerSubsystem->ClearAllMappings();

	LocalPlayerSubsystem->AddMappingContext(InputMappingContext, 0);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(Input_LookMouse, ETriggerEvent::Triggered, this, &ThisClass::LookMouse);
	EnhancedInputComponent->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ThisClass::Interact);
}

void AMYMPlayer::Move(const FInputActionInstance& Instance)
{
	FRotator ControlRotation = GetControlRotation();

	ControlRotation.Pitch = 0.f;
	ControlRotation.Roll = 0.f;

	const FVector2D& AxisValues = Instance.GetValue().Get<FVector2D>();

	const FVector& ForwardVector = ControlRotation.Vector();
	const FVector& RightVector = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, AxisValues.Y);

	AddMovementInput(RightVector, AxisValues.X);
}

void AMYMPlayer::LookMouse(const FInputActionInstance& Value)
{
	const FVector2D& InputVector = Value.GetValue().Get<FVector2D>();
	
	if (!InputVector.IsNearlyZero())
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

void AMYMPlayer::Interact()
{
	if (InteractionComponent)
	{
		InteractionComponent->Interact();
	}
}

