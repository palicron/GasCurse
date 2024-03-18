// CAS Tutorial JsPalacios


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "Game/AuraGameModeBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WordContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WordContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WordContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WordContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return AuraHUD->GetUAttributeMenuWidgetController(WidgetControllerParams);
		}
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
		if(const ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor()))
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, CombatInterface->GetPlayerLevel());
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
