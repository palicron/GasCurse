// CAS Tutorial JsPalacios


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState,Level);
	DOREPLIFETIME(AAuraPlayerState,PlayerXP);
}

void AAuraPlayerState::SetXP(const int32 NewXP)
{
	PlayerXP = NewXP;
	OnXpChangeDelegate.Broadcast(PlayerXP);
}

void AAuraPlayerState::AddToXP(const int32 NewXP)
{
	PlayerXP += NewXP;
	OnXpChangeDelegate.Broadcast(PlayerXP);
}

void AAuraPlayerState::SetLevel(const int32 Newlevel)
{
	Level = Newlevel;
	OnLevelChangeDelegate.Broadcast(Level);
}

void AAuraPlayerState::AddToLevel(const int32 Newlevel)
{
	Level += Newlevel;
	OnLevelChangeDelegate.Broadcast(Level);
}

void AAuraPlayerState::OnRep_PlayerXP()
{
	OnXpChangeDelegate.Broadcast(PlayerXP);
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangeDelegate.Broadcast(Level);
}
