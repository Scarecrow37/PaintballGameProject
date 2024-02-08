// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EntryPlayerController.generated.h"

class ACharacter;
class USoundMix;
class USoundClass;
class UAudioComponent;
class UUserWidget;
class UChatWidget;
class ULobbyRoomUserWidget;

/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API AEntryPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	//======================================================
//==================== ���� ó�� ���� ====================
//======================================================
public:
	AEntryPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION(Client, Reliable)
	void ResponseClientPossess();



	//======================================================
	//=================== ���� ó�� ���� ===================
	//======================================================
public:
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

private:
	// ======================= [ Member Function ]
	void InitializeAudio();

	void InitializeWidget();

	void ApplyMasterVolume(float Volume);

	void ApplyMusicVolume(float Volume);

	void ApplySFXVolume(float Volume);


	// ======================= [ Member Property ]
	// UI Property
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
	TObjectPtr<UAudioComponent> BackgroundMusicComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "AudioComponents")
	TObjectPtr<UAudioComponent> SFXComponent;



	//======================================================
	//=============== �÷��̾� �г��� ���� ���� ===============
	//======================================================
public:
	UFUNCTION(Server, Reliable)
	void RequestChangeUserName(const FString& NewName);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void RequestUpdateUserList();

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void ResponseUpdateUserList();


	//======================================================
	void BindPlayerState(class AEntryPlayerState* EntryPlayerState);

	void UpdateUserName();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateUserName(const FString& UserName);

	void OnUpdateUserName_Implementation(const FString& UserName);


	//======================================================
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> EntryWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TObjectPtr<UUserWidget> EntryWidget;

	FTimerHandle th_RequestUserName;

	FTimerHandle th_BindPlayerState;
};
