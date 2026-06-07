#include "BTTask_Shoot_DelangheJorrit.h"
#include "AIController.h"

#include "Common/InventoryComponent.h"
#include "StudentPerceptor_DelangheJorrit.h"

UBTTask_Shoot_DelangheJorrit::UBTTask_Shoot_DelangheJorrit()
{
	NodeName = "Shoot gun or shotgun";
}

EBTNodeResult::Type UBTTask_Shoot_DelangheJorrit::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
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
				GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
		  FString::Printf(TEXT("Shoot")));
				Inventory->UseItem(index);
				if (Item->GetValue()<=0)
				{
					Inventory->RemoveItem(index);
				}
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
