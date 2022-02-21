#include "Utils/JsonValueWrapper.h"
#include "Serialization/JsonSerializer.h"
#include "Policies/CondensedJsonPrintPolicy.h"

UJsonValueWrapper* UJsonValueWrapper::CreateJsonArrayValue(TArray<UJsonValueWrapper*> Values)
{
	auto Node = NewObject<UJsonValueWrapper>();
	TArray<TSharedPtr<FJsonValue>> Array;
	for (auto Val : Values)
	{
		Array.Add(Val->JsonValue);
	}
	Node->JsonValue = MakeShareable(new FJsonValueArray(Array));
	return Node;
}

UJsonValueWrapper* UJsonValueWrapper::CreateJsonObjectValue(TMap<FString, UJsonValueWrapper*> Values)
{
	auto Node = NewObject<UJsonValueWrapper>();
	auto Object = MakeShared<FJsonObject>();
	for (auto KeyVal : Values)
	{
		Object->SetField(KeyVal.Key, KeyVal.Value->JsonValue);
	}
	Node->JsonValue = MakeShareable(new FJsonValueObject(Object));
	return Node;
}

UJsonValueWrapper* UJsonValueWrapper::CreateJsonStringValue(FString Value)
{
	auto Node = NewObject<UJsonValueWrapper>();
	Node->JsonValue = MakeShareable(new FJsonValueString(Value));
	return Node;
}

UJsonValueWrapper* UJsonValueWrapper::CreateJsonFloatValue(float Value)
{
	auto Node = NewObject<UJsonValueWrapper>();
	Node->JsonValue = MakeShareable(new FJsonValueNumber(Value));
	return Node;
}

UJsonValueWrapper* UJsonValueWrapper::CreateJsonIntValue(int32 Value)
{
	auto Node = NewObject<UJsonValueWrapper>();
	Node->JsonValue = MakeShareable(new FJsonValueNumber(Value));
	return Node;
}

UJsonValueWrapper* UJsonValueWrapper::CreateJsonInt64Value(int64 Value)
{
	auto Node = NewObject<UJsonValueWrapper>();
	Node->JsonValue = MakeShareable(new FJsonValueNumber(Value));
	return Node;
}

UJsonValueWrapper* UJsonValueWrapper::CreateJsonByteValue(uint8 Value)
{
	auto Node = NewObject<UJsonValueWrapper>();
	Node->JsonValue = MakeShareable(new FJsonValueNumber(Value));
	return Node;
}

UJsonValueWrapper* UJsonValueWrapper::CreateJsonBooleanValue(bool Value)
{
	auto Node = NewObject<UJsonValueWrapper>();
	Node->JsonValue = MakeShareable(new FJsonValueBoolean(Value));
	return Node;
}

UJsonValueWrapper* UJsonValueWrapper::CreateJsonNullValue()
{
	auto Node = NewObject<UJsonValueWrapper>();
	Node->JsonValue = MakeShareable(new FJsonValueNull());
	return Node;
}

UJsonValueWrapper* UJsonValueWrapper::Parse(const FString& JsonString, bool& Success)
{
	Success = false;
	TSharedPtr<FJsonValue> JsonValue;
	TSharedRef<TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (FJsonSerializer::Deserialize(JsonReader, JsonValue) && JsonValue.IsValid())
	{
		Success = true;
		return UJsonValueWrapper::CreateJsonValue(JsonValue.ToSharedRef());
	}
	return nullptr;
}

EJsonValueType UJsonValueWrapper::GetType()
{
	return (EJsonValueType)this->JsonValue->Type;
}

bool UJsonValueWrapper::IsType(EJsonValueType Type)
{
	return ((EJsonValueType) this->JsonValue->Type) == Type;
}

UJsonValueWrapper* UJsonValueWrapper::CreateJsonValue(TSharedRef<FJsonValue> Value)
{
	auto Node = NewObject<UJsonValueWrapper>();
	Node->JsonValue = Value;
	return Node;
}

