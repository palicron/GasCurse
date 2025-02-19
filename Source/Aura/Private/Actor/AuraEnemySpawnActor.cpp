// CAS Tutorial JsPalacios


#include "Actor/AuraEnemySpawnActor.h"

#include "Actor/AuraEnemySpawnPoint.h"
#include "Components/BoxComponent.h"
#include "Interaction/PlayerInterface.h"


AAuraEnemySpawnActor::AAuraEnemySpawnActor()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionObjectType(ECC_WorldStatic);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
}

void AAuraEnemySpawnActor::LoadActor_Implementation()
{
	if (bReach)
	{
		Destroy();
	}
}

void AAuraEnemySpawnActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&AAuraEnemySpawnActor::OnBoxOverlap);
}

void AAuraEnemySpawnActor::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>())
	{
		return;
	}
	
	bReach = true;

	for (AAuraEnemySpawnPoint* Point : Points)
	{
		if (Point)
		{
			Point->SpawnEnemy();
		}
	}

	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
}




