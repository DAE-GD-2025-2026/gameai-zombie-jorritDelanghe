#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Village/House/House.h"
#include "BTTask_SetTarget_HouseDelangheJorrit.generated.h"

UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API  UBTTask_SetTarget_HouseDelangheJorrit final: public UBTTaskNode
{
	GENERATED_BODY()
public:
	explicit UBTTask_SetTarget_HouseDelangheJorrit();
	//avoid going to emptied houses
	UPROPERTY(EditAnywhere, Category="BlackBoard")
	bool bCanGoInVisistedHouses{false};
	
	//called when Behavour tree reaches node, one time
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	private:
	UPROPERTY(EditAnywhere,Category="Blackboard")
	FBlackboardKeySelector TargetHouseKey{};
};
