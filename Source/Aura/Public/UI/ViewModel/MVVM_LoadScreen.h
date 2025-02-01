// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadScreen.generated.h"

class UMVVM_LoadSlot;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlotSelectedSignature);
UCLASS()
class AURA_API UMVVM_LoadScreen : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FSlotSelectedSignature SlotSelectedDelegate;
	
	void InitializeLoadSlots();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadSlot> LoadSlotViewModelClass;

	UFUNCTION(BlueprintPure)
	UMVVM_LoadSlot* GetLoadSlotViewModelByIndex(const int32 Index) const;

	UFUNCTION(BlueprintCallable)
	void NewGameButtonPressed(const int32 Slot);
	
	UFUNCTION(BlueprintCallable)
	void NewSlotButtonPressed(const int32 Slot,const FString& EnteredName);

	UFUNCTION(BlueprintCallable)
	void SelectSlotButtonPressed(const int32 Slot);

	UFUNCTION(BlueprintCallable)
	void DeleteButtonPressed();
	
	void LoadData();
	
private:

	UPROPERTY()
	int32 CurrentSlot;
	
	UPROPERTY()
	TMap<int32,UMVVM_LoadSlot*> LoadSlots;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_0;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_1;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_2;
};
