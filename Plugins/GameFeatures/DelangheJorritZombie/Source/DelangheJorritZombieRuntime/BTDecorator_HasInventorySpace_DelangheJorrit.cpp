#include "BTDecorator_HasInventorySpace_DelangheJorrit.h"
#include "AIController.h"
#include "Common/InventoryComponent.h"

UBTDecorator_HasInventorySpace_DelangheJorrit::UBTDecorator_HasInventorySpace_DelangheJorrit()
{
	NodeName = "Has Inventory Space";
}

bool UBTDecorator_HasInventorySpace_DelangheJorrit::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	APawn* Pawn{OwnerComp.GetAIOwner()->GetPawn()};
	if (!Pawn) return false;

	auto* Inventory{Pawn->GetComponentByClass<UInventoryComponent>()};
	if (!Inventory) return false;

	for (int i{}; i < Inventory->GetInventoryCapacity(); ++i)
	{
		if (!Inventory->GetInventory()[i])
			return true; // found empty slot
	}
	return false;
}


