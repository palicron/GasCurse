// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	TArray<FVector> SpawnLocation;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2,FVector::UpVector);
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i,FVector::UpVector);
		const FVector ChosenSpawnLocation = Location + Direction * FMath::RandRange(MinSpawnDistance,MaxSpawnDistance);
		SpawnLocation.Add(ChosenSpawnLocation);
		UKismetSystemLibrary::DrawDebugArrow( GetAvatarActorFromActorInfo(),Location,Location + Direction * MaxSpawnDistance,4.f,FColor::Yellow,3.f);
	}
	

	return SpawnLocation;
}
