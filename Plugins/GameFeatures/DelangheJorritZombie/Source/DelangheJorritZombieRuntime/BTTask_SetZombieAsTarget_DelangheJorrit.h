
#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetZombieAsTarget_DelangheJorrit.generated.h"
UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API UBTTask_SetZombieAsTarget_DelangheJorrit final: public UBTTaskNode
{
	GENERATED_BODY()
public:
	explicit UBTTask_SetZombieAsTarget_DelangheJorrit();
	
	//called when Behavour tree reaches node, one time
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere,Category="Blackboard")
	FBlackboardKeySelector TargetZombieKey{};
	
};