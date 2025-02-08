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
	DOREPLIFETIME(AAuraPlayerState,AttributePoints);
	DOREPLIFETIME(AAuraPlayerState,SpellPoints);
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
	OnLevelChangeDelegate.Broadcast(Level,false);
}

void AAuraPlayerState::AddToLevel(const int32 Newlevel)
{
	Level += Newlevel;
	OnLevelChangeDelegate.Broadcast(Level,true);
}

void AAuraPlayerState::AddToAttributePoints(int32 InPoints)
{
	AttributePoints += InPoints;
	OnAttributePointChangeDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::AddToSpellPoints(int32 InPoints)
{
	SpellPoints += InPoints;
	OnSpellPointChangeDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::SetAttributePoint(const int32 InPoints)
{
	AttributePoints = InPoints;
	OnAttributePointChangeDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::SetSpellPoint(const int32 InPoints)
{
	SpellPoints = InPoints;
	OnSpellPointChangeDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::OnRep_PlayerXP()
{
	OnXpChangeDelegate.Broadcast(PlayerXP);
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangeDelegate.Broadcast(Level,true);
}

void AAuraPlayerState::OnRep_AttributePoints(int32 OldAttributesPoint)
{
	OnAttributePointChangeDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::OnRep_SpellPoints(int32 OldSpellPoints)
{
	OnSpellPointChangeDelegate.Broadcast(SpellPoints);
}
