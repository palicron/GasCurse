// CAS Tutorial JsPalacios


#include "Character/AuraEnemy.h"

void AAuraEnemy::HighlightActor()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			FString::Printf(TEXT("HightLight Actor :  %s"), *GetName()));
}

void AAuraEnemy::UnHighLightActor()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			FString::Printf(TEXT("UnHightLight Actor :  %s"), *GetName()));
}
