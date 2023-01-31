# UdSDK - 虚幻引擎插件<p align="right">[English](https://github.com/zengweicheng666/UdSDKProject/blob/master/README.md)</p>
此项目演示了如何在虚幻引擎实时开发平台上使用UdSDK。

```
语言:                  C#、C++
类型:                  集成
贡献者:                UdSDK开发组<support@euclideon.com>
机构:                  优立, https://www.euclideon.com/
日期:                  2022-01-20
UdSDK版本:             1.0.0
工具集:                要求虚幻引擎>= 4.27.1
```

## 快速入门指南

__虚幻——UdSDK示例需要用到一个免费的优立账户，可从[这里](https://www.euclideon.com/udsdk/)获取权限__
<br>UdSDK在虚幻引擎4.27.1版本中测试过。此插件在虚幻引擎的其他版本中也可能正常运行，但并不能保证。请确保您已安装已成功测试的版本。

### 准备工作
1. 使用您的许可证凭证在[这里](https://udstream.euclideon.com)下载并提取最后一个UdSDK安装包。您可以从[我们的官方网站](https://www.euclideon.com/free-development-resources/)获得一个免费的账户。
2. 从[这里](https://git.euclideon.cn:3000/wesley.zeng/UdSDKProject.git)克隆虚幻UdSDK示例或下载其压缩包。
![image](./Images/download.PNG)
3. 右键*UdSDKProject.uproject*，选择*Switch Unreal Engine version*，选择版本4.27并转换。您将得到*UdSDKProject.sln*。
![image](./Images/switch1.PNG)
![image](./Images/switch2.PNG)
4. 通过Microsoft Visual Studio打开*UdSDKProject.sln*，编译并调试该项目。之后会弹出一个虚幻引擎编辑器界面。现在您可在该编辑器内看到UdSDK插件。
<br>![image](./Images/udsdk1.PNG)

### 其他使用场景

1. __您也可将UdSDK应用于您的项目当中。只需将该示例的*Plugins*文件夹下的插件UdSDK拷贝到您的项目中的*Plugins*文件夹下（如果没有*plugins*文件夹则需自行创建）。__

2. __您还可将UdSDK应用于您所使用的某一版本的虚幻引擎。需将该示例*Plugins*文件夹下的插件UdSDK拷贝到目标版本的虚幻引擎目录下的*Plugins*文件夹下的*Marketplace*文件夹下（如果没有*Marketplace*文件夹则需自行创建）。之后可在虚幻编辑器的插件浏览器中找到UdSDK。__
<br>![image](./Images/plugin1.PNG)
![image](./Images/plugin2.PNG)
### 使用UdSDK

__您可以使用已注册的账户登录我们的服务器以获取Uds模型的使用权限。__
<br>![image](./Images/udsdk2.PNG)
![image](./Images/udsdk3.PNG)
<br>**资产**: 根据需要在虚幻编辑器中添加一个资产列表。登录服务器后资产列表自动获取资产或点击刷新按钮刷新资产。
![image](./Images/assets.PNG)
<br>**UDS**: 一个优立无限细节点云文件。您可通过指定url来为UDS演员分配一个具体的点云模型。
<br>![image](./Images/uds.PNG)
<br>**POI**: 描述感兴趣位置的点。
<br>**Polygon**: 一个多边形模型。通常是OBJ或FBX格式。

## 基础示例
1. 添加一个UDS演员，这里使用url''https://models.euclideon.com.cn/udDemos/SouthEastQueeland/GoldCoast_20mm.uds''
<br>![image](./Images/point_cloud.PNG)
![image](./Images/init.PNG)
2. 移动
<br>![image](./Images/move1.PNG)
![image](./Images/move2.PNG)
3. 旋转
<br>![image](./Images/rotate1.PNG)
![image](./Images/rotate2.PNG)
4. 缩放
<br>![image](./Images/scale1.PNG)
![image](./Images/scale2.PNG)
5. 隐藏和显示
<br>![image](./Images/hide1.PNG)
![image](./Images/hide2.PNG)
6. 在项目设置中可更改目标选中状态的颜色，点击*Refresh Data*后生效。
<br>![image](./Images/changecolor1.PNG)
![image](./Images/changecolor2.PNG)
![image](./Images/changecolor3.PNG)
![image](./Images/changecolor4.PNG)
7. 添加资产列表，点击刷新按钮后列表将列出从服务器获取的资产。
<br>![image](./Images/assetslist1.PNG)
8. 可按照日期、类型或添加日期对资产升序和降序排列。
<br>![image](./Images/assetslist2.PNG)
![image](./Images/assetslist3.PNG)
9. 搜索名称以找到目标资产。
<br>![image](./Images/assetslist4.PNG)
10. 添加资产到关卡中。
<br>![image](./Images/assetslist5.PNG)
![image](./Images/assetslist6.PNG)

## Demo
__"Youli"demo位于该项目目录下的Plugins\UdSDK\Content\Youli。该demo以展厅的形式展示了若干个通过UdSDK成功从服务器加载到UE4的uds模型，其中包括体育博物馆、采石场、雨林、高速公路、FZSW和黄金海岸。此外该demo还通屏幕上的滚动字幕介绍了我们公司。__

<p align="center">展厅全景</p>

<br>![image](./Images/panorama.PNG)

<p align="center">关于我们公司</p>

<br>![image](./Images/eulee1.PNG)
<br>![image](./Images/eulee2.PNG)
<br>![image](./Images/eulee3.PNG)

<p align="center">黄金海岸</p>

<br>![image](./Images/goldcoast.PNG)

<p align="center">雨林</p>

<br>![image](./Images/rainforest.PNG)

<p align="center">高速公路</p>

<br>![image](./Images/highway.PNG)

<p align="center">FZSW</p>

<br>![image](./Images/fzsw.PNG)

<p align="center">体育博物馆</p>

<br>![image](./Images/stadium.PNG)

<p align="center">采石场</p>

<br>![image](./Images/mine.PNG)
