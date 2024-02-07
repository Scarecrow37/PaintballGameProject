// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuthorizationPanel.h"
#include "LoginPanel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLoginRequestEvent, const FText&, ID, const FText&, Password);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenCreateAccountPanelRequestEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenNextLevelRequestEevent);

/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API ULoginPanel : public UAuthorizationPanel
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnLoginRequestEvent OnLoginRequested;
	
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnOpenCreateAccountPanelRequestEvent OnOpenCreateAccountPanelRequested;
	
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnOpenNextLevelRequestEevent OnOpenNextLevelRequested;

	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWIdget))
	TObjectPtr<UButton> CreateAccountButton;
	
	virtual void NativePreConstruct() override;

private:
	virtual void BindConfirmClicked() override;

	virtual void BindCloseSuccessMessage() override;
	
	virtual void BindCloseFailMessage() override;

	UFUNCTION()
	void BindCreateAccountClicked();
};
