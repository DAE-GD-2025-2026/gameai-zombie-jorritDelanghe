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
#include "PurgeZones/PurgeZone.h"
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
	
	//house
	void MarkHouseVisited(AHouse* House) { VisitedHouses.Add(House); }
	void ClearVisitedHouses() {VisitedHouses.Empty();}
	const TArray<AHouse*>& GetObservedHouses() const {return ObservedHouses;}
	const TArray<AHouse*>& GetVisitedHouses() const {return VisitedHouses;}
	
	 TArray<ABaseZombie*>& GetObservedZombies() {return  ObservedZombies;}
	const TArray<ABaseItem*>& GetObservedItems() const {return  ObservedItems;}
	const TArray<APurgeZone*>& GetObservedPurgeZones() const {return  ObservedPurgeZones;}
	
	void RemoveObservedItem(ABaseItem* item);
private:
	UPROPERTY()
	TArray<ABaseZombie*> ObservedZombies{};
	
	UPROPERTY()
	TArray<ABaseItem*> ObservedItems{};
	
	UPROPERTY()
	TArray<AHouse*> ObservedHouses{};
	
	UPROPERTY()
	TArray<AHouse*> VisitedHouses{};
	
	UPROPERTY()
	TArray<APurgeZone*> ObservedPurgeZones{};
	
	void CleanupZombies();
};
