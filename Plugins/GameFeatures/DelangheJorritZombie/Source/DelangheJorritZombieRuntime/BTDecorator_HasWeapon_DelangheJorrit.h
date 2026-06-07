#pragma once
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_HasWeapon_DelangheJorrit.generated.h"

UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API UBTDecorator_HasWeapon_DelangheJorrit final : public UBTDecorator
{
	GENERATED_BODY()
public:	
	explicit UBTDecorator_HasWeapon_DelangheJorrit();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};