// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainSoundWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_MasterVolume, float, m_MasterVolume);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_MusicVolume, float, m_MusicVolume);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_SFXVolume, float, m_SFXVolume);

/**
 * SoundWidget ���� �ٷ�� �� UserWidget Ŭ���� �Դϴ�.
 */
UCLASS()
class MAINSOUNDPLUGIN_API UMainSoundWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetVolume(float MasterVolume, float MusicVolume, float SFXVolume);

	// ======================= [ Event Dispatcher Function ]
	/**
	* ���޹��� �Ǽ��� ���� ��ü ������ �����մϴ�.
	* @param Volume ��ü ������ ������ ���� ũ�� ��
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SW_SetMasterVolume(float Volume);

	/**
	* ���޹��� �Ǽ��� ���� ��ü ������ �����մϴ�.
	* @param Volume ��ü ������ ������ ���� ũ�� ��
	*/
	void SW_SetMasterVolume_Implementation(float Volume);

	/**
	* ���޹��� �Ǽ��� ���� ���� ������ �����մϴ�.
	* @param Volume ���� ������ ������ ���� ũ�� ��
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SW_SetMusicVolume(float Volume);

	/**
	* ���޹��� �Ǽ��� ���� ���� ������ �����մϴ�.
	* @param Volume ���� ������ ������ ���� ũ�� ��
	*/
	void SW_SetMusicVolume_Implementation(float Volume);

	/**
	* ���޹��� �Ǽ��� ���� ȿ���� ������ �����մϴ�.
	* @param Volume ȿ���� ������ ������ ���� ũ�� ��
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SW_SetSFXVolume(float Volume);

	/**
	* ���޹��� �Ǽ��� ���� ȿ���� ������ �����մϴ�.
	* @param Volume ȿ���� ������ ������ ���� ũ�� ��
	*/
	void SW_SetSFXVolume_Implementation(float Volume);


	// ======================= [ Member Function ]
	/**
	* ���޹��� �Ǽ��� ������ �ּ�ġ�� �ִ�ġ�� ����� �ʰ� �����մϴ�.
	* @param Volume ������ �����ϰ��� �ϴ� ���� ��ġ
	* @return ���� ���� ���� ���, �Ǽ� ��
	*/
	float ValidateVolume(float Volume);


	// ======================= [ Delegate Property ]
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "sipal")
	float m_MasterVolume;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "sipal")
	float m_MusicVolume;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "sipal")
	float m_SFXVolume;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "sipal")
	FDele_MasterVolume m_Dele_MasterVolume;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "sipal")
	FDele_MusicVolume m_Dele_MusicVolume;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "sipal")
	FDele_SFXVolume m_Dele_SFXVolume;

protected:


private:

};
