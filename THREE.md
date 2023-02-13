# UdJson
## 头文件：JsonValueWrapper.h
## 类：UJsonValueWrapper
<font size=5>该章节将介绍UdJson的解析、创建、增、删、查等方法。</font>

## <font size=5>EJsonValueType枚举</font>
| 属性                         |                          描述 |
| ---------------------------  | ---------------------------: |
| None                         |                    无，代表所有类型 |
| Null                         |                    空 |
| String                       |                    字符串型 |
| Number                       |                    整型 |
| Boolean                      |                    布尔型 |
| Array                        |                    Array类型 |
| Object                       |                    Object类型 |

## UdJson解析（蓝图可调用）
**<font size=5>Parse(const FString& JsonString, bool& Success)</font>**

<font size=5>返回类型：UJsonValueWrapper *</font>

<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| JsonString                  | const FString & | 必选  |                                         UdJson内容 |
| Success                     |   bool &        | 必选 |                               返回UdJson解析成功是否成功 |

## 用UdJson Array创建UdJson（蓝图可调用）
**<font size=5>CreateJsonArrayValue(TArray<UJsonValueWrapper*> Values)</font>**

<font size=5>返回类型：UJsonValueWrapper *</font>

<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| Values                      | TArray<UJsonValueWrapper*> | 必选 |                                      UdJson Array |
  
## 用UdJson Object创建UdJson（蓝图可调用）
**<font size=5>CreateJsonObjectValue(TMap<FString, UJsonValueWrapper*> Values)</font>**

<font size=5>返回类型：UJsonValueWrapper *</font>

<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| Values                  | TMap<FString, UJsonValueWrapper*> | 必选  |                                         UdJson Object |
  
## 用布尔值创建UdJson（蓝图可调用）
**<font size=5>CreateJsonBooleanValue(bool Value)</font>**

<font size=5>返回类型：UJsonValueWrapper *</font>

<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| Value                  | bool | 必选  |                                         布尔值 |
  
## 用字节创建UdJson（蓝图可调用）
**<font size=5>CreateJsonByteValue(uint8 Value)</font>**

<font size=5>返回类型：UJsonValueWrapper *</font>

<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| Value                  | uint8 | 必选  |                                         字节 |
  
## 用浮点数创建UdJson（蓝图可调用）
**<font size=5>CreateJsonFloatValue(float Value)</font>**

<font size=5>返回类型：UJsonValueWrapper *</font>

<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| Value                  | float | 必选  |                                         浮点数 |
  
## 用整数创建UdJson（蓝图可调用）
**<font size=5>CreateJsonIntValue(int32 Value)</font>**

<font size=5>返回类型：UJsonValueWrapper *</font>

<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| Value                  | int32 | 必选  |                                         整数 |
  
## 用空值创建UdJson（蓝图可调用）
**<font size=5>CreateJsonNullValue()</font>**

<font size=5>返回类型：UJsonValueWrapper *</font>
  
## 用字符串创建UdJson（蓝图可调用）
**<font size=5>CreateJsonStringValue(FString Value)</font>**

<font size=5>返回类型：UJsonValueWrapper *</font>

<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| Value                  | FString | 必选  |                                         字符串 |
  
## 给UdJson添加字段（蓝图可调用）
**<font size=5>AddField(FString FieldName, UJsonValueWrapper* const& Value, bool& Success)</font>**

<font size=5>返回类型：UJsonValueWrapper *</font>

<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| FieldName                  | FString | 必选  |                                         字段名 |
| Value                  | UJsonValueWrapper* const& | 必选  |                                         UdJson |
| Success                  | bool& | 必选  |                                         返回字段是否成功 |
  
## 获取UdJson类型（蓝图可调用）
**<font size=5>GetType()</font>**

<font size=5>返回类型：EJsonValueType</font>
  
## 判断UdJson类型（蓝图可调用）
**<font size=5>IsType(EJsonValueType Type)</font>**

<font size=5>返回类型：bool</font>
  
<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| Type                  | EJsonValueType | 必选  |                                         UdJson类型 |
  
## UdJson是否为空值（蓝图可调用）
**<font size=5>IsNullValue()</font>**

<font size=5>返回类型：bool</font>
  
## 比较UdJson是否相同（蓝图可调用）
**<font size=5>Equals(UJsonValueWrapper* const& Other)</font>**

<font size=5>返回类型：bool</font>
  
<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| Other                  | UJsonValueWrapper* const& | 必选  |                                         另一个UdJson |

## 查找UdJson是否包含目标字段（蓝图可调用）
**<font size=5>HasField(FString Pattern, EJsonValueType FilterType = EJsonValueType::None)</font>**

<font size=5>返回类型：bool</font>
  
<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| Pattern                 | FString | 必选  |                                         要查找的目标字段 |
| FilterType                  | EJsonValueType | 必选  |                              字段类型 |
  
## 移除UdJson目标字段，返回移除目标字段后的UdJson（蓝图可调用）
**<font size=5>RemoveField(FString FieldName, bool& Success)</font>**

<font size=5>返回类型：UJsonValueWrapper *</font>
  
<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| FieldName                 | FString | 必选  |                                         要移除的目标字段 |
| Success                  | bool& | 必选  |                             返回目标字段是否移除成功 |
  
## 移除类型为Array的UdJson的目标元素，返回移除目标元素后的UdJson（蓝图可调用）
**<font size=5>RemoveValueAt(int32 Index, bool& Success)</font>**

<font size=5>返回类型：UJsonValueWrapper *</font>
  
<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| Index                 | int32 | 必选  |                                         要移除的目标元素的索引 |
| Success                  | bool& | 必选  |                             返回目标元素是否移除成功 |
