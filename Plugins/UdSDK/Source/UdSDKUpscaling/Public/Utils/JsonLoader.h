#pragma once

#include "CoreMinimal.h"
#include "Utils/JsonLoader.h"
#include "Utils/JsonValueWrapper.h"

#include <functional>


enum EJsonLoaderSource : uint8
{
	E_FILE,
	E_BUFFER,
	E_URL
};

struct FJsonLoaderOptions 
{
	EJsonLoaderSource Source = EJsonLoaderSource::E_BUFFER;
	FString From;
};


DECLARE_MULTICAST_DELEGATE_TwoParams(FJsonLoaderDelegate, UJsonValueWrapper*, const FString&);

typedef std::function<void(UJsonValueWrapper*, const FString&)>			FunJsonLoader;

class UDSDKUPSCALING_API CJsonLoader
{
public:

	FJsonLoaderDelegate Completed;
	FJsonLoaderDelegate Failed;

	CJsonLoader();
	~CJsonLoader();

	static void LoadJson(const FJsonLoaderOptions& Options,const FunJsonLoader & FuncCompleted = nullptr, const FunJsonLoader& FuncFailed = nullptr);

private:
	void LoadJsonFromFile();
	void LoadJsonFromBuffer(const FString& Buffer);
	void LoadJsonFromUrl();
	void _Completed(UJsonValueWrapper* JsonValue);
	void _Failed(const FString& ErrorReason);
private:
	FJsonLoaderOptions Options;
	TSharedPtr<CJsonLoader> SelfNode;
};


