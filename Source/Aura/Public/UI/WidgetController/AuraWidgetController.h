// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams(){}

	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* Asc, UAttributeSet* As ):
	PlayerController(PC),PlayerState(PS),AbilitySystemComponent(Asc), AttributeSet(As)  {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
	
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WcParams);

protected:
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
