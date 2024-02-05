// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainSoundInterface.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"


/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API AMainPlayerState : public APlayerState, public IMainSoundInterface
{
	GENERATED_BODY()

public:
	AMainPlayerState();

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

protected:
	virtual void BeginPlay() override;

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