// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"
#include "Items/BaseItem.h"
#include "Zombies/BaseZombie.h"
#include "Village/House/House.h"
#include "StudentPerceptor_DelangheJorrit.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DELANGHEJORRITZOMBIERUNTIME_API UStudentPerceptor_DelangheJorrit : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStudentPerceptor_DelangheJorrit();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	const TArray<AHouse*>& GetObservedHouses() const {return ObservedHouses;}
	const TArray<ABaseZombie*>& GetObservedZombies() const {return  ObservedZombies;}
	const TArray<ABaseItem*>& GetObservedItems() const {return  ObservedItems;}
private:
	UPROPERTY()
	TArray<ABaseZombie*> ObservedZombies{};
	
	UPROPERTY()
	TArray<ABaseItem*> ObservedItems{};
	
	UPROPERTY()
	TArray<AHouse*> ObservedHouses{};
};
