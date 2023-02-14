# 使用入门
__1.注册udStream账号__
<br><br>虚幻UdSDK示例需要用到一个免费的优立账户，可从[这里](https://www.euclideon.com/udsdk/)获取权限__
<br><br><br>__2.整体架构__
<br><br>__udUE SDK__
<br><br>__ⅰ.基础功能模块__
<br>__业务功能__
<br>点云
<br>兴趣点
<br>Polygon
<br><br>__通用__
<br>核心
<br>配置
<br>日志
<br><br>__工具集__
<br>单例
<br>线程池
<br>Json解析
<br>Json封装
<br><br>__ⅱ.第三方库模块__
<br>udSDK
<br><br>__ⅲ.用户界面模块__
<br>登录界面
<br>主菜单界面
<br>添加资产界面
<br>快速添加界面
<br><br>__ⅳ.UE插件桥接模块__
<br><br><br>__3.代码下载__
<br><br>使用您的许可证凭证在[这里](https://udstream.euclideon.com)下载并提取最后一个UdSDK安装包。您可以从[我们的官方网站](https://www.euclideon.com/free-development-resources/)获得一个免费的账户。
<br><br>从[这里](https://git.euclideon.cn:3000/wesley.zeng/UdSDKProject.git)克隆虚幻UdSDK示例或下载其压缩包。
![image](./Images/download.PNG)
<br><br><br>__4.快速上手__
<br><br>__ⅰ.转换项目版本__
<br><br>右键*UdSDKProject.uproject*，选择*Switch Unreal Engine version*，选择版本4.27并转换。您将得到*UdSDKProject.sln*。
![image](./Images/switch1.PNG)
![image](./Images/switch2.PNG)
<br><br>__ⅱ.导入插件__
<br><br>通过Microsoft Visual Studio打开*UdSDKProject.sln*，编译并调试该项目。之后会弹出一个虚幻引擎编辑器界面。现在您可在该编辑器内看到UdSDK插件。
<br>![image](./Images/udsdk1.PNG)
<br><br>__ⅲ.其他使用场景__
<br><br>您也可将UdSDK应用于您的项目当中。只需将该示例的*Plugins*文件夹下的插件UdSDK拷贝到您的项目中的*Plugins*文件夹下（如果没有*plugins*文件夹则需自行创建）。__
<br><br>您还可将UdSDK应用于您所使用的某一版本的虚幻引擎。需将该示例*Plugins*文件夹下的插件UdSDK拷贝到目标版本的虚幻引擎目录下的*Plugins*文件夹下的*Marketplace*文件夹下（如果没有*Marketplace*文件夹则需自行创建）。之后可在虚幻编辑器的插件浏览器中找到UdSDK。__
<br>![image](./Images/plugin1.PNG)
![image](./Images/plugin2.PNG)
<br><br>__ⅳ.获取uds模型权限__
<br><br>您可以使用已注册的账户登录我们的服务器以获取uds模型的使用权限。
<br>![image](./Images/udsdk3.PNG)
<br><br>__ⅴ.添加资产列表__
<br><br>根据需要在虚幻编辑器中添加一个资产列表。登录服务器后资产列表自动获取资产或点击刷新按钮刷新资产。
![image](./Images/assets.PNG)
<br><br>__ⅵ.获取模型地址__
<br><br>**UDS：** 一个优立无限细节点云文件。您可通过指定url来为UDS actor分配一个具体的点云模型。
<br>![image](./Images/uds.PNG)
<br><br>__ⅶ.基础功能__
<br><br>1.添加actor：
<br>添加一个UDS actor，这里使用url''https://models.euclideon.com.cn/udDemos/SouthEastQueeland/GoldCoast_20mm.uds''
<br>![image](./Images/point_cloud.PNG)
![image](./Images/init.PNG)
<br><br>2.移动操作示意：
<br>![image](./Images/move1.PNG)
![image](./Images/move2.PNG)
<br><br>3.旋转操作示意：
<br>![image](./Images/rotate1.PNG)
![image](./Images/rotate2.PNG)
<br><br>4.缩放操作示意：
<br>![image](./Images/scale1.PNG)
![image](./Images/scale2.PNG)
<br><br>5.隐藏和显示操作示意：
<br>![image](./Images/hide1.PNG)
![image](./Images/hide2.PNG)
<br><br>6.模型选中状态显示：
<br>在项目设置中可更改目标选中状态的颜色，点击*Refresh Data*后生效。
<br>![image](./Images/changecolor1.PNG)
![image](./Images/changecolor2.PNG)
![image](./Images/changecolor3.PNG)
![image](./Images/changecolor4.PNG)
<br><br>7.添加资产列表：
<br>添加资产列表，点击刷新按钮后列表将列出从服务器获取的资产。
<br>![image](./Images/assetslist1.PNG)
<br><br>8.资产排序：
<br>可按照日期、类型或添加日期对资产升序和降序排列。
<br>![image](./Images/assetslist2.PNG)
![image](./Images/assetslist3.PNG)
<br><br>9.资产搜索：
<br>搜索名称以找到目标资产。
<br>![image](./Images/assetslist4.PNG)
<br><br>10.资产添加：
<br>添加资产到关卡中。
<br>![image](./Images/assetslist5.PNG)
![image](./Images/assetslist6.PNG)
<br><br><br>__5.项目示例__
<br><br>**项目介绍：**
"Youli"demo位于该项目目录下的Plugins\UdSDK\Content\Youli。该demo以展厅的形式展示了若干个通过UdSDK成功从服务器加载到UE4的uds模型，其中包括体育博物馆、采石场、雨林、高速公路、FZSW和黄金海岸。此外该demo还通屏幕上的滚动字幕介绍了我们公司。

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
