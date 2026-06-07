#include "BTDecorator_HasWeapon_DelangheJorrit.h"
#include "AIController.h"
#include  "Common/InventoryComponent.h"


UBTDecorator_HasWeapon_DelangheJorrit::UBTDecorator_HasWeapon_DelangheJorrit()
{
	NodeName = "Has Weapon";
}

bool UBTDecorator_HasWeapon_DelangheJorrit::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* Pawn{OwnerComp.GetAIOwner()->GetPawn()};
	if (!Pawn) return false;

	auto* Inventory{Pawn->GetComponentByClass<UInventoryComponent>()};
	if (!Inventory) return false;

	for (int i{}; i < Inventory->GetInventoryCapacity(); ++i)
	{
		//null check
		auto* Item = Inventory->GetInventory()[i];
		if (!Item) continue;
		
		//look for gun
		if (Inventory->GetInventory()[i]->GetItemType() == EItemType::Pistol
			|| Inventory->GetInventory()[i]->GetItemType() == EItemType::Shotgun)
			return true; 
	}
	return false;
}
