// Fill out your copyright notice in the Description page of Project Settings.


#include "ASJ_CharactersASFix.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/SkeletalMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AWWH_CharactersASFixCharacter

AASJ_CharactersASFix::AASJ_CharactersASFix()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AASJ_CharactersASFix::ClientInkShoot_Implementation()
{
	ServerInkShoot();
}

void AASJ_CharactersASFix::ServerInkShoot_Implementation()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FTransform FT = UKismetMathLibrary::MakeTransform(
		InkWeaponComponent->GetSocketLocation("Muzzle"),
		GetController()->GetControlRotation());

	InkAmmo = GetWorld()->SpawnActor<AActor>(*InkAmmoClass, InkWeaponComponent->GetSocketLocation("Muzzle"), GetController()->GetControlRotation());

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("ServerInkShoot !!"));
}

void AASJ_CharactersASFix::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	MarkerSpawn();
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void AASJ_CharactersASFix::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AASJ_CharactersASFix::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AASJ_CharactersASFix::Look);

		// Shoot
		EnhancedInputComponent->BindAction(InkShootAction, ETriggerEvent::Triggered, this, &AASJ_CharactersASFix::InkShoot);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AASJ_CharactersASFix::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AASJ_CharactersASFix::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AASJ_CharactersASFix::InkShoot(const FInputActionValue& Value)
{
	ClientInkShoot();
}

//void AASJ_CharactersASFix::MarkerSpawn()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("attach !!"));
//	
//	// 무기 "Actor" 추가
//	//InkWeapon = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
//
//	// 무기 "스켈레탈 매시 컴포넌트" 추가 및 "스켈레탈 메시" 지정
//	FTransform FT = UKismetMathLibrary::MakeTransform(FVector(0, 0, 0), FRotator(0, 0, 0), FVector(1, 1, 1));
//	//InkWeapon->AddComponent(FName("Weapon"), true, FT, false);
//
//	UActorComponent* WeaponComponent = AddComponent(TEXT("WeaponComponent"), true, FT, USkeletalMeshComponent::StaticClass());
//	//InkWeaponSKMeshComp->SetSkeletalMesh(WeaponComponent);
//
//	// 무기 컴포넌트를 최상위 
//	//InkWeaponSKMeshComp->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
//
//	// 캐릭터 매시의 특정 소켓에 부착
//	InkWeaponScene = Cast<USkeletalMeshComponent>(WeaponComponent);
//	InkWeaponScene->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket"));
//
//	//InkWeaponSKMeshComp->RegisterComponent();
//}


void AASJ_CharactersASFix::MarkerSpawn()
{
	// 스켈레탈 메시 컴포넌트를 생성하고 초기화
	InkWeaponComponent = NewObject<USkeletalMeshComponent>(this, *InkWeaponComponentClass);
	if (InkWeaponComponent)
	{
		InkWeaponComponent->RegisterComponent();	// 실제 생성

		// 스켈레탈 메시 설정
		// InkWeaponComponent->SetSkeletalMesh(InkWeaponMesh);

		// 특정 소켓에 부착
		InkWeaponComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create InkWeaponScene"));
	}
}
