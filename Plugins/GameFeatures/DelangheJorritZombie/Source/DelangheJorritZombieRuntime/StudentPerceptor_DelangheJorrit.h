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
	
	const TArray<AHouse*>& GetPerceivedHouses() const {return PerceivedHouses;}
private:
	UPROPERTY()
	TArray<ABaseZombie*> PerceivedZombies{};
	
	UPROPERTY()
	TArray<ABaseItem*> PerceivedItems{};
	
	UPROPERTY()
	TArray<AHouse*> PerceivedHouses{};
};
