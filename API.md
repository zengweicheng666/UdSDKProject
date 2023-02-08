# 登录登出
<font size=5>该章节将介绍登录和登出udUE SDK的方法。此外还讲解了如何绑定委托，才能在登录和登出udUE SDK时执行额外的操作。</font>
## 登录
**<font size=5>Login()</font>**

<font size=5>返回类型：bool</font>
## 登录状态
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
| FuncDelegate                |const FunUdSDKDelegate&| 必选  |                                         仿函数（函数对象） |

## 绑定委托到登出时
**<font size=5>AddExitDelegateLambda(const FunUdSDKDelegate& FuncDelegate)</font>**

<font size=5>返回类型：FDelegateHandle</font>

<font size=5>参数类型：</font>
| 参数                        |         类型          | 属性  |                                             描述 |
| --------------------------- | :-------------------: | :---: | -----------------------------------------------: |
| FuncDelegate                |const FunUdSDKDelegate&| 必选  |                                         仿函数（函数对象） |
# 设置
<font size=5>该章节将介绍udUE SDK插件设置栏里的内容，以及如何加载和保存设置。</font>
