// CAS Tutorial JsPalacios


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGamePlayTags.h"
#include "Game/AuraGameModeBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

bool UAuraAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WordContextObject,FWidgetControllerParams& outWCParams,AAuraHUD*& OutAuraHud)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WordContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			OutAuraHud = AuraHUD;
			outWCParams.AttributeSet = AS;
			outWCParams.AbilitySystemComponent = ASC;
			outWCParams.PlayerState = PS;
			outWCParams.PlayerController = PC;
			return true;
		}
	}

	return false;
}

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WordContextObject)
{
	FWidgetControllerParams WCParams;
	AAuraHUD* AuraHUD;
	if(MakeWidgetControllerParams(WordContextObject,WCParams,AuraHUD))
	{
		return AuraHUD->GetOverlayWidgetController(WCParams);
	}
	
	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WordContextObject)
{

	FWidgetControllerParams WCParams;
	AAuraHUD* AuraHUD;

	if(MakeWidgetControllerParams(WordContextObject,WCParams,AuraHUD))
	{
		return AuraHUD->GetUAttributeMenuWidgetController(WCParams);
	}
	
	return nullptr;
	
}

USpellMenuWidgetController* UAuraAbilitySystemLibrary::GetSpellMenuWidgetController(const UObject* WordContextObject)
{
	FWidgetControllerParams WCParams;
	AAuraHUD* AuraHUD;

	if(MakeWidgetControllerParams(WordContextObject,WCParams,AuraHUD))
	{
		return AuraHUD->GetSpellMenuWidgetController(WCParams);
	}
	
	return nullptr;
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WordContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	if(const AAuraGameModeBase* AuraGM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WordContextObject)))
	{
		const AActor* AvatarActor = ASC->GetAvatarActor();
		
		const UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WordContextObject);
		const FCharacterClassDefaultInfo ClassDefInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

		FGameplayEffectContextHandle PrimaryContextsHandel = ASC->MakeEffectContext();
		PrimaryContextsHandel.AddSourceObject(AvatarActor);
		
		const FGameplayEffectSpecHandle PrimarySpecHandel = ASC->MakeOutgoingSpec(ClassDefInfo.PrimaryAttributes,Level,PrimaryContextsHandel);
		ASC->ApplyGameplayEffectSpecToSelf(*PrimarySpecHandel.Data);

		FGameplayEffectContextHandle SencondaryContextsHandel = ASC->MakeEffectContext();
		SencondaryContextsHandel.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle SecondarySpecHandel = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes,Level,SencondaryContextsHandel);
		ASC->ApplyGameplayEffectSpecToSelf(*SecondarySpecHandel.Data);

		FGameplayEffectContextHandle VitalContextsHandel = ASC->MakeEffectContext();
		VitalContextsHandel.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle VitalSpecHandel = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes,Level,VitalContextsHandel);
		ASC->ApplyGameplayEffectSpecToSelf(*VitalSpecHandel.Data);
	}
}

void UAuraAbilitySystemLibrary::GiveStartUpAbilities(const UObject* WordContextObject, UAbilitySystemComponent* ASC,ECharacterClass CharacterClass)
{
	const UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WordContextObject);
	if(!CharacterClassInfo) return;
	for (const TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (const TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{

		if(ASC && ASC->GetAvatarActor()->Implements<UCombatInterface>())
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, ICombatInterface::Execute_GetPlayerLevel(ASC->GetAvatarActor()));
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

UCharacterClassInfo* UAuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WordContextObject)
{
	if (const AAuraGameModeBase* AuraGM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WordContextObject)))
	{
		return AuraGM->CharacterClassInfo;
	}

	return nullptr;
}

bool UAuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle) 
{ 
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->IsBlockHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle) 
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->IsCriticalHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->IsSuccessfulDebuff();
	}
	return false;
}

float UAuraAbilitySystemLibrary::GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->GetDebuffDamage();
	}
	return false;
}

