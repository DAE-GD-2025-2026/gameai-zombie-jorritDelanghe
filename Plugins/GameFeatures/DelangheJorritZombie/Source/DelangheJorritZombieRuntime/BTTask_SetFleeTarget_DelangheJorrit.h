#pragma once
#include"CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetFleeTarget_DelangheJorrit.generated.h"

UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API UBTTask_SetFleeTarget_DelangheJorrit final : public UBTTaskNode
{
	GENERATED_BODY()
public:
	explicit UBTTask_SetFleeTarget_DelangheJorrit();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere,Category="Blackboard")
	FBlackboardKeySelector TargetFleeLocation{};
};
