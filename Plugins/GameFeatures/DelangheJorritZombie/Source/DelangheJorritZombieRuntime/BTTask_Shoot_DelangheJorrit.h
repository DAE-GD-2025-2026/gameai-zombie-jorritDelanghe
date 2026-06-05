#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Shoot_DelangheJorrit.generated.h"

UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API UBTTask_Shoot_DelangheJorrit final : public UBTTaskNode
{
	GENERATED_BODY()
public:
	explicit UBTTask_Shoot_DelangheJorrit();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

