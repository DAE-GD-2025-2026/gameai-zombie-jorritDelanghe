#pragma once
#include"CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MarkHouseVisited_DelangheJorrit.generated.h"

UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API UBTTask_MarkHouseVisited_DelangheJorrit final : public UBTTaskNode
{
	GENERATED_BODY()
public:
	explicit UBTTask_MarkHouseVisited_DelangheJorrit();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};