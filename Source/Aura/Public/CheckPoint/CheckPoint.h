// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "CheckPoint.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class AURA_API ACheckPoint : public APlayerStart
{
	GENERATED_BODY()

public:
	
	ACheckPoint(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void BeginPlay() override;

	void HandleGLowEffects();
	
	UFUNCTION(BlueprintImplementableEvent)
	void CheckPointReached(UMaterialInstanceDynamic* DynamicInstance);
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> CheckPointMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> CheckPointSphere;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);

	
};
