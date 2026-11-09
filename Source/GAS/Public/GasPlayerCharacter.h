// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GasCharacterBase.h"
#include "GasPlayerCharacter.generated.h"

class UInputAction;
struct FInputActionValue;

/**
 * Player-controlled GAS character.
 *
 * Only this layer knows about Enhanced Input. AI characters should derive from
 * AGasCharacterBase directly and trigger abilities through the ASC instead of
 * going through any input binding. Camera components stay in BP_GasPlayer.
 */
UCLASS()
class GAS_API AGasPlayerCharacter : public AGasCharacterBase
{
	GENERATED_BODY()

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MouseLookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Abilities")
	TObjectPtr<UInputAction> Ability1Action;

	/** Ability tag to activate when Ability1Action fires. Assign in BP_GasPlayer defaults. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Abilities")
	FGameplayTag Ability1Tag;

public:
	/** Player-facing helper. Move this to AGasCharacterBase once AI needs the same entry point. */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool ActivateAbilityByTag(FGameplayTag AbilityTag);

private:
	void OnMove(const FInputActionValue& Value);
	void OnLook(const FInputActionValue& Value);
	void OnAbility1(const FInputActionValue& Value);
};
