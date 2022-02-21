#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "UdPolygon.generated.h"


#if WITH_EDITOR

#endif

UCLASS()
class UDSDKUPSCALING_API AUdPolygon : public AActor {
	GENERATED_BODY()

public:
	AUdPolygon();
	virtual ~AUdPolygon();
};