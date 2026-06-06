#include "BTDecorator_IsLowHealth_DelangheJorrit.h"
#include "AIController.h"
#include "StudentPerceptor_DelangheJorrit.h"

UBTDecorator_IsLowHealth_DelangheJorrit::UBTDecorator_IsLowHealth_DelangheJorrit()
{
	NodeName = "Is low health" ;
}

bool UBTDecorator_IsLowHealth_DelangheJorrit::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
																					uint8* NodeMemory) const
{
	APawn* Pawn {OwnerComp.GetAIOwner()->GetPawn()};
	if (!Pawn) return false;
	
	auto* Health{Pawn->GetComponentByClass<UHealthComponent>()};
	if (!Health) return false;
	
	return Health->GetHealth()<= MinHealth;
}
