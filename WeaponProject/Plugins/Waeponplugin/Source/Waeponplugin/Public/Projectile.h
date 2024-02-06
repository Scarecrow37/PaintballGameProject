// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config = Game)
class Projectile : public AActor
{
	GENERATED_BODY()

public:
	//�ݸ��� ����
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;

	//�����Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MyProjectile")
	TObjectPtr<UStaticMeshComponent> Sphere;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Brush")
	TObjectPtr<UTexture2D> Brushtexture;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Brush")
	double Brushsize;

public:
	Projectile();

	//�� �̺�Ʈ
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//�浹ü �����
	USphereComponent* GetCollisionComp() const { return CollisionComp; }

	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

