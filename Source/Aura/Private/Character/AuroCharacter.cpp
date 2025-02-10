// CAS Tutorial JsPalacios


#include "Character/AuroCharacter.h"
#include "Character/AuroCharacter.h"

#include "AbilitySystemComponent.h"
#include "AuraGamePlayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Camera/CameraComponent.h"
#include "NiagaraComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Debuff/DebuffNiagaraComponent.h"
#include "Game/AuraGameInstance.h"
#include "Game/AuraGameModeBase.h"
#include "Game/LoadScreenSaveGame.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	ArmSpringCompoent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	ArmSpringCompoent->SetupAttachment(RootComponent);
	ArmSpringCompoent->TargetArmLength = 400.f;
	ArmSpringCompoent->bDoCollisionTest = false;
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(ArmSpringCompoent, USpringArmComponent::SocketName);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CharacterClass = ECharacterClass::Elementalist;

	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("Level Up Niagara Component");
	LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
	LevelUpNiagaraComponent->bAutoActivate = false;
}

int32 AAuraCharacter::GetPlayerLevel_Implementation() const
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
}

void AAuraCharacter::AddToXP_Implementation(int32 InXp)
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToXP(InXp);
}

void AAuraCharacter::LevelUp_Implementation()
{
	MulticastLevelUpParticles();
}


void AAuraCharacter::MulticastLevelUpParticles_Implementation() const
{
	if(IsValid(LevelUpNiagaraComponent))
	{
		const FVector CameraLocation = PlayerCamera->GetComponentLocation();
		const FVector NiagaraLocation = LevelUpNiagaraComponent->GetComponentLocation();
		const FRotator ToCameraRotation = (CameraLocation - NiagaraLocation).Rotation();
		LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotation);
		LevelUpNiagaraComponent->Activate(true);
	}
}

int32 AAuraCharacter::GetCurrentXP_Implementation() const
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerXP();
}

int32 AAuraCharacter::FindLevelForXP_Implementation(int32 InXP) const
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	check(AuraPlayerState->LevelUpInfo);
	return AuraPlayerState->LevelUpInfo->FindLevelForXp(InXP);
}

int32 AAuraCharacter::GetAttributePointReward_Implementation(const int32 Level) const
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	check(AuraPlayerState->LevelUpInfo);
	return AuraPlayerState->LevelUpInfo->LevelUpInfos[Level].AttributePointAward;
}

int32 AAuraCharacter::GetSpellPointsReward_Implementation(const int32 Level) const
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	check(AuraPlayerState->LevelUpInfo);
	return AuraPlayerState->LevelUpInfo->LevelUpInfos[Level].SpellPointAward;
}

void AAuraCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToLevel(InPlayerLevel);

	if(UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		AuraASC->UpdateAbilityStatus(AuraPlayerState->GetPlayerLevel());
	}
}

void AAuraCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{

	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToAttributePoints(InAttributePoints);
}

void AAuraCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToSpellPoints(InSpellPoints);
}

int32 AAuraCharacter::GetAttributePoints_Implementation() const
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetAttributePoints();
}

int32 AAuraCharacter::GetSpellPoints_Implementation() const
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetSpellPoints();
}

void AAuraCharacter::OnRep_IsStunned()
{
	if(UAuraAbilitySystemComponent* AuraASc = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		FGameplayTagContainer BlockedTags;
		
		BlockedTags.AddTag(FAuraGamePlayTags::Get().Player_Block_InputReleased);
		BlockedTags.AddTag(FAuraGamePlayTags::Get().Player_Block_CursorTrace);
		BlockedTags.AddTag(FAuraGamePlayTags::Get().Player_Block_InputHeld);
		BlockedTags.AddTag(FAuraGamePlayTags::Get().Player_Block_InputPressed);
		if(bIsStunned)
		{
			AuraASc->AddLooseGameplayTags(BlockedTags);
			StunDebuffComponent->Activate();
		}
		else
		{
			AuraASc->RemoveLooseGameplayTags(BlockedTags);
			StunDebuffComponent->Deactivate();
		}
		
	}
}

void AAuraCharacter::OnRep_IsBurned()
{
	if (bIsBurned)
	{
		BurnDebuffComponent->Activate();
	}
	else
	{
		BurnDebuffComponent->Deactivate();
	}
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
	LoadProgress();
	
	AddCharacterAbilities();
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
	OnASCRegisterRegister.Broadcast(AbilitySystemComponent);
	AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGamePlayTags::Get().Debuff_Stun,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&AAuraCharacter::StunTagChanged);
	
	if(	AAuraPlayerController* AuraPlayerController =  Cast<AAuraPlayerController>(GetController()))
	{
		 if(AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		 {
		 	AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		 }
	}


}

