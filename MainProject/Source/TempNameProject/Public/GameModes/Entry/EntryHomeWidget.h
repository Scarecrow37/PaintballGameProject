// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EntryHomeWidget.generated.h"

class UMediaSource;
class UMediaPlayer;

/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API UEntryHomeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UUserWidget* GetEntrySoundWidget();

private:
	UFUNCTION()
	bool EntrySoundISVisible();

	UFUNCTION(BlueprintCallable)
	void ToggleVisibleWidget();

protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> EntrySoundWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMediaPlayer> HomeLevelBackgroundPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMediaSource> HomeLevelBackgroundSource;
};
