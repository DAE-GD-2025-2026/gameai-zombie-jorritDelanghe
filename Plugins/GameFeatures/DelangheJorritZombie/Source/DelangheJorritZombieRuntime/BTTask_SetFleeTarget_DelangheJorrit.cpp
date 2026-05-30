#include "BTTask_SetFleeTarget_DelangheJorrit.h"

#include "AIController.h"
#include "StudentPerceptor_DelangheJorrit.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetFleeTarget_DelangheJorrit::UBTTask_SetFleeTarget_DelangheJorrit()
{
	NodeName = "Set Target To Flee";
}

EBTNodeResult::Type UBTTask_SetFleeTarget_DelangheJorrit::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;
	
	auto* perceptor{Pawn->GetComponentByClass<UStudentPerceptor_DelangheJorrit>()};
	if (!perceptor) return EBTNodeResult::Failed;
	
	const auto& zombies{perceptor->GetObservedZombies()};
	if (zombies.IsEmpty()) return EBTNodeResult::Failed;
	
	//find nearest zombie
	float closestDistance{FLT_MAX};
	ABaseZombie* closestZombie{nullptr};
	
	for (auto& zombie : zombies)
	{
		const float distance {static_cast<float>( FVector::Dist(Pawn->GetActorLocation(),zombie->GetActorLocation()))};
		
		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestZombie = zombie;
		}
	}
	//flee from nearest zombie
	constexpr float distanceAway{500.f};
	const FVector fleeDirection{(Pawn->GetActorLocation()-closestZombie->GetActorLocation()).GetSafeNormal()};
	const FVector fleeLocation{Pawn->GetActorLocation() + fleeDirection* distanceAway};
	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetFleeLocation.SelectedKeyName,fleeLocation);
	return EBTNodeResult::Succeeded;
}
