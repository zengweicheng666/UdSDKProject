#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UdPointCloud.generated.h"


#if WITH_EDITOR

#endif


UCLASS()
class UDSDKUPSCALING_API AUdPointCloud : public AActor {
	GENERATED_BODY()

public:
	AUdPointCloud();
	virtual ~AUdPointCloud();

	void UpdatePointCloudTransform(const FTransform& InScale);
public:
	UFUNCTION(BlueprintGetter, Category = "UdSDK")
	FString GetUrl() const { return Url; }

	UFUNCTION(BlueprintSetter, Category = "UdSDK")
	void SetUrl(FString InUrl);

	UFUNCTION(CallInEditor, BlueprintCallable, Category = "UdSDK")
	void RefreshPointCloud();

protected:

	/** Overridable native event for when play begins for this actor. */
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginDestroy() override;
	virtual void Destroyed() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostLoad() override;
	virtual void Serialize(FArchive& Ar) override;

	// UObject overrides
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditUndo() override;
	virtual void PostEditImport() override;
#endif

	virtual void PreDuplicate(FObjectDuplicationParameters& DupParams) override;
	virtual void PostDuplicate(bool bDuplicateForPIE) override;

private:
	void LoadPointCloud();
	void ReloadPointCloud();
	void DestroyPointCloud();
	void SelectPointCloud(bool InSelect);
	void LoginPointCloud();
	void ExitPointCloud();
private:
	UPROPERTY(EditAnywhere, Category = "UdSDK|Debug")
	bool UpdateInEditor = true;

	UPROPERTY(
		EditAnywhere,
		BlueprintGetter = GetUrl,
		BlueprintSetter = SetUrl,
		Category = "UdSDK")
	FString Url;

private:
	uint8 bWasDuplicatedForPIE : 1;
	uint8 bWasHiddenEd : 1;
	uint8 bWasSelectedInEditor : 1;

	TSharedPtr<struct FUdAsset> pAsset;

	FDelegateHandle LoginDelegateHandle;
	FDelegateHandle ExitDelegateHandle;
};