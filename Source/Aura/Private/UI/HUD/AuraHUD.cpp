// CAS Tutorial JsPalacios


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UAuraUserWidget* Widget = CreateWidget<UAuraUserWidget>(GetWorld(),OverLayWidgetClass);
	Widget->AddToViewport();
}
