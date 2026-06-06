#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Wander_DelangheJorrit.generated.h"

UCLASS()
class DELANGHEJORRITZOMBIERUNTIME_API  UBTTask_Wander_DelangheJorrit final : public UBTTaskNode
{
GENERATED_BODY()
public:
	explicit UBTTask_Wander_DelangheJorrit();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere,Category="Blackboard")
	FBlackboardKeySelector TargetLocationKey;
	
	// How far ahead the wander circle is projected
	UPROPERTY(EditAnywhere, Category="Wander", meta=(ClampMin="50.0", ClampMax="1000.0"))
	float OffsetDistance{ 50.f };
 
	// Radius of the wander circle,larger = more weird turns
	UPROPERTY(EditAnywhere, Category="Wander", meta=(ClampMin="50.0", ClampMax="500.0"))
	float WanderRadius{ 50.f };
 
	// Max angle change
	UPROPERTY(EditAnywhere, Category="Wander", meta=(ClampMin="0.1", ClampMax="3.14"))
	float MaxAngleChange{ 0.5f };
	
	float m_WanderAngle{ 0.f };
};
