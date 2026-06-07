#include "BTTask_SetFleeTarget_DelangheJorrit.h"

#include "AIController.h"
#include "StudentPerceptor_DelangheJorrit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTHelpers_DelangheJorrit.h"

UBTTask_SetFleeTarget_DelangheJorrit::UBTTask_SetFleeTarget_DelangheJorrit()
{
	NodeName = "Set Target To Flee";
}

EBTNodeResult::Type UBTTask_SetFleeTarget_DelangheJorrit::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;
	
	auto* Perceptor{Pawn->GetComponentByClass<UStudentPerceptor_DelangheJorrit>()};
	if (!Perceptor) return EBTNodeResult::Failed;
	
	const auto& Zombies{Perceptor->GetObservedZombies()};
	const auto& PurgeZones{Perceptor->GetObservedPurgeZones()};
	if (Zombies.IsEmpty() && PurgeZones.IsEmpty()) return EBTNodeResult::Failed;
	
	//find nearest threat
	ABaseZombie* ClosestZombie{FindClosestActor(Zombies, Pawn->GetActorLocation())};
	APurgeZone* ClosestPurgeZone{FindClosestActor(PurgeZones, Pawn->GetActorLocation())};
	
	//compare distance threats
	const FVector ActorLocation{Pawn->GetActorLocation()};
	AActor* ClosestThreat{nullptr};
	if (ClosestZombie&& ClosestPurgeZone)
	{
		const float ZombieDist{static_cast<float>(FVector::Dist(ClosestZombie->GetActorLocation(),ActorLocation))};
		const float PurgeZonesDist{static_cast<float>(FVector::Dist(ClosestPurgeZone->GetActorLocation(),ActorLocation))};
		ClosestThreat = ZombieDist<=PurgeZonesDist ? Cast<AActor>(ClosestZombie) : Cast<AActor>(ClosestPurgeZone); //no object slicing because pointer
	}
	else
	{
		ClosestThreat = ClosestZombie? Cast<AActor>(ClosestZombie) : Cast<AActor>(ClosestPurgeZone);
	}
	
	//flee from nearest threat
	constexpr float DistanceAway{1500.f};
	const FVector FleeDirection{(ActorLocation-ClosestThreat->GetActorLocation()).GetSafeNormal()};
	const FVector FleeLocation{ActorLocation + FleeDirection* DistanceAway};
	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetFleeLocation.SelectedKeyName,FleeLocation);
	return EBTNodeResult::Succeeded;
}
