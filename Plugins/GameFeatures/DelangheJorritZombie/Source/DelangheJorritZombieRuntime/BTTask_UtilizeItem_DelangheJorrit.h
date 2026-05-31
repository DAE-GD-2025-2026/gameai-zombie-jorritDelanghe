#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"
#include "BTTask_UtilizeItem_DelangheJorrit.generated.h"
UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API UBTTask_UtilizeItem_DelangheJorrit final: public UBTTaskNode
{
	GENERATED_BODY()
public:
	explicit UBTTask_UtilizeItem_DelangheJorrit();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
