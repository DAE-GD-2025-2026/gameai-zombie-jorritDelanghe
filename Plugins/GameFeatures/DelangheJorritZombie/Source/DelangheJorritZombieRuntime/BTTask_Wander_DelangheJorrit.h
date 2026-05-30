#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Wander_DelangheJorrit.generated.h"

UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API  UBTTask_Wander_DelangheJorrit : public UBTTaskNode
{
GENERATED_BODY()
public:
	UBTTask_Wander_DelangheJorrit();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere,Category="Blackboard")
	FBlackboardKeySelector TargetLocationKey;
private:
};
