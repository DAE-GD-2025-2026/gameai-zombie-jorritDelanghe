#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Village/House/House.h"
#include "BTTask_SetTarget_HouseDelangheJorrit.generated.h"

UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API  UBTTask_SetTarget_HouseDelangheJorrit : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_SetTarget_HouseDelangheJorrit();
	
	//called when Behavour tree reaches node, one time
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere,Category="Blackboard")
	FBlackboardKeySelector TargetHouseKey;
	private:
};