void AAuraCharacter::LoadProgress()
{
	AAuraGameModeBase* AuraGameModeBase = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	if (!AuraGameModeBase)
	{
		return;
	}
	
	ULoadScreenSaveGame* SaveData =  AuraGameModeBase->RetrieveInGameSaveData();

	if (!SaveData)
	{
		return;
	}

	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	if (!AuraPlayerState)
	{
		return;
	}


	if (SaveData->bFirstTimeLoadIn)
	{
		InitializeDefaultAttributes();
		AddCharacterAbilities();
	}
	else
	{
		if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
		{
			AuraASC->AddCharacterAbilitiesFromSaveData(SaveData);
		}

		AuraPlayerState->SetLevel(SaveData->PlayerLevel);
		AuraPlayerState->SetXP(SaveData->PlayerXP);
		AuraPlayerState->SetAttributePoint(SaveData->AttributePoints);
		AuraPlayerState->SetSpellPoint(SaveData->SpellPoints);

		UAuraAbilitySystemLibrary::InitializeDefaultAttributesFromSaveData(this,AbilitySystemComponent,SaveData);
	}
	
}



void AAuraCharacter::ShowMagicCircle_Implementation(UMaterialInterface* DecalInterface)
{
	if(	AAuraPlayerController* AuraPlayerController =  Cast<AAuraPlayerController>(GetController()))
	{
		AuraPlayerController->ShowMagicCircle(DecalInterface);
		AuraPlayerController->bShowMouseCursor = false;
	}
}

void AAuraCharacter::HideMagicCircle_Implementation()
{
	if(	AAuraPlayerController* AuraPlayerController =  Cast<AAuraPlayerController>(GetController()))
	{
		AuraPlayerController->HideMagicCircle();
		AuraPlayerController->bShowMouseCursor = true;
	}
}

void AAuraCharacter::SaveProgress_Implementation(const FName& CheckPointTag)
{
	if (!HasAuthority())
	{
		return;
	}
	
	AAuraGameModeBase* AuraGameModeBase = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	if (!AuraGameModeBase)
	{
		return;
	}
	
	ULoadScreenSaveGame* SaveData =  AuraGameModeBase->RetrieveInGameSaveData();

	if (!SaveData)
	{
		return;
	}


	SaveData->PlayerStartTag = CheckPointTag;

	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	if (!AuraPlayerState)
	{
		return;
	}

	SaveData->PlayerLevel = AuraPlayerState->GetPlayerLevel();
	SaveData->PlayerXP = AuraPlayerState->GetPlayerXP();
	SaveData->AttributePoints = AuraPlayerState->GetAttributePoints();
	SaveData->SpellPoints = AuraPlayerState->GetSpellPoints();
	SaveData->bFirstTimeLoadIn = false;

	SaveData->Strength = UAuraAttributeSet::GetStrengthAttribute().GetNumericValue(GetAttributeSet());
	SaveData->Intelligence = UAuraAttributeSet::GetIntelligenceAttribute().GetNumericValue(GetAttributeSet());
	SaveData->Resilience = UAuraAttributeSet::GetResilienceAttribute().GetNumericValue(GetAttributeSet());
	SaveData->Vigor = UAuraAttributeSet::GetVigorAttribute().GetNumericValue(GetAttributeSet());


	FForEachAbility SaveAbilityDelegate;
	UAuraAbilitySystemComponent* AuraAC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	SaveData->SaveAbilities.Empty();
	SaveAbilityDelegate.BindLambda([&](const FGameplayAbilitySpec& spec)
	{

		FSaveAbility Ability;
		const FGameplayTag AbilityTag = AuraAC->GetAbilityTagFromSpec(spec);
		UAbilityInfo* AbilityInfo = UAuraAbilitySystemLibrary::GetAbilityInfo(this);
		FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);

		Ability.GameplayAbility = Info.Ability;
		Ability.AbilityLevel = spec.Level;
		Ability.AbilitySlot = AuraAC->GetSlotFromAbilityTag(AbilityTag);
		Ability.StatusAbilityTag = AuraAC->GetStatusFromAbilityTag(AbilityTag);
		Ability.AbilityTag = AbilityTag;
		Ability.AbilityType = Info.AbilityType;
		
		SaveData->SaveAbilities.AddUnique(Ability);
	});
	
	AuraAC->ForEachAbility(SaveAbilityDelegate);
	
	AuraGameModeBase->SaveInGameProgressData(SaveData);
}
