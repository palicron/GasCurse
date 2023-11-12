// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverLayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WcParamas);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* Asc, UAttributeSet* As );

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverLayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
};
