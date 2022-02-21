#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"
#include "Serialization/JsonWriter.h"
#include "JsonValueWrapper.generated.h"

UENUM(BlueprintType)
enum class EJsonValueType : uint8
{
	None		UMETA(DisplayName = "None"),
	Null		UMETA(DisplayName = "Null"),
	String		UMETA(DisplayName = "String"),
	Number		UMETA(DisplayName = "Number"),
	Boolean		UMETA(DisplayName = "Boolean"),
	Array		UMETA(DisplayName = "Array"),
	Object		UMETA(DisplayName = "Object")
};

UCLASS(BlueprintType, Blueprintable)
class UDSDKUPSCALING_API UJsonValueWrapper : public UObject
{
	GENERATED_BODY()
private:
	TSharedPtr<FJsonValue> JsonValue;
public:
	UFUNCTION(BlueprintPure, Category = "UDComposite Json", CustomThunk, meta = (CustomStructureParam = "Value"))
	static void CreateJsonCustomValue(UJsonValueWrapper*& Out, const UStruct* Value);
	DECLARE_FUNCTION(execCreateJsonCustomValue)
	{
		P_GET_OBJECT_REF(UJsonValueWrapper, Out);
		Stack.Step(Stack.Object, NULL);

		FProperty* Prop = Stack.MostRecentProperty;
		void* Ptr = Stack.MostRecentPropertyAddress;

		P_FINISH;

		Out = UJsonValueWrapper::CreateJsonValue(UJsonValueWrapper::CustomToJsonValue(Prop, Ptr));
	}
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	static UJsonValueWrapper* CreateJsonArrayValue(TArray<UJsonValueWrapper*> Values);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	static UJsonValueWrapper* CreateJsonObjectValue(TMap<FString, UJsonValueWrapper*> Values);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	static UJsonValueWrapper* CreateJsonStringValue(FString Value);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json", meta = (DisplayName = "Create Json Number Value", Keywords = "float number json"))
	static UJsonValueWrapper* CreateJsonFloatValue(float Value);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json", meta = (DisplayName = "Create Json Number Value", Keywords = "int number json"))
	static UJsonValueWrapper* CreateJsonIntValue(int32 Value);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json", meta = (DisplayName = "Create Json Number Value", Keywords = "int64 number json"))
	static UJsonValueWrapper* CreateJsonInt64Value(int64 Value);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json", meta = (DisplayName = "Create Json Number Value", Keywords = "byte number json"))
	static UJsonValueWrapper* CreateJsonByteValue(uint8 Value);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	static UJsonValueWrapper* CreateJsonBooleanValue(bool Value);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	static UJsonValueWrapper* CreateJsonNullValue();
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	static UJsonValueWrapper* Parse(const FString& JsonString, bool& Success);
public:
	// member
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	EJsonValueType GetType();
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	bool IsType(EJsonValueType Type);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	void Stringify(FString& JsonString, bool& Success, bool PrettyPrint = false);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	bool HasField(FString Pattern, EJsonValueType FilterType = EJsonValueType::None);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	bool FindField(FString Pattern, UJsonValueWrapper*& Value, EJsonValueType FilterType = EJsonValueType::None);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	bool GetFieldNames(TArray<FString>& FieldNames);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	bool Equals(UJsonValueWrapper* const& Other);
	// accessors
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	bool IsNullValue();
	UFUNCTION(BlueprintPure, Category = "UDComposite Json", meta = (DisplayName = "Get Byte Number Value", Keywords = "byte number json"))
	bool GetByteValue(uint8& Value, uint8 Default = 0);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json", meta = (DisplayName = "Get Int Number Value", Keywords = "int number json"))
	bool GetIntValue(int32& Value, int32 Default = 0);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json", meta = (DisplayName = "Get Int64 Number Value", Keywords = "Int64 number json"))
	bool GetInt64Value(int64& Value, int64 Default = 0);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json", meta = (DisplayName = "Get Float Number Value", Keywords = "float number json"))
	bool GetFloatValue(float& Value, float Default = 0.0f);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	bool GetStringValue(FString& Value, FString Default = "");
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	bool GetBooleanValue(bool& Value, bool Default = false);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	bool GetObjectValue(TMap<FString, UJsonValueWrapper*>& Values);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json")
	bool GetArrayValue(TArray<UJsonValueWrapper*>& Values);
	UFUNCTION(BlueprintPure, Category = "UDComposite Json", CustomThunk, meta = (CustomStructureParam = "Value"))
	void GetCustomValue(bool& Success, UStruct*& Value);
	DECLARE_FUNCTION(execGetCustomValue)
	{
		UJsonValueWrapper* Target = (UJsonValueWrapper*) P_THIS_OBJECT;
		P_GET_UBOOL_REF(Success);

		Stack.Step(Stack.Object, NULL);

		FProperty* Prop = Stack.MostRecentProperty;
		void* Ptr = Stack.MostRecentPropertyAddress;

		P_FINISH;

		int32 TotalErrors = 0;

		Success = false;

		TSharedRef<FJsonValue> InJsonValue = UJsonValueWrapper::JsonValueToCustom(Prop, Target->JsonValue, TotalErrors);

		if (InJsonValue->Type != EJson::None && InJsonValue->Type != EJson::Null)
		{
			Success = FJsonObjectConverter::JsonValueToUProperty(InJsonValue, Prop, Ptr, 0, 0);
			Success &= (TotalErrors == 0);
		}
	}
	// utility wrapper object
	UFUNCTION(BlueprintCallable, Category = "UDComposite Json", meta = (DisplayName = "RemoveField", Keywords = "json map object utility remove field"))
	UJsonValueWrapper* RemoveField(FString FieldName, bool& Success);
	UFUNCTION(BlueprintCallable, Category = "UDComposite Json", meta = (DisplayName = "AddField", Keywords = "json map object utility add field"))
	UJsonValueWrapper* AddField(FString FieldName, UJsonValueWrapper* const& Value, bool& Success);
	// utility wrapper array
	UFUNCTION(BlueprintCallable, Category = "UDComposite Json", meta = (DisplayName = "RemoveValueAt", Keywords = "json array utility remove index"))
	UJsonValueWrapper* RemoveValueAt(int32 Index, bool& Success);
	UFUNCTION(BlueprintCallable, Category = "UDComposite Json", meta = (DisplayName = "RemoveValue", Keywords = "json array utility remove value"))
	UJsonValueWrapper* RemoveValue(UJsonValueWrapper* const& Value, bool& Success);
	UFUNCTION(BlueprintCallable, Category = "UDComposite Json", meta = (DisplayName = "AddValue", Keywords = "json array utility add index"))
	UJsonValueWrapper* AddValue(UJsonValueWrapper* const& Value, bool& Success, int32 Index = -1);
public:
	static TSharedRef<FJsonValue> JsonValueToCustom(FProperty* Property, TSharedPtr<FJsonValue> Value, int32& TotalErrors);
	static TSharedRef<FJsonValue> CustomToJsonValue(FProperty* Property, void* ValuePtr);
	static UJsonValueWrapper* CreateJsonValue(TSharedRef<FJsonValue> Value);
private:
	TSharedPtr<FJsonValue> GetField(TSharedPtr<FJsonValue> Value, FString Pattern, EJsonValueType FilterType);
	template <class PrintPolicy> static bool Stringify(UJsonValueWrapper* Wrapper, FString& JsonString, const TSharedRef<TJsonWriter<TCHAR, PrintPolicy>>& JsonWriter);
};
