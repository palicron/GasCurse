// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Aura Gameplay Tags
 *
 * Singleton containing native Gameplay Tags
 */

struct  FAuraGamePlayTags
{
public:

 static const FAuraGamePlayTags& Get() { return GameplayTags;}
 static void InitializeNativeGameplayTags();

 FGameplayTag Attributes_Secondary_Armor;
 
protected:

private:

 static FAuraGamePlayTags GameplayTags;
 
};
