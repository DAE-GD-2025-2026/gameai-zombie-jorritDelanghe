#include "BTTask_SetZombieAsTarget_DelangheJorrit.h"
#include "StudentPerceptor_DelangheJorrit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BTHelpers_DelangheJorrit.h"

UBTTask_SetZombieAsTarget_DelangheJorrit::UBTTask_SetZombieAsTarget_DelangheJorrit()
{
	NodeName = "Set Target Zombie";
}

EBTNodeResult::Type UBTTask_SetZombieAsTarget_DelangheJorrit::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
																	  uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;
	
	auto* Perceptor = Pawn->GetComponentByClass<UStudentPerceptor_DelangheJorrit>();
	if (!Perceptor) return EBTNodeResult::Failed;
	
	const auto& Zombies{Perceptor->GetObservedZombies()};
	if (Zombies.IsEmpty()) return EBTNodeResult::Failed;
	
	//look for nearest Item
	ABaseZombie* ClosestZombie{FindClosestActor(Zombies,Pawn->GetActorLocation())};
	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetZombieKey.SelectedKeyName,ClosestZombie);
	return EBTNodeResult::Succeeded;
}