TSharedPtr<FJsonValue> UJsonValueWrapper::GetField(TSharedPtr<FJsonValue> Value, FString Pattern, EJsonValueType FilterType)
{
	FString Start = Pattern;
	FString Rest;
	Pattern.Split("/", &Start, &Rest);
	if (Value->Type == EJson::Object)
	{
		auto Obj = Value->AsObject();
		auto Res = Obj->Values.Find(Start);
		if (Res)
		{
			if (Rest.IsEmpty() && (FilterType == EJsonValueType::None || FilterType == ((EJsonValueType)(*Res)->Type)))
			{
				return *Res;
			}
			else
			{
				return this->GetField(*Res, Rest, FilterType);
			}
		}
	} 
	else if (Value->Type == EJson::Array)
	{
			if (Start.IsNumeric())
			{
				auto Arr = Value->AsArray();
				int32 Idx = FCString::Atoi(*Start);
				if (Idx > -1 && Idx < Arr.Num())
				{
					if (Rest.IsEmpty() && (FilterType == EJsonValueType::None || FilterType == ((EJsonValueType)(Arr[Idx])->Type)))
					{
						return Arr[Idx];
					}
					else
					{
						return this->GetField(Arr[Idx], Rest, FilterType);
					}
				}
			}
	}
	return nullptr;
}

UJsonValueWrapper* UJsonValueWrapper::RemoveField(FString FieldName, bool& Success)
{
	Success = false;
	if (this->IsType(EJsonValueType::Object))
	{
		auto Object = this->JsonValue->AsObject();
		if (Object->HasField(FieldName))
		{
			Object->RemoveField(FieldName);
			Success = true;
			return UJsonValueWrapper::CreateJsonValue(MakeShareable(new FJsonValueObject(Object)));
		}
	}
	return nullptr;
}

UJsonValueWrapper* UJsonValueWrapper::AddField(FString FieldName, UJsonValueWrapper* const& Value, bool& Success)
{
	Success = false;
	if (this->IsType(EJsonValueType::Object))
	{
		auto Object = this->JsonValue->AsObject();
		Object->SetField(FieldName, Value->JsonValue);
		Success = true;
		return UJsonValueWrapper::CreateJsonValue(MakeShareable(new FJsonValueObject(Object)));
	}
	return nullptr;
}

UJsonValueWrapper* UJsonValueWrapper::RemoveValueAt(int32 Index, bool& Success)
{
	Success = false;
	if (this->IsType(EJsonValueType::Array))
	{
		auto Array = this->JsonValue->AsArray();
		if (Array.IsValidIndex(Index))
		{
			Array.RemoveAt(Index);
			Success = true;
			return UJsonValueWrapper::CreateJsonValue(MakeShareable(new FJsonValueArray(Array)));
		}
	}
	return nullptr;
}

UJsonValueWrapper* UJsonValueWrapper::RemoveValue(UJsonValueWrapper* const& Value, bool& Success)
{
	Success = false;
	if (this->IsType(EJsonValueType::Array))
	{
		auto Array = this->JsonValue->AsArray();
		if (Array.Remove(Value->JsonValue) > 0)
		{
			Success = true;
			return UJsonValueWrapper::CreateJsonValue(MakeShareable(new FJsonValueArray(Array)));
		}
	}
	return nullptr;
}

UJsonValueWrapper* UJsonValueWrapper::AddValue(UJsonValueWrapper* const& Value, bool& Success, int32 Index)
{
	Success = false;
	if (this->IsType(EJsonValueType::Array))
	{
		auto Array = this->JsonValue->AsArray();
		if ((Index > -1 ? Array.Insert(Value->JsonValue, Index) : Array.Add(Value->JsonValue)) >= 0)
		{
			Success = true;
			return UJsonValueWrapper::CreateJsonValue(MakeShareable(new FJsonValueArray(Array)));
		}
	}
	return nullptr;
}

