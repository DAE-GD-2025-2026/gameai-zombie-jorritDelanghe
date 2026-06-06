#include "BTTask_Wander_DelangheJorrit.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Wander_DelangheJorrit::UBTTask_Wander_DelangheJorrit()
{
	NodeName = "Wander around";
}

EBTNodeResult::Type UBTTask_Wander_DelangheJorrit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!Pawn|| !NavSystem) return EBTNodeResult::Failed;
	
	//forward direction
	const FVector2D ForwardVector{Pawn->GetActorForwardVector().X, Pawn->GetActorForwardVector().Y};
	
	// Circle center
	const FVector2D PawnPosition{Pawn->GetActorLocation().X, Pawn->GetActorLocation().Y};
	const FVector2D CirclePos{ PawnPosition + ForwardVector*OffsetDistance};
	

	m_WanderAngle = FMath::Fmod(m_WanderAngle + FMath::RandRange(-1.f, 1.f) * MaxAngleChange, 2.f * PI);

	//target on circle
	const FVector2D TargetOnCircle{
		CirclePos.X + WanderRadius * FMath::Cos(m_WanderAngle)
		,CirclePos.Y + WanderRadius * FMath::Sin(m_WanderAngle)};
	
	//snap to navemesh, otherwise problems with wandering forever
	const FVector WanderTarget{ TargetOnCircle.X, TargetOnCircle.Y, Pawn->GetActorLocation().Z };
	const FVector SnapExtent{ 200.f, 200.f, 200.f };
	
	FNavLocation NavLocation;
	if (!NavSystem->ProjectPointToNavigation(WanderTarget, NavLocation, SnapExtent))
	{
		//no failed because otherwise infinite loop needs always to succeed
		NavSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), WanderRadius, NavLocation);
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, NavLocation);
	return EBTNodeResult::Succeeded;
}
