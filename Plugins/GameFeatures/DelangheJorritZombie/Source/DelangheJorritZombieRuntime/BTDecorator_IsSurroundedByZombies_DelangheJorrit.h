#pragma once
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsSurroundedByZombies_DelangheJorrit.generated.h"

UCLASS()
class UBTDecorator_IsSurroundedByZombies_DelangheJorrit final : public UBTDecorator
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int MaxZombies{3};
	
	explicit UBTDecorator_IsSurroundedByZombies_DelangheJorrit();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
