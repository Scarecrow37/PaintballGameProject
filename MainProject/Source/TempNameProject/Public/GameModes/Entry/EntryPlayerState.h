// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "EntryPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEntryUserName, const FString&, UserName);

/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API AEntryPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AEntryPlayerState();

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	void SetUserName(const FString NewUserName);

	void UpdateBind();

public:
	UFUNCTION()
	void OnRep_EntryUserName();

	UFUNCTION(BlueprintPure)
	FString GetStrUserName() { return EntryUserName; };

public:
	UPROPERTY(ReplicatedUsing = OnRep_EntryUserName)
	FString EntryUserName;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FEntryUserName OnSetUserName;

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
