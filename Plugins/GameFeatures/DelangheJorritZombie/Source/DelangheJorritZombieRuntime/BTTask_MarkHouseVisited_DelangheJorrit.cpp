#include "BTTask_MarkHouseVisited_DelangheJorrit.h"
#include "AIController.h"
#include "StudentPerceptor_DelangheJorrit.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MarkHouseVisited_DelangheJorrit::UBTTask_MarkHouseVisited_DelangheJorrit()
{
	NodeName = "Mark House Visited";
}

EBTNodeResult::Type UBTTask_MarkHouseVisited_DelangheJorrit::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	auto* Perceptor = Pawn->GetComponentByClass<UStudentPerceptor_DelangheJorrit>();
	if (!Perceptor) return EBTNodeResult::Failed;
	
	if (AHouse* CurrentHouse = Cast<AHouse>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetHouse"))))
	{
		Perceptor->MarkHouseVisited(CurrentHouse);
	}
	return EBTNodeResult::Succeeded;
}
