// CAS Tutorial JsPalacios


#include "AuraAssetManager.h"
#include "AuraGamePlayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	return *Cast<UAuraAssetManager>(GEngine->AssetManager);
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAuraGamePlayTags::InitializeNativeGameplayTags();
}
