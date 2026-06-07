// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptor_DelangheJorrit.h"


UStudentPerceptor_DelangheJorrit::UStudentPerceptor_DelangheJorrit()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStudentPerceptor_DelangheJorrit::BeginPlay()
{
	Super::BeginPlay();
	
	//get pawn
	auto OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find ownerPawn"));
		return;
	}
	//ai controller of pawn
	auto AiController = OwnerPawn->GetController();
	if (!AiController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find AiController"));
	}
	//find AI perceptionComponent
	if (auto PerceptionComp = OwnerPawn->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptor_DelangheJorrit::OnPerceptionUpdated);
		UE_LOG(LogTemp, Warning, TEXT("StudentPerceptor: Successfully bound to perception!"));
	}

}

void UStudentPerceptor_DelangheJorrit::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor) return;
	
	bool const bSensed = Stimulus.WasSuccessfullySensed();
	UE_LOG(LogTemp, Warning, TEXT("Perceived %s| sensed %s"), *Actor->GetName(), bSensed ? TEXT("Yes"):TEXT("NO"));
	
	if (ABaseZombie* Zombie = Cast<ABaseZombie>(Actor))
	{
		if (bSensed)
		{
			ObservedZombies.AddUnique(Zombie);;
		}
	}
	
	if (ABaseItem* Item = Cast<ABaseItem>(Actor))
	{
		if (bSensed)
		{
			ObservedItems.Add(Item);
		}
	}
	
	if (auto House = Cast<AHouse>(Actor))
	{
		if (bSensed)
		{
			ObservedHouses.Add(House);
		}
		else
		{
			ObservedHouses.Remove(House);
		}
	}
	
	if (auto PurgeZone = Cast<APurgeZone>(Actor))
	{
		if (bSensed)
		{
			ObservedPurgeZones.Add(PurgeZone);
		}
		else
		{
			ObservedPurgeZones.Remove(PurgeZone);
		}
	}

}

void UStudentPerceptor_DelangheJorrit::RemoveObservedItem(ABaseItem* item)
{
	ObservedItems.Remove(item);
}
