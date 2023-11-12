// CAS Tutorial JsPalacios


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WcParamas)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WcParamas);
	}

	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* Asc, UAttributeSet* As)
{
	checkf(OverLayWidgetClass, TEXT("OverLayy widget class Unitialized, pleas fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass,
	       TEXT("OverLayy widget Controller class Unitialized, pleas fill out BP_AuraHUD"));
	UAuraUserWidget* Widget = CreateWidget<UAuraUserWidget>(GetWorld(), OverLayWidgetClass);
	OverLayWidget = Cast<UAuraUserWidget>(Widget);
	const FWidgetControllerParams WidgetControllerParams(PC, PS, Asc, As);
	OverlayWidgetController = GetOverlayWidgetController(WidgetControllerParams);
	Widget->AddToViewport();
}
