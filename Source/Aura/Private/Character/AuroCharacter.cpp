// CAS Tutorial JsPalacios


#include "Character/AuroCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	ArmSpringCompoent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	ArmSpringCompoent->SetupAttachment(RootComponent);
	ArmSpringCompoent->TargetArmLength = 400.f;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(ArmSpringCompoent, USpringArmComponent::SocketName);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	
	if(	AAuraPlayerController* AuraPlayerController =  Cast<AAuraPlayerController>(GetController()))
	{
		 if(AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		 {
		 	AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		 }
	}
}
