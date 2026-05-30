#include "BTTask_SetTarget_HouseDelangheJorrit.h"
#include "StudentPerceptor_DelangheJorrit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

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
	
	const auto& Houses{Perceptor->GetObservedHouses()};
	if (Houses.IsEmpty()) return EBTNodeResult::Failed;
	
	//look for nearest house
	float ClosestDistance{FLT_MAX};
	AHouse* ClosestHosue{nullptr};
	
	for (auto& House : Houses)
	{
		const float distance {static_cast<float>( FVector::Dist(Pawn->GetActorLocation(),House->GetActorLocation()))};
		
		if (distance < ClosestDistance)
		{
			ClosestDistance = distance;
			ClosestHosue = House;
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetHouseKey.SelectedKeyName,ClosestHosue);
	return EBTNodeResult::Succeeded;
}
