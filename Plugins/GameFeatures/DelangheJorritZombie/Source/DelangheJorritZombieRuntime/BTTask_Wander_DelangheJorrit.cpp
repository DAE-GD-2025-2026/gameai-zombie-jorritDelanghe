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
	constexpr float radius{500.f};
	APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!pawn) return EBTNodeResult::Failed;
	
	FNavLocation location;
	UNavigationSystemV1::GetCurrent(GetWorld())->GetRandomReachablePointInRadius(
		pawn->GetActorLocation()
		,radius
		,location);
	
	const FVector randomLocation{location};
	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, randomLocation);
	return EBTNodeResult::Succeeded;
}