TSharedRef<FJsonValue> UJsonValueWrapper::JsonValueToCustom(FProperty* Property, TSharedPtr<FJsonValue> Value, int32& Errors)
{
	if (!Value.IsValid() || Value->IsNull() || Property == NULL)
	{
		return MakeShareable(new FJsonValueNull());
	}
	// array
	else if (FArrayProperty* arrayProperty = CastField<FArrayProperty>(Property))
	{
		TArray<TSharedPtr<FJsonValue>> OutArray;
		if (Value->Type == EJson::Array)
		{
			auto InArray = Value->AsArray();
			for (int32 ArrayIndex = 0; ArrayIndex < InArray.Num(); ArrayIndex++)
			{
				OutArray.Add(UJsonValueWrapper::JsonValueToCustom(arrayProperty->Inner, InArray[ArrayIndex], Errors));
			}
		}
		else
		{
			Errors++;
			UE_LOG(LogTemp, Warning, TEXT("JsonValueToCustom: error while converting JsonValue to array, type %i is invalid with array property, returning empty array"), Value->Type);
		}
		return MakeShareable(new FJsonValueArray(OutArray));
	}
	// set
	else if (FSetProperty* setProperty = CastField<FSetProperty>(Property))
	{
		TArray<TSharedPtr<FJsonValue>> OutSet;
		if (Value->Type == EJson::Array)
		{
			auto InSet = Value->AsArray();
			for (int32 ArrayIndex = 0; ArrayIndex < InSet.Num(); ArrayIndex++)
			{
				OutSet.Add(UJsonValueWrapper::JsonValueToCustom(setProperty->ElementProp, InSet[ArrayIndex], Errors));
			}
		}
		else
		{
			Errors++;
			UE_LOG(LogTemp, Warning, TEXT("JsonValueToCustom: error while converting JsonValue to set, type %i is invalid with set property, returning empty set"), Value->Type);
		}
		return MakeShareable(new FJsonValueArray(OutSet));
	}
	// map
	else if (FMapProperty* mapProperty = CastField<FMapProperty>(Property))
	{
		TSharedRef<FJsonObject> OutMap = MakeShared<FJsonObject>();
		if (Value->Type == EJson::Object)
		{
			auto InMap = Value->AsObject();
			for (auto Val : InMap->Values)
			{
				OutMap->SetField(Val.Key, UJsonValueWrapper::JsonValueToCustom(mapProperty->ValueProp, Val.Value, Errors));
			}
		}
		else
		{
			Errors++;
			UE_LOG(LogTemp, Warning, TEXT("JsonValueToCustom: error while converting JsonValue to map, type %i is invalid with map property, returning empty object"), Value->Type);
		}
		return MakeShareable(new FJsonValueObject(OutMap));
	}
	// struct
	else if (FStructProperty* structProperty = CastField<FStructProperty>(Property))
	{
		TSharedRef<FJsonObject> OutObject = MakeShared<FJsonObject>();
		if (Value->Type == EJson::Object)
		{
			auto InObject = Value->AsObject();
			for (TFieldIterator<FProperty> It(structProperty->Struct); It; ++It)
			{
				FProperty* Prop = *It;
				if (InObject->HasField(Prop->GetAuthoredName()))
				{
					OutObject->SetField(Prop->GetName(), UJsonValueWrapper::JsonValueToCustom(Prop, InObject->Values.Find(Prop->GetAuthoredName())->ToSharedRef(), Errors));
				}
				else if (InObject->HasField(Prop->GetName()))
				{
					OutObject->SetField(Prop->GetName(), UJsonValueWrapper::JsonValueToCustom(Prop, InObject->Values.Find(Prop->GetName())->ToSharedRef(), Errors));
				}
			}
		}
		else
		{
			Errors++;
			UE_LOG(LogTemp, Warning, TEXT("JsonValueToCustom: error while converting JsonValue to struct, type %i is invalid with struct property, returning empty object"), Value->Type);
		}
		return MakeShareable(new FJsonValueObject(OutObject));
	}
	// object
	else if (FObjectProperty* objectProperty = CastField<FObjectProperty>(Property))
	{
		TSharedRef<FJsonObject> OutObject = MakeShared<FJsonObject>();
		if (objectProperty->PropertyClass->IsNative())
		{
			return Value.ToSharedRef();
		}
		if (Value->Type == EJson::Object)
		{
			auto InObject = Value->AsObject();
			for (TFieldIterator<FProperty> It(objectProperty->PropertyClass); It; ++It)
			{
				FProperty* Prop = *It;
				if (InObject->HasField(Prop->GetAuthoredName()))
				{
					OutObject->SetField(Prop->GetName(), UJsonValueWrapper::JsonValueToCustom(Prop, InObject->Values.Find(Prop->GetAuthoredName())->ToSharedRef(), Errors));
				}
				else if (InObject->HasField(Prop->GetName()))
				{
					OutObject->SetField(Prop->GetName(), UJsonValueWrapper::JsonValueToCustom(Prop, InObject->Values.Find(Prop->GetName())->ToSharedRef(), Errors));
				}
			}
		}
		else
		{
			Errors++;
			UE_LOG(LogTemp, Warning, TEXT("JsonValueToCustom: error while converting JsonValue to object, type %i is invalid with object property, returning empty object"), Value->Type);
		}
		return MakeShareable(new FJsonValueObject(OutObject));
	}
	// scalar
	else
	{
		return Value.ToSharedRef();
	}
}

