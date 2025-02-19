// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "GameFramework/Actor.h"
#include "Interaction/SaveInterface.h"
#include "AuraEnemySpawnActor.generated.h"

class AAuraEnemySpawnPoint;
class UBoxComponent;
enum class ECharacterClass : uint8;
class AAuraEnemy;

UCLASS()
class AURA_API AAuraEnemySpawnActor : public AActor, public ISaveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEnemySpawnActor();

	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool bReach = false;
	//Save

	virtual void LoadActor_Implementation() override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<AAuraEnemySpawnPoint*> Points;
protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);

	
};
