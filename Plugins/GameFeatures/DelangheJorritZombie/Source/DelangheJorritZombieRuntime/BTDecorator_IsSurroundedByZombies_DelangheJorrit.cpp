#include "BTDecorator_IsSurroundedByZombies_DelangheJorrit.h"
#include "AIController.h"
#include "StudentPerceptor_DelangheJorrit.h"

UBTDecorator_IsSurroundedByZombies_DelangheJorrit::UBTDecorator_IsSurroundedByZombies_DelangheJorrit()
{
	NodeName = "Is Surrounded by zombies" ;
}

bool UBTDecorator_IsSurroundedByZombies_DelangheJorrit::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                                    uint8* NodeMemory) const
{
	APawn* Pawn {OwnerComp.GetAIOwner()->GetPawn()};
	if (!Pawn) return false;
	
	auto* Perceptor{Pawn->GetComponentByClass<UStudentPerceptor_DelangheJorrit>()};
	if (!Perceptor) return false;
	
	//remove zombies if too far
	constexpr float ForgetDistance{2500.f};
	FVector MyLocation{Pawn->GetActorLocation()};
	Perceptor->GetObservedZombies().RemoveAll([&](ABaseZombie* Z)
	{
		return !Z || FVector::Dist(Z->GetActorLocation(), MyLocation) > ForgetDistance;
	});
	
	return Perceptor->GetObservedZombies().Num()>= MaxZombies;
}
