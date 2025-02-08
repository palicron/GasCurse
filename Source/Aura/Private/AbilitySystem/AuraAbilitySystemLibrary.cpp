// CAS Tutorial JsPalacios


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGamePlayTags.h"
#include "Game/AuraGameModeBase.h"
#include "Game/LoadScreenSaveGame.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

bool UAuraAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WordContextObject,FWidgetControllerParams& outWCParams,AAuraHUD*& OutAuraHud)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WordContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			OutAuraHud = AuraHUD;
			outWCParams.AttributeSet = AS;
			outWCParams.AbilitySystemComponent = ASC;
			outWCParams.PlayerState = PS;
			outWCParams.PlayerController = PC;
			return true;
		}
	}

	return false;
}

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WordContextObject)
{
	FWidgetControllerParams WCParams;
	AAuraHUD* AuraHUD;
	if(MakeWidgetControllerParams(WordContextObject,WCParams,AuraHUD))
	{
		return AuraHUD->GetOverlayWidgetController(WCParams);
	}
	
	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WordContextObject)
{

	FWidgetControllerParams WCParams;
	AAuraHUD* AuraHUD;

	if(MakeWidgetControllerParams(WordContextObject,WCParams,AuraHUD))
	{
		return AuraHUD->GetUAttributeMenuWidgetController(WCParams);
	}
	
	return nullptr;
	
}

USpellMenuWidgetController* UAuraAbilitySystemLibrary::GetSpellMenuWidgetController(const UObject* WordContextObject)
{
	FWidgetControllerParams WCParams;
	AAuraHUD* AuraHUD;

	if(MakeWidgetControllerParams(WordContextObject,WCParams,AuraHUD))
	{
		return AuraHUD->GetSpellMenuWidgetController(WCParams);
	}
	
	return nullptr;
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WordContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	if(const AAuraGameModeBase* AuraGM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WordContextObject)))
	{
		const AActor* AvatarActor = ASC->GetAvatarActor();
		
		const UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WordContextObject);
		const FCharacterClassDefaultInfo ClassDefInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

		FGameplayEffectContextHandle PrimaryContextsHandel = ASC->MakeEffectContext();
		PrimaryContextsHandel.AddSourceObject(AvatarActor);
		
		const FGameplayEffectSpecHandle PrimarySpecHandel = ASC->MakeOutgoingSpec(ClassDefInfo.PrimaryAttributes,Level,PrimaryContextsHandel);
		ASC->ApplyGameplayEffectSpecToSelf(*PrimarySpecHandel.Data);

		FGameplayEffectContextHandle SencondaryContextsHandel = ASC->MakeEffectContext();
		SencondaryContextsHandel.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle SecondarySpecHandel = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes,Level,SencondaryContextsHandel);
		ASC->ApplyGameplayEffectSpecToSelf(*SecondarySpecHandel.Data);

		FGameplayEffectContextHandle VitalContextsHandel = ASC->MakeEffectContext();
		VitalContextsHandel.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle VitalSpecHandel = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes,Level,VitalContextsHandel);
		ASC->ApplyGameplayEffectSpecToSelf(*VitalSpecHandel.Data);
	}
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributesFromSaveData(const UObject* WordContextObject,
	UAbilitySystemComponent* ASC, ULoadScreenSaveGame* SaveGame)
{
	const UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WordContextObject);
	if(!CharacterClassInfo)
	{
		return;
	}

	const FAuraGamePlayTags& GamePlayTags = FAuraGamePlayTags::Get();

	const AActor* SourceAvatarActor = ASC->GetAvatarActor();
	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);
	
	
	const FGameplayEffectSpecHandle DamageEffectSpecHandle =  ASC->MakeOutgoingSpec(CharacterClassInfo->PrimaryAttributes_SetByCaller,1.f,EffectContextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,GamePlayTags.Attributes_Primary_Strength,SaveGame->Strength);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,GamePlayTags.Attributes_Primary_Intelligence,SaveGame->Intelligence);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,GamePlayTags.Attributes_Primary_Resilience,SaveGame->Resilience);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,GamePlayTags.Attributes_Primary_Vigor,SaveGame->Vigor);

	ASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data);

	FGameplayEffectContextHandle SencondaryContextsHandel = ASC->MakeEffectContext();
	SencondaryContextsHandel.AddSourceObject(SourceAvatarActor);
	const FGameplayEffectSpecHandle SecondarySpecHandel = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes_Infinite,1.f,SencondaryContextsHandel);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondarySpecHandel.Data);

	FGameplayEffectContextHandle VitalContextsHandel = ASC->MakeEffectContext();
	VitalContextsHandel.AddSourceObject(SourceAvatarActor);
	const FGameplayEffectSpecHandle VitalSpecHandel = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes,1.f,VitalContextsHandel);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalSpecHandel.Data);
}

