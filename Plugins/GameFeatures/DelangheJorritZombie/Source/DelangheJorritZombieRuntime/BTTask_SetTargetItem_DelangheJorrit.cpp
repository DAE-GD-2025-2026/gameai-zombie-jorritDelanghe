#include "BTTask_SetTargetItem_DelangheJorrit.h"
#include "StudentPerceptor_DelangheJorrit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BTHelpers_DelangheJorrit.h"

UBTTask_SetTargetItem_DelangheJorrit::UBTTask_SetTargetItem_DelangheJorrit()
{
	NodeName = "Set Target Item";
}

EBTNodeResult::Type UBTTask_SetTargetItem_DelangheJorrit::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
                                                                      uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;
	
	auto* Perceptor = Pawn->GetComponentByClass<UStudentPerceptor_DelangheJorrit>();
	if (!Perceptor) return EBTNodeResult::Failed;
	
	OwnerComp.GetBlackboardComponent()->ClearValue(TargetItemKey.SelectedKeyName);
	
	//filter trough only the useful items, no garbage
	const auto& Items{Perceptor->GetObservedItems()};
	TArray <ABaseItem*> UsefulItems;
	
	for (auto Item : Items)
	{
		if (IsValid(Item) && Item->GetItemType() != EItemType::Garbage)
		{
			UsefulItems.Add(Item);
		}
		else if (!IsValid(Item))
		{
			Perceptor->RemoveObservedItem(Item);
		}
	}
	if (UsefulItems.IsEmpty()) return EBTNodeResult::Failed;
	
	//look for nearest Item
	ABaseItem* ClosestItem{FindClosestActor(UsefulItems,Pawn->GetActorLocation())};
	if (!ClosestItem) return EBTNodeResult::Failed;
	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetItemKey.SelectedKeyName, ClosestItem);
	return EBTNodeResult::Succeeded;
}