TSharedRef<FJsonValue> UJsonValueWrapper::CustomToJsonValue(FProperty* Property, void* ValuePtr)
{
	if (ValuePtr == NULL || Property == NULL)
	{
		return MakeShareable(new FJsonValueNull());
	}
	// array
	else if (FArrayProperty* arrayProperty = CastField<FArrayProperty>(Property))
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		auto Helper = FScriptArrayHelper::CreateHelperFormInnerProperty(arrayProperty->Inner, ValuePtr);
		for (int32 ArrayIndex = 0; ArrayIndex < Helper.Num(); ArrayIndex++)
		{
			Array.Add(UJsonValueWrapper::CustomToJsonValue(arrayProperty->Inner, Helper.GetRawPtr(ArrayIndex)));
		}
		return MakeShareable(new FJsonValueArray(Array));
	}
	// set
	else if (FSetProperty* setProperty = CastField<FSetProperty>(Property))
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		auto Helper = FScriptSetHelper::CreateHelperFormElementProperty(setProperty->ElementProp, ValuePtr);
		for (int32 ArrayIndex = 0; ArrayIndex < Helper.Num(); ++ArrayIndex)
		{
			Array.Add(UJsonValueWrapper::CustomToJsonValue(setProperty->ElementProp, Helper.GetElementPtr(ArrayIndex)));
		}
		return MakeShareable(new FJsonValueArray(Array));
	}
	// map 
	else if (FMapProperty* mapProperty = CastField<FMapProperty>(Property))
	{
		TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		auto Helper = FScriptMapHelper::CreateHelperFormInnerProperties(mapProperty->KeyProp, mapProperty->ValueProp, ValuePtr);
		for (int32 ArrayIndex = 0; ArrayIndex < Helper.Num(); ++ArrayIndex)
		{
			FString KeyStr;
			auto Key = UJsonValueWrapper::CustomToJsonValue(mapProperty->KeyProp, Helper.GetKeyPtr(ArrayIndex));
			if (!Key->TryGetString(KeyStr))
			{
				mapProperty->KeyProp->ExportTextItem(KeyStr, Helper.GetKeyPtr(ArrayIndex), nullptr, nullptr, 0);
				if (KeyStr.IsEmpty())
				{
					UE_LOG(LogTemp, Warning, TEXT("CustomToJsonValue : Error serializing key in map property at index %i, using empty string as key"), ArrayIndex);
				}
			}
			auto Val = UJsonValueWrapper::CustomToJsonValue(mapProperty->ValueProp, Helper.GetValuePtr(ArrayIndex));
			JsonObject->SetField(KeyStr, Val);
		}
		return MakeShareable(new FJsonValueObject(JsonObject));
	}
	// struct
	else if (FStructProperty* structProperty = CastField<FStructProperty>(Property))
	{
		TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		for (TFieldIterator<FProperty> It(structProperty->Struct); It; ++It)
		{
			FProperty* Prop = *It;
			JsonObject->SetField(Prop->GetAuthoredName(), UJsonValueWrapper::CustomToJsonValue(Prop, Prop->ContainerPtrToValuePtr<void*>(ValuePtr)));
		}
		return MakeShareable(new FJsonValueObject(JsonObject));
	}
	// object
	else if (FObjectProperty* objectProperty = CastField<FObjectProperty>(Property))
	{
		void* PropValue = objectProperty->GetObjectPropertyValue(ValuePtr);
		if (PropValue == NULL)
		{
			return MakeShareable(new FJsonValueNull());
		}
		if (objectProperty->PropertyClass->IsNative())
		{
			auto Value = FJsonObjectConverter::UPropertyToJsonValue(Property, ValuePtr, 0, 0);
			return Value.ToSharedRef();
		}
		TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		for (TFieldIterator<FProperty> It(objectProperty->PropertyClass); It; ++It)
		{
			FProperty* Prop = *It;
			JsonObject->SetField(Prop->GetAuthoredName(), UJsonValueWrapper::CustomToJsonValue(Prop, Prop->ContainerPtrToValuePtr<void*>(PropValue)));
		}
		return MakeShareable(new FJsonValueObject(JsonObject));
	}
	// scalar
	else
	{
		auto Value = FJsonObjectConverter::UPropertyToJsonValue(Property, ValuePtr, 0, 0);
		return Value.ToSharedRef();
	}
}


