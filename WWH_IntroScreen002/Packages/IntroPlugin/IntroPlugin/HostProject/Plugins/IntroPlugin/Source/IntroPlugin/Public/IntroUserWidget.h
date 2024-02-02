// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Delegates/DelegateCombinations.h"
#include "Blueprint/UserWidget.h"
#include "MediaPlayer.h"
#include "IntroUserWidget.generated.h"

class UMediaPlayer;
class UMediaSource;
/**
 *��Ʈ�� ȭ�� ����
 */
UCLASS()
class UIntroUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	*On End Reached(BP)�� ���ε� �� ���·� ����Ǵ� Event.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "[Custom]VideoOptions")
	void OnVideoEnd();

	void OnVideoEnd_Implementation();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "[Custom]VideoOptions")
	TObjectPtr<UMediaPlayer> IntroMediaPlayer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "[Custom]VideoOptions")
	TObjectPtr<UMediaSource> IntroMediaSource;

private:
};
