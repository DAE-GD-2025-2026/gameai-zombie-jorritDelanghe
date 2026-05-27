// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptor.h"


UStudentPerceptor::UStudentPerceptor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStudentPerceptor::BeginPlay()
{
	Super::BeginPlay();
	
	//get pawn
	auto ownerPawn = Cast<APawn>(GetOwner());
	if (!ownerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find ownerPawn"));
		return;
	}
	//ai controller of pawn
	auto AiController = ownerPawn->GetController();
	if (!AiController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find AiController"));
	}
	//find AI perceptionComponent
	if (auto PerceptionComp = ownerPawn->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptor::OnPerceptionUpdated);
		UE_LOG(LogTemp, Warning, TEXT("StudentPerceptor: Successfully bound to perception!"));
	}

}

void UStudentPerceptor::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something!")));
	if (!Actor) return;
	
	bool const sensed = Stimulus.WasSuccessfullySensed();
	UE_LOG(LogTemp, Warning, TEXT("Perceived %s| sensed %s"), *Actor->GetName(), sensed ? TEXT("Yes"):TEXT("NO"));
	
	if (ABaseZombie* zombie = Cast<ABaseZombie>(Actor))
	{
		if (sensed)
		{
			PerceivedZombies.Add(zombie);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Zombie!")));
		}
		else
		{
			PerceivedZombies.Remove(zombie);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Zombie not in view anymore!")));
		}
	}
	
	if (ABaseItem* item = Cast<ABaseItem>(Actor))
	{
		if (sensed)
		{
			PerceivedItems.Add(item);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw item!")));
		}
		else
		{
			PerceivedItems.Remove(item);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("item not in view anymore!")));
		}
	}
	
	if (auto house = Cast<AHouse>(Actor))
	{
		if (sensed)
		{
			PerceivedHouses.Add(house);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw house!")));
		}
		else
		{
			PerceivedHouses.Remove(house);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("house not in view anymore!")));
		}
	}

}
