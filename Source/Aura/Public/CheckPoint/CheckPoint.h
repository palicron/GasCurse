// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "Aura/Aura.h"
#include "GameFramework/PlayerStart.h"
#include "Interaction/HighlightInterface.h"
#include "Interaction/SaveInterface.h"
#include "CheckPoint.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class AURA_API ACheckPoint : public APlayerStart, public ISaveInterface, public IHighlightInterface
{
	GENERATED_BODY()

public:
	
	ACheckPoint(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool bReached = false;

	//SAve interface

	virtual bool ShouldLoadTransform_Implementation() override { return false; };

	virtual void LoadActor_Implementation() override;

	virtual void SetMoveToLocation_Implementation(FVector& OutDestination) override;

	virtual void HighlightActor_Implementation() override;

	virtual void UnHighLightActor_Implementation() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 CustomDepthStencilOverride = CUSTOM_DEPTH_TAN;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> MoveToComponent;
protected:

	virtual void BeginPlay() override;

	void HandleGLowEffects();
	
	UFUNCTION(BlueprintImplementableEvent)
	void CheckPointReached(UMaterialInstanceDynamic* DynamicInstance);
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> CheckPointMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> CheckPointSphere;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);

	
};
