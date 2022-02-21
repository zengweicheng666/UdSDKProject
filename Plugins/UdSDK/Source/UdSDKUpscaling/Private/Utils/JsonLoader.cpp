#include "Utils/JsonLoader.h"
#include "HAL/PlatformFilemanager.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "UdSDKMacro.h"

CJsonLoader::CJsonLoader()
{
	SelfNode = MakeShared<CJsonLoader>(*this);
}

CJsonLoader::~CJsonLoader()
{
	this->Completed.RemoveAll(this);
	this->Failed.RemoveAll(this);
}

void CJsonLoader::LoadJson(const FJsonLoaderOptions& Options, const FunJsonLoader& FuncCompleted, const FunJsonLoader& FuncFailed)
{
	CJsonLoader * Node = new CJsonLoader;

	Node->Options = Options;

	if(FuncCompleted)
		Node->Completed.AddLambda(FuncCompleted);
	if(FuncFailed)
		Node->Failed.AddLambda(FuncFailed);

	switch (Node->Options.Source)
	{
	case(EJsonLoaderSource::E_BUFFER):
		Node->LoadJsonFromBuffer(Node->Options.From);
		break;
	case(EJsonLoaderSource::E_FILE):
		Node->LoadJsonFromFile();
		break;
	case(EJsonLoaderSource::E_URL):
		Node->LoadJsonFromUrl();
		break;
	}
}

void CJsonLoader::LoadJsonFromFile()
{
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();
	if (file.FileExists(*this->Options.From))
	{
		FString Output;
		if (FFileHelper::LoadFileToString(Output, *this->Options.From))
		{
			this->LoadJsonFromBuffer(Output);
		}
		else
		{
			this->_Failed("CJsonLoader: Could not load text content of file : " + this->Options.From);
		}
	}
	else
	{
		this->_Failed("CJsonLoader: Invalid filepath provided : " + this->Options.From);
	}
}

void CJsonLoader::LoadJsonFromBuffer(const FString& Buffer)
{
	bool Result;
	UJsonValueWrapper* Value = UJsonValueWrapper::Parse(Buffer, Result);
	if (Result)
	{
		this->_Completed(Value);
	}
	else
	{
		this->_Failed("CJsonLoader: Could not parse string into JsonValue");
	}
}

void CJsonLoader::LoadJsonFromUrl()
{
	auto Request = FHttpModule::Get().CreateRequest();
	Request->SetVerb("GET");
	Request->SetHeader("Accept", "application/json");
	Request->SetURL(this->Options.From);
	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess)
	{
		if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
		{
			FFrame::KismetExecutionMessage(TEXT("CJsonLoader: Request or response is invalid, cannot complete http request"), ELogVerbosity::Error);
			this->_Failed("CJsonLoader: Request or response is invalid, cannot complete http request");
			return;
		}
		if (bSuccess)
		{
			this->LoadJsonFromBuffer(HttpResponse->GetContentAsString());
		}
		else
		{
			this->_Failed("CJsonLoader: Http request failed with error code : " + FString::FromInt(HttpResponse->GetResponseCode()));
		}
	});
	Request->ProcessRequest();
}

void CJsonLoader::_Completed(UJsonValueWrapper* JsonValue)
{
	if (this->Completed.IsBound())
	{
		this->Completed.Broadcast(JsonValue, FString());
	}
	SelfNode = nullptr;
}

void CJsonLoader::_Failed(const FString& ErrorReason)
{
	UDSDK_ERROR_MSG("JsonLoader: Failed reason : %s ", *ErrorReason);
	if (this->Failed.IsBound())
	{
		this->Failed.Broadcast(nullptr, ErrorReason);
	}
	SelfNode = nullptr;
}
