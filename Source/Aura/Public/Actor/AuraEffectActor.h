// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class  EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy: uint8
{
	RemovalOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraEffectActor();

	virtual void Tick(float DeltaSeconds) override;
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickUP Movement")
	bool bRotates = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickUP Movement")
	float RotationRate = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickUP Movement")
	bool bSinusoidalMovement = false;

	UFUNCTION(BlueprintCallable, Category="PickUP Movement")
	void StartSinosoidalMovement();

	UFUNCTION(BlueprintCallable, Category="PickUP Movement")
	void StartRotationMovement();
	
	UPROPERTY(BlueprintReadWrite)
	FVector CalculatedLocation;

	UPROPERTY(BlueprintReadOnly)
	FRotator CalculatedRotation;
	
	void ItemMovement(float DeltaSeconds);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickUP Movement")
	float SineAmplitude = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickUP Movement")
	FVector InitialLocation;

	float RunningTime = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickUP Movement")
	float SinePeriodConst  = 1.f;
	TMap<UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveEffectHandles;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	bool bDestroyOnEffectApplication = false;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	bool bApplyEffectsToEnemies = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemovalOnEndOverlap;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGamePlayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGamePlayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGamePlayEffectClass;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GamePlayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Applied Effects")
	float ActorLevel = 1.f;
};
