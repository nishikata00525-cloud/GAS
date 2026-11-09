// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GasCharacterBase.generated.h"

UCLASS()
class GAS_API AGasCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGasCharacterBase();
	
	// Ability System Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	class UBasicAttributeSet* BasicAttributeSet;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
	EGameplayEffectReplicationMode AscReplicationMode = EGameplayEffectReplicationMode::Mixed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual  UAbilitySystemComponent* GetAbilitySystemComponent() const override;

};
