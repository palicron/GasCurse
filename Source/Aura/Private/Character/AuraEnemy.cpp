// CAS Tutorial JsPalacios


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"


AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEnemy::HighlightActor()
{
	if (IsValid(GetMesh()) && IsValid(Weapon))
	{
		GetMesh()->SetRenderCustomDepth(true);
		Weapon->SetRenderCustomDepth(true);
	}
}

void AAuraEnemy::UnHighLightActor()
{
	if (IsValid(GetMesh()) && IsValid(Weapon))
	{
		GetMesh()->SetRenderCustomDepth(false);
		Weapon->SetRenderCustomDepth(false);
	}
}
