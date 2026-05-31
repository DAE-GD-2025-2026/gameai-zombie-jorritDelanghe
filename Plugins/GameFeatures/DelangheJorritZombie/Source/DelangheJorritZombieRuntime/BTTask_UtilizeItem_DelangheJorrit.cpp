#include "BTTask_UtilizeItem_DelangheJorrit.h"

#include "AIController.h"
#include "Common/InventoryComponent.h"
#include "Items/Medkit.h"

UBTTask_UtilizeItem_DelangheJorrit::UBTTask_UtilizeItem_DelangheJorrit()
{
	NodeName = "Use Items in inventory";
}

EBTNodeResult::Type UBTTask_UtilizeItem_DelangheJorrit::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	APawn* Pawn {OwnerComp.GetAIOwner()->GetPawn()};
	if (!Pawn) return EBTNodeResult::Failed;
	
	constexpr int MinCapacity{1};
	auto* Inventory{Pawn->GetComponentByClass<UInventoryComponent>()};
	if (!Inventory) return EBTNodeResult::Failed;
	if (Inventory->GetInventoryCapacity()<MinCapacity) return EBTNodeResult::Failed;
	
	auto* HealthComp{Pawn->GetComponentByClass<UHealthComponent>()};
	auto* StaminaComp{Pawn->GetComponentByClass<UStaminaComponent>()};
	
	constexpr int MinHealthForHeal{6};
	constexpr int MinStaminaForBoost{6};
	for (int i{};i<Inventory->GetInventoryCapacity();++i)
	{
		const ABaseItem* item {Inventory->GetInventory()[i]};
		if (!item) return EBTNodeResult::Failed;
		
		if (item->GetItemType() == EItemType::Medkit && HealthComp->GetHealth()<MinHealthForHeal)
		{
			Inventory->UseItem(i);
			return EBTNodeResult::Succeeded;
		}
		if (item->GetItemType() == EItemType::Food && StaminaComp->GetCurrentStamina()<MinStaminaForBoost)
		{
			Inventory->UseItem(i);
			return EBTNodeResult::Succeeded;
		}
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
