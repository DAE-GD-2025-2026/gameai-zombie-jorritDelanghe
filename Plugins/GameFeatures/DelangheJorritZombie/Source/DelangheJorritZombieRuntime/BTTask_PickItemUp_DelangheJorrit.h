#pragma once
#include"CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PickItemUp_DelangheJorrit.generated.h"

UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API UBTTask_PickItemUp_DelangheJorrit final: public UBTTaskNode
{
	GENERATED_BODY()
public:
	explicit UBTTask_PickItemUp_DelangheJorrit();
	
	//called when Behavour tree reaches node, one time
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere,Category="Blackboard")
	FBlackboardKeySelector TargetItemKey{};
	
};
