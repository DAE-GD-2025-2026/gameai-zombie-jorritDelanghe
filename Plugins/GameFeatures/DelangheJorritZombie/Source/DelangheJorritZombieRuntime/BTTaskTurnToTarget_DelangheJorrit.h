#pragma once
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskTurnToTarget_DelangheJorrit.generated.h"

UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API UBTTaskTurnToTarget_DelangheJorrit final : public UBTTask_BlackboardBase  
{
	GENERATED_BODY()
public:
	explicit UBTTaskTurnToTarget_DelangheJorrit();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

