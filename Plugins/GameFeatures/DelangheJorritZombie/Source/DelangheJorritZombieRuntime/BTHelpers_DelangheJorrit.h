#pragma once

template<typename T>
static T* FindClosestActor(const TArray<T*>& actors, const FVector& survivor)
{
	float closestDistance{FLT_MAX};
	T* closestActor{nullptr};
	
	for (auto* actor : actors)
	{
		const float distance {static_cast<float>( FVector::Dist(survivor,actor->GetActorLocation()))};
		
		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestActor = actor;
		}
	}
	return closestActor;
}
