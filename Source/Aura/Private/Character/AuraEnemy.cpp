// CAS Tutorial JsPalacios


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "AuraGamePlayTags.h"
#include "AI/AuraAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/AuraUserWidget.h"


AAuraEnemy::AAuraEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");

	HealthBar->SetupAttachment(GetRootComponent());
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->MarkRenderStateDirty();
	Weapon->MarkRenderStateDirty();
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	BaseWalkSpeed = 250.f;
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	InitAbilityActorInfo();
	if(HasAuthority())
	{
		UAuraAbilitySystemLibrary::GiveStartUpAbilities(this,AbilitySystemComponent, CharacterClass);	
	}
	
	if (UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		AuraUserWidget->SetWidgetController(this);
	}

	if (const UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGamePlayTags::Get().Effects_HitReact,EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,&AAuraEnemy::HitReactTagChange);
		OnHealthChanged.Broadcast(AuraAS->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
	}
}


int32 AAuraEnemy::GetPlayerLevel_Implementation() const
{
	return Level;
}

void AAuraEnemy::Die(const FVector& DeathImpulse)
{
	SpawnLoot();
	SetLifeSpan(LifeSpan);
	if(AuraAIController && AuraAIController->GetBlackboardComponent())
	{
		AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dead"),true);
	}
	Super::Die(DeathImpulse);
}

void AAuraEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* AAuraEnemy::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void AAuraEnemy::HighlightActor_Implementation()
{
	if (IsValid(GetMesh()) && IsValid(Weapon))
	{
		GetMesh()->SetRenderCustomDepth(true);
		Weapon->SetRenderCustomDepth(true);
	}
}

void AAuraEnemy::UnHighLightActor_Implementation()
{
	if (IsValid(GetMesh()) && IsValid(Weapon))
	{
		GetMesh()->SetRenderCustomDepth(false);
		Weapon->SetRenderCustomDepth(false);
	}
}

void AAuraEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGamePlayTags::Get().Debuff_Stun,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&AAuraEnemy::StunTagChanged);
	if(HasAuthority())
	{
		InitializeDefaultAttributes();
	}

	OnASCRegisterRegister.Broadcast(AbilitySystemComponent);
}

void AAuraEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(!HasAuthority())
	{
		return;
	}
	
	AuraAIController = Cast<AAuraAIController>(NewController);
	if(AuraAIController && AuraAIController->GetBlackboardComponent())
	{
		AuraAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		AuraAIController->RunBehaviorTree(BehaviorTree);
		AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"),false);
		AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"),CharacterClass != ECharacterClass::Warrior);
	}

	
}

void AAuraEnemy::HitReactTagChange(const FGameplayTag CallBackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if(AuraAIController && AuraAIController->GetBlackboardComponent())
	{
		AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"),bHitReacting);
	}
}

void AAuraEnemy::InitializeDefaultAttributes() const
{
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this,CharacterClass,Level,AbilitySystemComponent);
}

void AAuraEnemy::StunTagChanged(const FGameplayTag CallbackTag, const int32 NewCount)
{
	Super::StunTagChanged(CallbackTag, NewCount);
	if(AuraAIController && AuraAIController->GetBlackboardComponent())
	{
		AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("Stunned"),bIsStunned);
	}
}
