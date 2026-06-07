#include "BTTask_Wander_DelangheJorrit.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Wander_DelangheJorrit::UBTTask_Wander_DelangheJorrit()
{
	NodeName = "Wander around";
}

EBTNodeResult::Type UBTTask_Wander_DelangheJorrit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	constexpr float Radius{600.f};
	constexpr float ForwardDist{200.f};
	
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;
	
	// bias origin forward before picking random point
	const FVector Forward = Pawn->GetActorForwardVector();
	const FVector BiasedOrigin = Pawn->GetActorLocation() + Forward * ForwardDist;
	
	FNavLocation Location;
	UNavigationSystemV1::GetCurrent(GetWorld())->GetRandomReachablePointInRadius(
	BiasedOrigin
		,Radius
		,Location);
	
	const FVector RandomLocation{Location};
	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, RandomLocation);
	return EBTNodeResult::Succeeded;
}
