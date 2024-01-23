// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HomePlayerController.h"
#include "MainPlayerController.generated.h"

class ACharacter;
class USoundMix;
class USoundClass;
class UAudioComponent;
class UUserWidget;

/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API AMainPlayerController : public AHomePlayerController
{
	GENERATED_BODY()

public:
	AMainPlayerController();

	// ======================= [ Event Dispatcher Function ]
	/**
	* ���޹��� �Ǽ��� ���� ��ü ������ �����մϴ�.
	* @param Volume ��ü ������ ������ ���� ũ�� ��
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSetMasterVolume(float Volume);

	/**
	* ���޹��� �Ǽ��� ���� ��ü ������ �����մϴ�.
	* @param Volume ��ü ������ ������ ���� ũ�� ��
	*/
	virtual void OnSetMasterVolume_Implementation(float Volume);

	/**
	* ���޹��� �Ǽ��� ���� ���� ������ �����մϴ�.
	* @param Volume ���� ������ ������ ���� ũ�� ��
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSetMusicVolume(float Volume);

	/**
	* ���޹��� �Ǽ��� ���� ���� ������ �����մϴ�.
	* @param Volume ���� ������ ������ ���� ũ�� ��
	*/
	virtual void OnSetMusicVolume_Implementation(float Volume);

	/**
	* ���޹��� �Ǽ��� ���� ȿ���� ������ �����մϴ�.
	* @param Volume ȿ���� ������ ������ ���� ũ�� ��
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSetSFXVolume(float Volume);

	/**
	* ���޹��� �Ǽ��� ���� ȿ���� ������ �����մϴ�.
	* @param Volume ȿ���� ������ ������ ���� ũ�� ��
	*/
	virtual void OnSetSFXVolume_Implementation(float Volume);


protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	// ======================= [ Replication Function ]
	UFUNCTION(Client, Reliable)
	void ResClientPossess();


	// ======================= [ Member Function ]
	void InitializeAudio();

	void InitializeWidget();

	void ApplyMasterVolume(float Volume);

	void ApplyMusicVolume(float Volume);

	void ApplySFXVolume(float Volume);


	// ======================= [ Member Property ]
	// UI Property
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "UI")
	TSubclassOf<UUserWidget> HudWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "UI")
	TObjectPtr<UUserWidget> HudWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "UI")
	TSubclassOf<UUserWidget> SoundWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "UI")
	TObjectPtr<UUserWidget> SoundWidget;


	// Sound Class, Mix Property
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Sound")
	TObjectPtr<USoundMix> SoundMix;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Sound")
	TObjectPtr<USoundClass> SoundMusicClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Sound")
	TObjectPtr<USoundClass> SoundSFXClass;


	// UAudioComponent Property
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "AudioComponents")
	TObjectPtr<UAudioComponent> BackgroundMusic;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "AudioComponents")
	TObjectPtr<UAudioComponent> SampleSFX;

	FTimerHandle th_InitWidget;

};