void UJsonValueWrapper::Stringify(FString& JsonString, bool& Success, bool PrettyPrint)
{
	Success = false;
	JsonString = "";
	if (PrettyPrint)
	{
		Success = UJsonValueWrapper::Stringify<TPrettyJsonPrintPolicy<TCHAR>>(this, JsonString, TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&JsonString, 0));
	}
	else
	{
		Success = UJsonValueWrapper::Stringify<TCondensedJsonPrintPolicy<TCHAR>>(this, JsonString, TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonString, 0));
	}
}

bool UJsonValueWrapper::HasField(FString Pattern, EJsonValueType FilterType)
{
	return this->GetField(this->JsonValue, Pattern, FilterType) != nullptr;
}

bool UJsonValueWrapper::FindField(FString Pattern, UJsonValueWrapper*& Value, EJsonValueType FilterType)
{
	auto Res = this->GetField(this->JsonValue, Pattern, FilterType);
	if (Res)
	{
		Value = UJsonValueWrapper::CreateJsonValue(Res.ToSharedRef());
		return true;
	}
	return false;
}

bool UJsonValueWrapper::GetFieldNames(TArray<FString>& FieldNames)
{
	if (this->JsonValue->Type == EJson::Object)
	{
		this->JsonValue->AsObject()->Values.GetKeys(FieldNames);
		return true;
	}
	return false;
}

bool UJsonValueWrapper::Equals(UJsonValueWrapper* const& Other)
{
	if (!this->JsonValue.IsValid() || !Other->JsonValue.IsValid())
	{
		return false;
	}
	return FJsonValue::CompareEqual(*this->JsonValue.Get(), *Other->JsonValue.Get());
}

bool UJsonValueWrapper::IsNullValue()
{
	return this->JsonValue->IsNull();
}

bool UJsonValueWrapper::GetByteValue(uint8& Value, uint8 Default)
{
	if (this->JsonValue->TryGetNumber(Value))
	{
		return true;
	}
	Value = Default;
	return false;
}

bool UJsonValueWrapper::GetIntValue(int32& Value, int32 Default)
{
	if (this->JsonValue->TryGetNumber(Value))
	{
		return true;
	}
	Value = Default;
	return false;
}

bool UJsonValueWrapper::GetInt64Value(int64& Value, int64 Default)
{
	if (this->JsonValue->TryGetNumber(Value))
	{
		return true;
	}
	Value = Default;
	return false;
}

bool UJsonValueWrapper::GetFloatValue(float& Value, float Default)
{
	if (this->JsonValue->TryGetNumber(Value))
	{
		return true;
	}
	Value = Default;
	return false;
}

bool UJsonValueWrapper::GetStringValue(FString& Value, FString Default)
{
	if (this->JsonValue->TryGetString(Value))
	{
		return true;
	}
	Value = Default;
	return false;
}

bool UJsonValueWrapper::GetBooleanValue(bool& Value, bool Default)
{
	if (this->JsonValue->TryGetBool(Value))
	{
		return true;
	}
	Value = Default;
	return false;
}

bool UJsonValueWrapper::GetObjectValue(TMap<FString, UJsonValueWrapper*>& Value)
{
	if (this->JsonValue->Type == EJson::Object)
	{
		auto Obj = this->JsonValue->AsObject();
		for (auto KeyVal : Obj->Values)
		{
			Value.Add(KeyVal.Key, UJsonValueWrapper::CreateJsonValue(KeyVal.Value.ToSharedRef()));
		}
		return true;
	}
	return false;
}

bool UJsonValueWrapper::GetArrayValue(TArray<UJsonValueWrapper*>& Value)
{
	if (this->JsonValue->Type == EJson::Array)
	{
		auto Arr = this->JsonValue->AsArray();
		for (auto Val : Arr)
		{
			Value.Add(UJsonValueWrapper::CreateJsonValue(Val.ToSharedRef()));
		}
		return true;
	}
	return false;
}

template<class PrintPolicy>
bool UJsonValueWrapper::Stringify(UJsonValueWrapper* Wrapper, FString& JsonString, const TSharedRef<TJsonWriter<TCHAR, PrintPolicy>>& JsonWriter)
{
	bool Result = false;
	if (Wrapper->JsonValue->Type == EJson::Object)
	{
		Result = FJsonSerializer::Serialize(Wrapper->JsonValue->AsObject().ToSharedRef(), JsonWriter);
	}
	else if (Wrapper->JsonValue->Type == EJson::Array)
	{
		Result = FJsonSerializer::Serialize(Wrapper->JsonValue->AsArray(), JsonWriter);
	}
	JsonWriter->Close();
	return Result;
}
