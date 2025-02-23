// CAS Tutorial JsPalacios


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Kismet/KismetMathLibrary.h"
#include "Serialization/GameplayEffectContextNetSerializer.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRooy"));
	
}

void AAuraEffectActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	RunningTime += DeltaSeconds;
	if (RunningTime >= ((2 * PI)/SinePeriodConst))
	{
		RunningTime = 0.f;
	}
	ItemMovement(DeltaSeconds);
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	CalculatedLocation = GetActorLocation();
	CalculatedRotation = GetActorRotation();

}

void AAuraEffectActor::StartSinosoidalMovement()
{
	bSinusoidalMovement = true;
	InitialLocation = GetActorLocation();
	CalculatedLocation = GetActorLocation();
}

void AAuraEffectActor::StartRotationMovement()
{
	bRotates = true;
	CalculatedRotation = GetActorRotation();
}

void AAuraEffectActor::ItemMovement(float DeltaSeconds)
{
	if (bRotates)
	{
		const FRotator DeltaRotator(0.f, DeltaSeconds * RotationRate, 0.f);
		CalculatedRotation = UKismetMathLibrary::ComposeRotators(CalculatedRotation,DeltaRotator);
	}
	if (bSinusoidalMovement)
	{
		const float Sine = SineAmplitude * FMath::Sin(RunningTime * SinePeriodConst);
		CalculatedLocation = InitialLocation + FVector(0.f,0.0f,Sine);
	}
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GamePlayEffectClass)
{
	if(TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies)
	{
		return;
	}
	
	UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	
	if (!TargetAsc)
	{
		return;
	}

	check(GamePlayEffectClass);
	FGameplayEffectContextHandle ContextHandel = TargetAsc->MakeEffectContext();
	ContextHandel.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandel = TargetAsc->MakeOutgoingSpec(GamePlayEffectClass, ActorLevel, ContextHandel);
	FActiveGameplayEffectHandle ActiveEffectHandle =  TargetAsc->ApplyGameplayEffectSpecToSelf(*EffectSpecHandel.Data.Get());

	const bool bIsInfinite = EffectSpecHandel.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	if(bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemovalOnEndOverlap)
	{
		ActiveEffectHandles.Add(TargetAsc, ActiveEffectHandle);
	}

	if(!bIsInfinite)
	{
		Destroy();
	}
	
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if(TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies)
	{
		return;
	}
	
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
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGamePlayEffectClass);
	}
	
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if(TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies)
	{
		return;
	}
	
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
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGamePlayEffectClass);
		return;
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemovalOnEndOverlap)
	{
		UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetAsc) || !ActiveEffectHandles.Contains(TargetAsc))
		{
			return;
		}

		TargetAsc->RemoveActiveGameplayEffect(ActiveEffectHandles[TargetAsc], 1);
		ActiveEffectHandles.FindAndRemoveChecked(TargetAsc);
	}
}

