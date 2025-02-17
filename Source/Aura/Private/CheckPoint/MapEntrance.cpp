// CAS Tutorial JsPalacios


#include "CheckPoint/MapEntrance.h"

#include "Game/AuraGameModeBase.h"
#include "Interaction/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"


AMapEntrance::AMapEntrance(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

void AMapEntrance::HighlightActor_Implementation()
{
	if (CheckPointMesh)
	{
		CheckPointMesh->SetRenderCustomDepth(true);
	}
}

void AMapEntrance::LoadActor_Implementation()
{
}

void AMapEntrance::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UPlayerInterface>())
	{
		if (AAuraGameModeBase* AuraGM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			AuraGM->SaveWorldState(GetWorld(),DestinationMap.ToSoftObjectPath().GetAssetName());
		}
		IPlayerInterface::Execute_SaveProgress(OtherActor, DestinationPlayerStartTag);
	}
	UGameplayStatics::OpenLevelBySoftObjectPtr(this,DestinationMap);
}
