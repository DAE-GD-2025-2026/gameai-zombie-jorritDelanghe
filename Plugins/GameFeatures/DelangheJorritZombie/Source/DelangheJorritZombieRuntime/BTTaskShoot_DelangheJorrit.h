#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskShoot_DelangheJorrit.generated.h"

UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API UBTTaskShoot_DelangheJorrit final : public UBTTaskNode
{
	GENERATED_BODY()
public:
	explicit UBTTaskShoot_DelangheJorrit();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

