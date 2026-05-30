#include "BTTask_SetTarget_HouseDelangheJorrit.h"
#include "StudentPerceptor_DelangheJorrit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BTHelpers_DelangheJorrit.h"

UBTTask_SetTarget_HouseDelangheJorrit::UBTTask_SetTarget_HouseDelangheJorrit()
{
	NodeName= "Set Target House"; //helps display editor
}

EBTNodeResult::Type UBTTask_SetTarget_HouseDelangheJorrit::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
                                                                       uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;
	
	auto* Perceptor = Pawn->GetComponentByClass<UStudentPerceptor_DelangheJorrit>();
	if (!Perceptor) return EBTNodeResult::Failed;
	
	const auto& houses{Perceptor->GetObservedHouses()};
	if (houses.IsEmpty()) return EBTNodeResult::Failed;
	
	//look for nearest house
	AHouse* closestHouse{FindClosestActor(houses,Pawn->GetActorLocation())};
	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetHouseKey.SelectedKeyName,closestHouse);
	return EBTNodeResult::Succeeded;
}
