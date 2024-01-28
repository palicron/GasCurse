// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"


#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UKismetSystemLibrary::PrintString(this,FString("Activate Abilityyy c++"),true, true,FLinearColor::Yellow,3);
}