void UAuraAbilitySystemLibrary::GiveStartUpAbilities(const UObject* WordContextObject, UAbilitySystemComponent* ASC,ECharacterClass CharacterClass)
{
	const UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WordContextObject);
	if(!CharacterClassInfo) return;
	for (const TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (const TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{

		if(ASC && ASC->GetAvatarActor()->Implements<UCombatInterface>())
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, ICombatInterface::Execute_GetPlayerLevel(ASC->GetAvatarActor()));
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

UCharacterClassInfo* UAuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WordContextObject)
{
	if (const AAuraGameModeBase* AuraGM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WordContextObject)))
	{
		return AuraGM->CharacterClassInfo;
	}

	return nullptr;
}

bool UAuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle) 
{ 
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->IsBlockHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle) 
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->IsCriticalHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->IsSuccessfulDebuff();
	}
	return false;
}

float UAuraAbilitySystemLibrary::GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->GetDebuffDamage();
	}
	return false;
}

float UAuraAbilitySystemLibrary::GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->GetDebuffDuration();
	}
	return 0.f;
}

float UAuraAbilitySystemLibrary::GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->GetDebuffFrecuency();
	}
	return 0.f;
}

FGameplayTag UAuraAbilitySystemLibrary::GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		if(Context->GetDamageType().IsValid())
		{
			return *Context->GetDamageType();
		}
	}
	return FGameplayTag();
}

FVector UAuraAbilitySystemLibrary::GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->GetDeathImpulse();
	}
	return FVector::ZeroVector;
}

FVector UAuraAbilitySystemLibrary::GetKnockBackForce(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->GetKnockBackForce();
	}
	return FVector::ZeroVector;
}

bool UAuraAbilitySystemLibrary::IsRadialDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->IsRadialDamage();
	}
	return false;
}

float UAuraAbilitySystemLibrary::GetRadialDamageInnerRadius(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->GetRadialDamageInnerRadius();
	}
	return 0.f;
}

float UAuraAbilitySystemLibrary::GetRadialDamageOutterRadius(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->GetRadialDamageOuterRadius();
	}
	return 0.f;
}

FVector UAuraAbilitySystemLibrary::GetRadiusDamageOrigen(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext* Context = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return Context->GetRadialDamageOrigin();
	}
	return FVector::ZeroVector;
}


void UAuraAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetIsBlockHit(bInIsBlockedHit);
	}
}

void UAuraAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UAuraAbilitySystemLibrary::SetIsSuccefulDebuff(FGameplayEffectContextHandle& EffectContextHandle,bool bInSuccessfulDebuff)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetIsSuccessfulDebuff(bInSuccessfulDebuff);
	}
}

void UAuraAbilitySystemLibrary::SetDebuffDamage(FGameplayEffectContextHandle& EffectContextHandle, float InDebuffDamage)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetIsDebuffDamage(InDebuffDamage);
	}
}

void UAuraAbilitySystemLibrary::SetDebuffDuration(FGameplayEffectContextHandle& EffectContextHandle,
	float InDebuffDuration)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetDebuffDuration(InDebuffDuration);
	}
}

void UAuraAbilitySystemLibrary::SetDebuffFrequency(FGameplayEffectContextHandle& EffectContextHandle,float InDebuffFrquency)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetDebuffFrecuency(InDebuffFrquency);
	}
}

void UAuraAbilitySystemLibrary::SetDebuffType(FGameplayEffectContextHandle& EffectContextHandle,const FGameplayTag& InDamageType)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		const TSharedPtr<FGameplayTag> DamageType = MakeShared<FGameplayTag>(InDamageType);
		Context->SetDamageTypes(DamageType);
	}
}

