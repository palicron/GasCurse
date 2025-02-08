// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Game/LoadScreenSaveGame.h"
#include "MVVM_LoadSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndexSignature, const int32 ,WidgetSwitcherIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnableSelectSlotButtonSignature, const bool ,bEnable);
/**
 * 
 */
UCLASS()
class AURA_API UMVVM_LoadSlot : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FSetWidgetSwitcherIndexSignature SetWidgetSwitcherIndexDelegate;

	UPROPERTY(BlueprintAssignable)
	FEnableSelectSlotButtonSignature EnableSelectSlotButtonDelegate;
	
	void InitializeSlot();


	UPROPERTY()
	int32 SlotIndex;

	UPROPERTY()
	FName PlayerStartTag;
	
	void SetPlayerName(FString InPlayerName);

	FString GetPlayerName() const { return PlayerName; };

	void SetLoadSlotName(FString InLoadSlotName);

	FString GetLoadSlotName() const { return LoadSlotName; };

	void SetMapName(FString InMapName);

	FString GetMapName() const { return MapName; };

	void SetPlayerLevel(int32 InLevel);

	int32 GetPlayerLevel() const { return PlayerLevel; };
	
	UPROPERTY()
	TEnumAsByte<ESaveLoadStatus> LoadSlotStatus;
	
protected:

	//**field Notfies**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	FString LoadSlotName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	FString MapName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	int32 PlayerLevel;


};
