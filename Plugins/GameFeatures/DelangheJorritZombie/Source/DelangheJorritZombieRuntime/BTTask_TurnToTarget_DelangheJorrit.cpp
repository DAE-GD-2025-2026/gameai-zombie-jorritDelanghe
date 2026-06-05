#include "BTTask_TurnToTarget_DelangheJorrit.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget_DelangheJorrit::UBTTask_TurnToTarget_DelangheJorrit()
{
	NodeName = "Turn to Target";
}

EBTNodeResult::Type UBTTask_TurnToTarget_DelangheJorrit::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;
	
	//read the target from the blackBoardkey
	UBlackboardComponent* blackBoardComponent {OwnerComp.GetBlackboardComponent()};
	AActor* Target{Cast<AActor>(blackBoardComponent->GetValueAsObject(GetSelectedBlackboardKey()))};
	if (!Target) return EBTNodeResult::Failed;
	
	const FVector Direction = (Target->GetActorLocation() - Pawn->GetActorLocation()).GetSafeNormal();
	Pawn->SetActorRotation(Direction.ToOrientationRotator());
	
	return EBTNodeResult::Succeeded;
}
