// CAS Tutorial JsPalacios


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WcParams)
{
	PlayerController = WcParams.PlayerController;
	PlayerState = WcParams.PlayerState;
	AbilitySystemComponent = WcParams.AbilitySystemComponent;
	AttributeSet = WcParams.AttributeSet;
}
