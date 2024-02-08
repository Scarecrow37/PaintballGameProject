// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainSoundInterface.h"
#include "GameFramework/PlayerState.h"
#include "InGamePlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInGameUserName, const FString&, UserName);

/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API AInGamePlayerState : public APlayerState, public IMainSoundInterface
{
	GENERATED_BODY()

public:
	AInGamePlayerState();

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	void SetUserName(const FString UserName);

	void UpdateBind();

public:
	UFUNCTION()
	void OnRep_InGameUserName();

	UFUNCTION(BlueprintPure)
	FString GetStrUserName() { return InGameUserName; };

public:
	UPROPERTY(ReplicatedUsing = OnRep_InGameUserName)
	FString InGameUserName;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FInGameUserName OnSetUserName;

	FTimerHandle th_UpdateBind;



	//======================================================
	//=================== ���� ó�� ���� ===================
	//======================================================
public:
	/**
	* ������ ���� ��ü ������ ��ġ�� �����ɴϴ�.
	* @return ���� ��ü ���� ��ġ �Ǽ� ��
	*/
	float GetMasterVolume();

	/**
	* ������ ���� ���� ������ ��ġ�� �����ɴϴ�.
	* @return ���� ���� ���� ��ġ �Ǽ� ��
	*/
	float GetMusicVolume();

	/**
	* ������ ���� ȿ���� ������ ��ġ�� �����ɴϴ�.
	* @return ���� ȿ���� ���� ��ġ �Ǽ� ��
	*/
	float GetSFXVolume();

	/**
	* ������ ��ü ���� ��ġ�� �����մϴ�.
	* @return ������ ��ü ���� ��ġ �Ǽ� ��
	*/
	void SetMasterVolume(float Volume);

	/**
	* ������ ���� ���� ��ġ�� �����մϴ�.
	* @return ������ ���� ���� ��ġ �Ǽ� ��
	*/
	void SetMusicVolume(float Volume);

	/**
	* ������ ȿ���� ���� ��ġ�� �����մϴ�.
	* @return ������ ȿ���� ���� ��ġ �Ǽ� ��
	*/
	void SetSFXVolume(float Volume);


private:
	// ======================= [ Member Function ]
	float ValidateVolume(float Volume);


	// ======================= [ Member Property ]
	// Sound Property
	UPROPERTY(VisibleAnywhere, Category = "Volume")
	float MasterVolume;

	UPROPERTY(VisibleAnywhere, Category = "Volume")
	float MusicVolume;

	UPROPERTY(VisibleAnywhere, Category = "Volume")
	float SFXVolume;

};