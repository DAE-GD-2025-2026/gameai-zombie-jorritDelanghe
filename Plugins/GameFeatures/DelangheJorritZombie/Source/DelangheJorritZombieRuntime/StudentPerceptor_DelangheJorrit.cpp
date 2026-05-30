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
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptor_DelangheJorrit::OnPerceptionUpdated);
		UE_LOG(LogTemp, Warning, TEXT("StudentPerceptor: Successfully bound to perception!"));
	}

}

void UStudentPerceptor_DelangheJorrit::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
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
			ObservedZombies.Add(zombie);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Zombie!")));
		}
		else
		{
			ObservedZombies.Remove(zombie);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Zombie not in view anymore!")));
		}
	}
	
	if (ABaseItem* item = Cast<ABaseItem>(Actor))
	{
		if (sensed)
		{
			ObservedItems.Add(item);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw item!")));
		}
		else
		{
			ObservedItems.Remove(item);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("item not in view anymore!")));
		}
	}
	
	if (auto house = Cast<AHouse>(Actor))
	{
		if (sensed)
		{
			ObservedHouses.Add(house);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw house!")));
		}
		else
		{
			ObservedHouses.Remove(house);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("house not in view anymore!")));
		}
	}

}
