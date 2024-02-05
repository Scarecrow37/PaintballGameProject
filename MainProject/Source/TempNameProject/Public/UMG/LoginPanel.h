// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginPanel.generated.h"

class UButton;
class ULabeledInput;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLoginButtonClickedEvent, const FText&, ID, const FText&, Password);

/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API ULoginPanel : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnLoginButtonClickedEvent OnLoginRequested;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	TObjectPtr<ULabeledInput> IdWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	TObjectPtr<ULabeledInput> PasswordWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	TObjectPtr<UButton> LoginButton;
	
	virtual void NativePreConstruct() override;

private:
	UFUNCTION()
	void BindLoginClicked();

	bool BoundLogin;
};