void UAuraAbilitySystemLibrary::SetDeathImpulse(FGameplayEffectContextHandle& EffectContextHandle,const FVector& InDeathImpulse)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetDeathImpulse(InDeathImpulse);
	}
}

void UAuraAbilitySystemLibrary::SetKnockBackForce(FGameplayEffectContextHandle& EffectContextHandle,const FVector& InForce)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetKnockBackForce(InForce);
	}
}

void UAuraAbilitySystemLibrary::SetIsRadialDamage(FGameplayEffectContextHandle& EffectContextHandle, const bool bInIsRadialDamage)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetIsRadialDamage(bInIsRadialDamage);
	}
}

void UAuraAbilitySystemLibrary::SetIsRadialDamageInnerRadius(FGameplayEffectContextHandle& EffectContextHandle, const float InInnerRadius)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetRadialDamageInnerRadius(InInnerRadius);
	}
}

void UAuraAbilitySystemLibrary::SetIsRadialDamageOuterRadius(FGameplayEffectContextHandle& EffectContextHandle, const float InOuterRadius)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetRadialDamageOuterRadius(InOuterRadius);
	}
}

void UAuraAbilitySystemLibrary::SetRadialDamageOrigin(FGameplayEffectContextHandle& EffectContextHandle, const FVector& InRadialDamageOrigen)
{
	if(FAuraGameplayEffectContext* Context = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		Context->SetRadialDamageOrigin(InRadialDamageOrigen);
	}
}

void UAuraAbilitySystemLibrary::GetLifePlayerWithinRadius(const UObject* WordContextObject,
                                                          TArray<AActor*>& OutOverLappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);
	// query scene to see what we hit
	
	TArray<FOverlapResult> Overlaps;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WordContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			
			if( Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverLappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}

void UAuraAbilitySystemLibrary::GetClosestTargets(const int32 MaxTargets, const TArray<AActor*>& Actors, TArray<AActor*>& OutClosestTargets, const FVector& Origin)
{
	if(Actors.Num() <= MaxTargets)
	{
		OutClosestTargets = Actors;
		return;
	}

	TArray<AActor*> ActorsToCheck = Actors;
	int32 NumTargetsFound = 0;

	while(NumTargetsFound < MaxTargets)
	{
		if (ActorsToCheck.Num() == 0)
		{
			break;
		}
		double ClosesDistance = TNumericLimits<double>::Max();
		AActor* ClosestActor = nullptr;
		for (AActor* PotentialTarget : ActorsToCheck)
		{
			if (const double Distance = FVector::Dist(Origin, PotentialTarget->GetActorLocation()); Distance < ClosesDistance)
			{
				ClosesDistance = Distance;
				ClosestActor = PotentialTarget;
			}
		}
		ActorsToCheck.Remove(ClosestActor);
		OutClosestTargets.AddUnique(ClosestActor);
		++NumTargetsFound;
	}
}


bool UAuraAbilitySystemLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	return !FirstActor->ActorHasTag(FName("Player")) == SecondActor->ActorHasTag(FName("Player"));
}

int32 UAuraAbilitySystemLibrary::GetXPRewardForClassAndLevel(const UObject* WordContextObject, ECharacterClass CharacterClass, int32 CharacterLevel)
{
	const UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WordContextObject);
	if(!CharacterClassInfo) return 0;

	FCharacterClassDefaultInfo CharacterInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	return static_cast<int32>(CharacterInfo.XPReward.GetValueAtLevel(CharacterLevel));
}

UAbilityInfo* UAuraAbilitySystemLibrary::GetAbilityInfo(const UObject* WordContextObject)
{
	if (const AAuraGameModeBase* AuraGM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WordContextObject)))
	{
		return AuraGM->AbilityInfo;
	}

	return nullptr;
}

