// CAS Tutorial JsPalacios


#include "AuraAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "AuraGamePlayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	return *Cast<UAuraAssetManager>(GEngine->AssetManager);
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAuraGamePlayTags::InitializeNativeGameplayTags();
	//Requiere to useTarget Data
	UAbilitySystemGlobals::Get().InitGlobalData();

}
