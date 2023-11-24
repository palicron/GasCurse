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

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GamePlayEffectClass)
{
	UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	
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

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGamePlayEffectClass);
		return;
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGamePlayEffectClass);
		return;
	}
	
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGamePlayEffectClass);
		return;
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGamePlayEffectClass);
		return;
	}
}

