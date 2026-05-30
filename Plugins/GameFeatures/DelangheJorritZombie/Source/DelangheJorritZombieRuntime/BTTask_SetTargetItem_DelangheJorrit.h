#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetTargetItem_DelangheJorrit.generated.h"
UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API UBTTask_SetTargetItem_DelangheJorrit final: public UBTTaskNode
{
	GENERATED_BODY()
public:
	explicit UBTTask_SetTargetItem_DelangheJorrit();
	
	//called when Behavour tree reaches node, one time
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere,Category="Blackboard")
	FBlackboardKeySelector TargetItemKey{};
	
};
