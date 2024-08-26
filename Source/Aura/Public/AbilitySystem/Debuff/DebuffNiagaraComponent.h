// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NiagaraComponent.h"
#include "DebuffNiagaraComponent.generated.h"


/**
 * 
 */
UCLASS()
class AURA_API UDebuffNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()

public:

	UDebuffNiagaraComponent();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag DebuffTag;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void DebuffTagChanged(const FGameplayTag CallBackTag,int32 NewCount);

	UFUNCTION()
	void OnOwnerDeath(AActor* DeadActor);
};