FGameplayEffectContextHandle UAuraAbilitySystemLibrary::ApplyDamageEffect(const FDamageEffectParams DamageEffectParams)
{
	const FAuraGamePlayTags& GamePlayTags = FAuraGamePlayTags::Get();
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	FGameplayEffectContextHandle EffectContextHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);
	
	SetDeathImpulse(EffectContextHandle,DamageEffectParams.DeathImpulse);
	SetKnockBackForce(EffectContextHandle,DamageEffectParams.KnockBackForce);
	SetIsRadialDamage(EffectContextHandle,DamageEffectParams.bIsRadialDamage);
	SetIsRadialDamageInnerRadius(EffectContextHandle,DamageEffectParams.RadialDamageInnerRadius);
	SetIsRadialDamageOuterRadius(EffectContextHandle,DamageEffectParams.RadialDamageOuterRadius);
	SetRadialDamageOrigin(EffectContextHandle,DamageEffectParams.RadialDamageOrigin);

		
	const FGameplayEffectSpecHandle DamageEffectSpecHandle =  DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass,DamageEffectParams.AbilityLevel,EffectContextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,DamageEffectParams.DamageType,DamageEffectParams.BaseDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,GamePlayTags.Debuff_Damage,DamageEffectParams.DebuffDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,GamePlayTags.Debuff_Duration,DamageEffectParams.DebuffDuration);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,GamePlayTags.Debuff_Chance,DamageEffectParams.DebuffChance);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle,GamePlayTags.Debuff_Frequency,DamageEffectParams.DebuffFrequency);
	
	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data);
	return EffectContextHandle;
}

TArray<FRotator> UAuraAbilitySystemLibrary::EvenlySpaceRotators(const FVector& Forward, const FVector& Axis, const float Spread, const int32 NumRotator)
{
	TArray<FRotator> Rotators;

	if (NumRotator > 1)
	{
		const FVector LeftSpread = Forward.RotateAngleAxis(-Spread / 2.f, Axis);
		const float DeltaSpread = Spread / (NumRotator - 1);
		for (int32 i = 0; i < NumRotator; i++)
		{
			const FVector Direction = LeftSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			Rotators.Add(Direction.Rotation());
		}

		return Rotators;
	}
	
	Rotators.Add(Forward.Rotation());
	return Rotators;
}

TArray<FVector> UAuraAbilitySystemLibrary::EvenlyRotateVectors(const FVector& Forward, const FVector& Axis, const float Spread, const int32 NumVectors)
{
	TArray<FVector> Rotators;

	if (NumVectors > 1)
	{
		const FVector LeftSpread = Forward.RotateAngleAxis(-Spread / 2.f, Axis);
		const float DeltaSpread = Spread / (NumVectors - 1);
		for (int32 i = 0; i < NumVectors; i++)
		{
			const FVector Direction = LeftSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			Rotators.Add(Direction);
		}

		return Rotators;
	}

	Rotators.Add(Forward);
	return Rotators;
}

void UAuraAbilitySystemLibrary::SetIsRadialDamageEffectParam(FDamageEffectParams& DamageEffectParams, bool bIsRadial, float InnerRadius, float OuterRadius, FVector Origin)
{
	DamageEffectParams.bIsRadialDamage = bIsRadial;
	DamageEffectParams.RadialDamageInnerRadius = InnerRadius;
	DamageEffectParams.RadialDamageOuterRadius = OuterRadius;
	DamageEffectParams.RadialDamageOrigin = Origin;
}

void UAuraAbilitySystemLibrary::SetKnockbackDirection(FDamageEffectParams& DamageEffectParams, FVector KnockBackDirection, float Magnitude)
{
	DamageEffectParams.KnockBackForce = KnockBackDirection.GetSafeNormal() * (Magnitude == 0.f ? DamageEffectParams.KnockBackForceMagnitude : Magnitude);
}

void UAuraAbilitySystemLibrary::SetDeathInpulsDirection(FDamageEffectParams& DamageEffectParams, FVector InpulseDirection, float Magnitude)
{
	DamageEffectParams.DeathImpulse = InpulseDirection.GetSafeNormal() * (Magnitude == 0.f ? DamageEffectParams.DeathImpulseMagnitude : Magnitude);
}

void UAuraAbilitySystemLibrary::SetEffectParamASC(FDamageEffectParams& DamageEffectParams, UAbilitySystemComponent* InASC)
{
	DamageEffectParams.TargetAbilitySystemComponent = InASC;
}
