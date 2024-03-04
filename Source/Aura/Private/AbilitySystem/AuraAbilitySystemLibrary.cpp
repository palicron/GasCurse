// CAS Tutorial JsPalacios


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "Game/AuraGameModeBase.h"
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

void UAuraAbilitySystemLibrary::GiveStartUpAbilities(const UObject* WordContextObject, UAbilitySystemComponent* ASC)
{
	if(const AAuraGameModeBase* AuraGM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WordContextObject)))
	{
		const UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WordContextObject);
		
		for(const TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
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
