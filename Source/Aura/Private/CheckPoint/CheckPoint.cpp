// CAS Tutorial JsPalacios


#include "CheckPoint/CheckPoint.h"

#include "Components/SphereComponent.h"
#include "Game/AuraGameModeBase.h"
#include "Interaction/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"

ACheckPoint::ACheckPoint(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	CheckPointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckPointMesh"));
	CheckPointMesh->SetupAttachment(GetRootComponent());
	CheckPointMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CheckPointMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	
	CheckPointSphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	CheckPointSphere->SetupAttachment(GetRootComponent());
	CheckPointSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CheckPointSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	CheckPointSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	MoveToComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MoveToComponent"));
	MoveToComponent->SetupAttachment(GetRootComponent());
	
	CheckPointMesh->SetCustomDepthStencilValue(CustomDepthStencilOverride);
	CheckPointMesh->MarkRenderStateDirty();
	CheckPointMesh->SetRenderCustomDepth(false);

}

void ACheckPoint::LoadActor_Implementation()
{
	if (bReached)
	{
		HandleGLowEffects();
	}
}

void ACheckPoint::SetMoveToLocation_Implementation(FVector& OutDestination)
{
	OutDestination = MoveToComponent->GetComponentLocation();
}

void ACheckPoint::HighlightActor_Implementation()
{
	if (CheckPointMesh && !bReached)
	{
		CheckPointMesh->SetRenderCustomDepth(true);
	}
}

void ACheckPoint::UnHighLightActor_Implementation()
{
	if (CheckPointMesh)
	{
		CheckPointMesh->SetRenderCustomDepth(false);
	}
}

void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	if (bCallOverLapCallback)
	{
		CheckPointSphere->OnComponentBeginOverlap.AddDynamic(this,&ACheckPoint::OnSphereOverlap);
	}

}

void ACheckPoint::HandleGLowEffects()
{
	CheckPointSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UMaterialInstanceDynamic* DynamicInstance = UMaterialInstanceDynamic::Create(CheckPointMesh->GetMaterial(0), this);
	CheckPointMesh->SetMaterial(0, DynamicInstance);
	CheckPointReached(DynamicInstance);
}

void ACheckPoint::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UPlayerInterface>())
	{
		bReached = true;
		if (AAuraGameModeBase* AuraGM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			const UWorld* World = GetWorld();
			FString MapName = World->GetMapName();
			MapName.RemoveFromStart(World->StreamingLevelsPrefix);
			
			AuraGM->SaveWorldState(GetWorld(),MapName);
		}
		IPlayerInterface::Execute_SaveProgress(OtherActor, PlayerStartTag);
		HandleGLowEffects();
	}
	
}
