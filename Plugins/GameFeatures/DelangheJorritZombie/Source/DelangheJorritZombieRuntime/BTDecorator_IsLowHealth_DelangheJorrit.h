#pragma once
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsLowHealth_DelangheJorrit.generated.h"

UCLASS()
class UBTDecorator_IsLowHealth_DelangheJorrit final : public UBTDecorator
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int MinHealth{3};
	
	explicit UBTDecorator_IsLowHealth_DelangheJorrit();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
