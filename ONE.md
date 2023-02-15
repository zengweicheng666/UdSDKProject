# 登录登出
## 头文件：UdSDKFunctionLibrary.h
## 类：UUdSDKFunctionLibrary
<font size=5>该章节将介绍登录和登出udUE SDK的方法。此外还介绍了如何绑定委托，才能在登录和登出udUE SDK时执行额外的操作。</font>
## 登录
**<font size=5>Login()</font>**

<font size=5>返回类型：bool</font>
## 判断是否登录
**<font size=5>IsLogin()</font>**

<font size=5>返回类型：bool</font>
## 登出
**<font size=5>Exit()</font>**

<font size=5>返回类型：bool</font>
## 绑定委托到登录时
**<font size=5>AddLoginDelegateLambda(const FunUdSDKDelegate& FuncDelegate)</font>**

<font size=5>返回类型：FDelegateHandle</font>

<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| FuncDelegate                |const FunUdSDKDelegate&| 必选  |                                         std::function<void()>对象 |

## 绑定委托到登出时
**<font size=5>AddExitDelegateLambda(const FunUdSDKDelegate& FuncDelegate)</font>**

<font size=5>返回类型：FDelegateHandle</font>

<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| FuncDelegate                |const FunUdSDKDelegate&| 必选  |                                         std::function<void()>对象 |
