# 加载UdJson文件
## 头文件：JsonLoader.h
## 类：CJsonLoader
<font size=5>该章节将介绍加载UdJson文件的方法。</font>


## <font size=5>FJsonLoaderOptions结构体</font>
| 属性                        |         类型          |                                            描述 |
| --------------------------- | :-------------------: | -----------------------------------------------: |
| Source                | EJsonLoaderSource |                                          UdJson来源 |
| From                  |           Fstring |                                          UdJson内容 |

## <font size=5>EJsonLoaderSource枚举</font>
| 属性                         |                          描述 |
| ---------------------------  | ---------------------------: |
| E_FILE                       |                    文件 |
| E_BUFFER                     |                    缓存 |
| E_URL                        |                    URL  |

## 加载UdJson文件
**<font size=5>LoadJson(const FJsonLoaderOptions& Options,const FunJsonLoader & FuncCompleted = nullptr, const FunJsonLoader& FuncFailed = nullptr)</font>**

<font size=5>返回类型：void</font>

<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| Options                |const FJsonLoaderOptions&| 必选  |                                         UdJson内容和来源 |
| FuncCompleted          |const FunJsonLoader &| 非必选 |      std::function<void(UJsonValueWrapper*, const FString&)>对象，用于绑定委托到UdJson加载成功时 |
| FuncFailed             |const FunJsonLoader&| 非必选  |      std::function<void(UJsonValueWrapper*, const FString&)>对象，用于绑定委托到UdJson加载失败时 |