// Fill out your copyright notice in the Description page of Project Settings.

#include "GasPlayerCharacter.h"

#include "GAS.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Controller.h"

void AGasPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogGAS, Error, TEXT("AGasPlayerCharacter: '%s' has no EnhancedInputComponent. Check DefaultInput.ini."), *GetNameSafe(this));
		return;
	}

	// Null checks keep this safe before the InputAction assets are assigned in the blueprint.
	if (MoveAction)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	}
	if (LookAction)
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
	}
	if (MouseLookAction)
	{
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
	}
	if (JumpAction)
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
	if (Ability1Action)
	{
		EnhancedInputComponent->BindAction(Ability1Action, ETriggerEvent::Started, this, &ThisClass::OnAbility1);
	}
}

void AGasPlayerCharacter::OnMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (GetController() == nullptr)
	{
		return;
	}

	const FRotator Rotation = GetController()->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), MovementVector.Y);
	AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), MovementVector.X);
}

void AGasPlayerCharacter::OnLook(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AGasPlayerCharacter::OnAbility1(const FInputActionValue&)
{
	ActivateAbilityByTag(Ability1Tag);
}

bool AGasPlayerCharacter::ActivateAbilityByTag(FGameplayTag AbilityTag)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (ASC == nullptr || !AbilityTag.IsValid())
	{
		return false;
	}

	FGameplayTagContainer AbilityTags;
	AbilityTags.AddTag(AbilityTag);
	return ASC->TryActivateAbilitiesByTag(AbilityTags);
}
