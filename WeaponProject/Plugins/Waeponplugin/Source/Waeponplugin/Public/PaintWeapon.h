// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaintWeapon.generated.h"

UCLASS()
class WAEPONPLUGIN_API APaintWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UTP_APaintWeapon();

public:
	//�޽�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* WeaponMesh;
	//ĳ���� ����
	UPROPERTY(BlueprintReadWrite)
	ACharacter* m_pOwnchar;

	//������ƮŸ�� ����
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AweaeXProjectile> ProjectileClass;

	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	//AnimMontage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	//muzzle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	//mapping
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	//fire
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachWeapon(ThirdPersonCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EventShoot();

	virtual void EventShoot_Implementation() override;

	////////////// ����//////////////////////////////////////
public:
	UFUNCTION(Server, Reliable)
	void ReqShoot();







};
