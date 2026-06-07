#pragma once
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_HasInventorySpace_DelangheJorrit.generated.h"

UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API UBTDecorator_HasInventorySpace_DelangheJorrit final : public UBTDecorator
{
	GENERATED_BODY()
public:	
	explicit UBTDecorator_HasInventorySpace_DelangheJorrit();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
