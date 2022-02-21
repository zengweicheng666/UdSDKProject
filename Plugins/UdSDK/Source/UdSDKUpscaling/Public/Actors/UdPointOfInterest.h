#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "UdPointOfInterest.generated.h"


#if WITH_EDITOR

#endif

UCLASS()
class UDSDKUPSCALING_API AUdPointOfInterest : public AActor {
	GENERATED_BODY()

public:
	AUdPointOfInterest();
	virtual ~AUdPointOfInterest();
};