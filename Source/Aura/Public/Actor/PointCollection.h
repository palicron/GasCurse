// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointCollection.generated.h"

UCLASS()
class AURA_API APointCollection : public AActor
{
	GENERATED_BODY()

public:
	APointCollection();

	UFUNCTION(BlueprintPure)
	TArray<USceneComponent*> GetGroundPoints(const FVector& GroundLocation, const int32 NumPoints, const float YawOverride = 0.f);
	
protected:
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<USceneComponent*> ImmutablePts;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> Pt_0;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> Pt_1;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> Pt_2;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> Pt_3;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> Pt_4;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> Pt_5;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> Pt_6;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> Pt_7;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> Pt_8;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> Pt_9;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> Pt_10;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> Pt_11;
	


};
