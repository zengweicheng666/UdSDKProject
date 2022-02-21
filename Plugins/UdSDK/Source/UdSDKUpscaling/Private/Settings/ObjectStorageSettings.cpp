// Copyright (C) RenZhai.2021.All Rights Reserved.
#include "Settings/ObjectStorageSettings.h"
#include "UdSDKComposite.h"

UObjectStorageSettings::UObjectStorageSettings()
	:ServerPath("")
	, Username("")
	, Password("")
	//, Offline(false)
	, SelectColor(FColor::Blue)
{

}

void UObjectStorageSettings::RefreshData()
{
	CUdSDKComposite::SetSelectColor(SelectColor.DWColor());
}