float UAuraAbilitySystemLibrary::GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->GetDebuffDuration();
	}
	return 0.f;
}

float UAuraAbilitySystemLibrary::GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->GetDebuffFrecuency();
	}
	return 0.f;
}

FGameplayTag UAuraAbilitySystemLibrary::GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		if(Context->GetDamageType().IsValid())
		{
			return *Context->GetDamageType();
		}
	}
	return FGameplayTag();
}


void UAuraAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetIsBlockHit(bInIsBlockedHit);
	}
}

void UAuraAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UAuraAbilitySystemLibrary::SetIsSuccefulDebuff(FGameplayEffectContextHandle& EffectContextHandle,bool bInSuccessfulDebuff)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetIsSuccessfulDebuff(bInSuccessfulDebuff);
	}
}

void UAuraAbilitySystemLibrary::SetDebuffDamage(FGameplayEffectContextHandle& EffectContextHandle, float InDebuffDamage)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetIsDebuffDamage(InDebuffDamage);
	}
}

void UAuraAbilitySystemLibrary::SetDebuffDuration(FGameplayEffectContextHandle& EffectContextHandle,
	float InDebuffDuration)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetDebuffDuration(InDebuffDuration);
	}
}

void UAuraAbilitySystemLibrary::SetDebuffFrequency(FGameplayEffectContextHandle& EffectContextHandle,float InDebuffFrquency)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetDebuffFrecuency(InDebuffFrquency);
	}
}

void UAuraAbilitySystemLibrary::SetDebuffType(FGameplayEffectContextHandle& EffectContextHandle,const FGameplayTag& InDamageType)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		const TSharedPtr<FGameplayTag> DamageType = MakeShared<FGameplayTag>(InDamageType);
		Context->SetDamageTypes(DamageType);
	}
}

void UAuraAbilitySystemLibrary::GetLifePlayerWithinRadius(const UObject* WordContextObject,
                                                          TArray<AActor*>& OutOverLappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);
	// query scene to see what we hit
	
	TArray<FOverlapResult> Overlaps;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WordContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			
			if( Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverLappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}

bool UAuraAbilitySystemLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	return !FirstActor->ActorHasTag(FName("Player")) == SecondActor->ActorHasTag(FName("Player"));
}

int32 UAuraAbilitySystemLibrary::GetXPRewardForClassAndLevel(const UObject* WordContextObject, ECharacterClass CharacterClass, int32 CharacterLevel)
{
	const UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WordContextObject);
	if(!CharacterClassInfo) return 0;

	FCharacterClassDefaultInfo CharacterInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	return static_cast<int32>(CharacterInfo.XPReward.GetValueAtLevel(CharacterLevel));
}

UAbilityInfo* UAuraAbilitySystemLibrary::GetAbilityInfo(const UObject* WordContextObject)
{
	if (const AAuraGameModeBase* AuraGM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WordContextObject)))
	{
		return AuraGM->AbilityInfo;
	}

	return nullptr;
}

FGameplayEffectContextHandle UAuraAbilitySystemLibrary::ApplyDamageEffect(const FDamageEffectParams DamageEffectParams)
{
	const FAuraGamePlayTags& GamePlayTags = FAuraGamePlayTags::Get();
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	FGameplayEffectContextHandle EffectContextHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);
	const FGameplayEffectSpecHandle DamageEffectSpecHandle =  DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass,DamageEffectParams.AbilityLevel,EffectContextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,DamageEffectParams.DamageType,DamageEffectParams.BaseDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,GamePlayTags.Debuff_Damage,DamageEffectParams.DebuffDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,GamePlayTags.Debuff_Duration,DamageEffectParams.DebuffDuration);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,GamePlayTags.Debuff_Chance,DamageEffectParams.DebuffChance);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,GamePlayTags.Debuff_Frequency,DamageEffectParams.DebuffFrequency);
	
	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data);
	return EffectContextHandle;
}
