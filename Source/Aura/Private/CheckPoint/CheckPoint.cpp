// CAS Tutorial JsPalacios


#include "CheckPoint/CheckPoint.h"

#include "Components/SphereComponent.h"

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

}

void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	CheckPointSphere->OnComponentBeginOverlap.AddDynamic(this,&ACheckPoint::OnSphereOverlap);
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
	if (OtherActor->ActorHasTag(FName("Player")))
	{
		HandleGLowEffects();
	}

}
