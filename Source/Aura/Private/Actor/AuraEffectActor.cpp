// CAS Tutorial JsPalacios


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Serialization/GameplayEffectContextNetSerializer.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRooy"));
	
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GamePlayEffectClass)
{
	UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	
	if (!TargetAsc)
	{
		return;
	}

	check(GamePlayEffectClass);
	FGameplayEffectContextHandle ContextHandel = TargetAsc->MakeEffectContext();
	ContextHandel.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandel = TargetAsc->MakeOutgoingSpec(GamePlayEffectClass, 1.f, ContextHandel);
	TargetAsc->ApplyGameplayEffectSpecToSelf(*EffectSpecHandel.Data.Get());
}

