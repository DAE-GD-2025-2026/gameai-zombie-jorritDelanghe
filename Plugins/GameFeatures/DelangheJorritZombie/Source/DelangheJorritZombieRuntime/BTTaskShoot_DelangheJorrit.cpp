#include "BTTaskShoot_DelangheJorrit.h"
#include "AIController.h"

#include "Common/InventoryComponent.h"
#include "StudentPerceptor_DelangheJorrit.h"

UBTTaskShoot_DelangheJorrit::UBTTaskShoot_DelangheJorrit()
{
	NodeName = "Shoot gun or shotgun";
}

EBTNodeResult::Type UBTTaskShoot_DelangheJorrit::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
                                                             uint8* NodeMemory)
{
	APawn* Pawn {OwnerComp.GetAIOwner()->GetPawn()};
	if (!Pawn) return EBTNodeResult::Failed;
	
	auto* Perceptor{Pawn->GetComponentByClass<UStudentPerceptor_DelangheJorrit>()};
	if (!Perceptor) return EBTNodeResult::Failed;
	
	constexpr int MinCapacity{1};
	auto* Inventory{Pawn->GetComponentByClass<UInventoryComponent>()};
	if (!Inventory) return EBTNodeResult::Failed;
	if (Inventory->GetInventoryCapacity()<MinCapacity) return EBTNodeResult::Failed;
	
	for (int index{}; index<Inventory->GetInventoryCapacity(); ++index)
	{
		auto* Item {Inventory->GetInventory()[index]};
		if (!Item) continue;
		
		EItemType ItemType {Item->GetItemType()};
		
		//check is pistol, then have bulelts, then shoot
		if (ItemType==EItemType::Pistol || ItemType == EItemType::Shotgun)
		{
			if (Item->GetValue() > 0)
			{
				Inventory->UseItem(index);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
