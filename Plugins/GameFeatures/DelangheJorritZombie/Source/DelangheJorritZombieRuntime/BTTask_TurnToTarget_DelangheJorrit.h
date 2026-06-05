#pragma once
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_TurnToTarget_DelangheJorrit.generated.h"

UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API UBTTask_TurnToTarget_DelangheJorrit final : public UBTTask_BlackboardBase  
{
	GENERATED_BODY()
public:
	explicit UBTTask_TurnToTarget_DelangheJorrit();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

