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
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something!")));
	if (!Actor) return;
	CleanupZombies(); // so no endless list
	bool const bSensed = Stimulus.WasSuccessfullySensed();
	UE_LOG(LogTemp, Warning, TEXT("Perceived %s| sensed %s"), *Actor->GetName(), bSensed ? TEXT("Yes"):TEXT("NO"));
	
	if (ABaseZombie* Zombie = Cast<ABaseZombie>(Actor))
	{
		if (bSensed)
		{
			ObservedZombies.Add(Zombie);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Zombie!")));
		}
		else
		{
			ObservedZombies.Remove(Zombie);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Zombie not in view anymore!")));
		}
	}

	if (ABaseItem* Item = Cast<ABaseItem>(Actor))
	{
		if (bSensed)
		{
			ObservedItems.Add(Item);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw item!")));
		}
	}
	
	if (auto House = Cast<AHouse>(Actor))
	{
		if (bSensed)
		{
			ObservedHouses.Add(House);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw house!")));
		}
		else
		{
			ObservedHouses.Remove(House);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("house not in view anymore!")));
		}
	}
	
	if (auto PurgeZone = Cast<APurgeZone>(Actor))
	{
		if (bSensed)
		{
			ObservedPurgeZones.Add(PurgeZone);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw PurgeZone!")));
		}
		else
		{
			ObservedPurgeZones.Remove(PurgeZone);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("PurgeZone not in view anymore!")));
		}
	}

}

void UStudentPerceptor_DelangheJorrit::RemoveObservedItem(ABaseItem* item)
{
	ObservedItems.Remove(item);
}

void UStudentPerceptor_DelangheJorrit::CleanupZombies()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;

	const FVector MyLocation = OwnerPawn->GetActorLocation();
	constexpr float ForgetDistance = 2500.f;

	ObservedZombies.RemoveAll([&](ABaseZombie* Z)
	{
		return !IsValid(Z) || FVector::Dist(Z->GetActorLocation(), MyLocation) > ForgetDistance;
	});
}
