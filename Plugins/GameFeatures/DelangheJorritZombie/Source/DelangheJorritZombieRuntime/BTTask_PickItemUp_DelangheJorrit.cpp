#include "BTTask_PickItemUp_DelangheJorrit.h"

#include "AIController.h"
#include "StudentPerceptor_DelangheJorrit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Common/InventoryComponent.h"
#include "Items/BaseItem.h"

class UStudentPerceptor_DelangheJorrit;

UBTTask_PickItemUp_DelangheJorrit::UBTTask_PickItemUp_DelangheJorrit()
{
	NodeName="Grab item";
}

EBTNodeResult::Type UBTTask_PickItemUp_DelangheJorrit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn{OwnerComp.GetAIOwner()->GetPawn()};
	if (!Pawn) return EBTNodeResult::Failed;
	
	ABaseItem* Item {Cast<ABaseItem>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject(
			TargetItemKey.SelectedKeyName))} ;
	
	if (!Item) return EBTNodeResult::Failed;
	
	auto* Inventory{Pawn->GetComponentByClass<UInventoryComponent>()};
	if (!Inventory) return EBTNodeResult::Failed;
	
	for (int i{}; i<Inventory->GetInventoryCapacity();++i)
	{
		if (Inventory->GrabItem(i,Item))
		{
			// Tell the perceptor this item is gone
			if (auto* Perceptor{Pawn->GetComponentByClass<UStudentPerceptor_DelangheJorrit>()})
			{
				Perceptor->RemoveObservedItem(Item);
			}
			OwnerComp.GetBlackboardComponent()->ClearValue(TargetItemKey.SelectedKeyName);
			return EBTNodeResult::Succeeded;
		}
	}
	//prevent stuck loop
	if (auto* Perceptor{Pawn->GetComponentByClass<UStudentPerceptor_DelangheJorrit>()})
	{
		Perceptor->RemoveObservedItem(Item); // ADD THIS
	}
	OwnerComp.GetBlackboardComponent()->ClearValue(TargetItemKey.SelectedKeyName);
	return EBTNodeResult::Failed;
}
