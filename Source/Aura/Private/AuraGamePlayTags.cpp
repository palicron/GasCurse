// CAS Tutorial JsPalacios


#include "AuraGamePlayTags.h"
#include "GameplayTagsManager.h"

FAuraGamePlayTags FAuraGamePlayTags::GameplayTags;

void FAuraGamePlayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),FString("Reduces damage taken, improve Block Chance"));
}
