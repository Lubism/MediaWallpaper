# MediaWallpaper 视频壁纸播放器

## *将播放视频投射在桌面上的播放器*

---

## 原理及依赖

播放器投射原理同 **墙纸引擎**( *Wallpaper Engine* )  

媒体播放层依赖*mpv*视频播放库(版本 *0.35.1*)  

界面交互层依赖*Qt*图形库(版本 *5.15.5*)  

使用 C++ 编写(C++ 11 为主)  

---

## 基本

支持多个屏幕同时播放, 开机自启动, 自定义CSS样式表, 以及程序运行期间更新界面CSS样式  

程序退出时会自动保存当前播放的关键数据(时间、音量、播放速度等)  

主窗口和播放列表窗口支持窗口大小记忆  

支持时间、速度、音量调整  

支持音频开关及字幕开关  

支持自定义参数调整  

仅使用本地资源播放  

### 注意

托盘形式为启动后默认形式, 如需调整, 请双击打开界面,  

或右键打开菜单, 点击 **显示** 打开界面。   

---

## 使用方法

### 播放视频

1. 打开程序
2. 在终端组中选择想要投射的显示器
3. 点击 "选择文件夹" 按钮, 弹出一个选择窗口
4. 选择想要播放的 **视频** 文件夹后点击确定
5. 视频将自动播放, 可通过面板调整视频的音量、速度等参数

### 切换面板与开机自启动

1. 在终端组中有两个选项: **当前面板** 和 **开机启动**;  
2. **开机启动** 选项控制系统启动时启动该程序,  
3. **当前面板** 选项控制右侧的面板窗口。  

---

## 关于自动保存

### 面板

每个面板对应一个数据文件, 文件均存放于程序根目录的 ***mediaData*** 文件夹中  

播放视频的数据将在程序退出时或关机时, 自动保存至对应的数据文件  

### 程序主界面

主界面支持大小记忆, 数据存放于程序根目录的 ***mainWindow.dat*** 文件中  

程序退出时或关机时会自动保存到文件中

### 注意事项

保存的数据文件均为二进制形式,  

任何以非二进制打开并保存的方式将可能破坏文件内容  

---

## 关于参数文件(.conf)

每个面板对应一个参数文件, 文件均存放于程序根目录的 ***mediaData\config*** 文件夹中  

这些参数文件会在程序启动时读取一次, 可点击 **刷新显示** 按钮读取更新  

### 注意事项

参数文件为文本格式, 且不会在程序启动时自动创建, 请自行创建  

### 参数文件命名规范

screen#X.conf (X 为显示屏索引, 从0开始计数)  

### 参数设置参考

官方: https://mpv.io/manual/master/

中文: https://hooke007.github.io/

---

## 关于样式表

CSS样式表存放于程序根目录的 ***resources\css*** 文件夹中  

这些样式表会在程序启动时读取一次, 可点击 **更新界面样式** 按钮读取更新  

**以下是读取CSS样式的图形控件:**  

### 窗口

| 名称			| 文件( \widget\\~.css )		| 包含类					|
| :---:			| :---:						| :---:					|
| 主窗口			| MainWindow				| QWidget				|
| 页面窗口		| PageWidget				| QWidget				|
| 播放窗口		| MediaWidget				| QWidget				|
| 面板窗口		| PanelWidget				| QStackedWidget		|
| 播放列表窗口	| PlaylistWidget			| QWidget, QListWidget	|

### 基本组( css\basicGroup\ )

| 名称		| 文件( ~.css )				| 包含类			|
| :---:		| :---:						| :---:			|
| 基本组		| BasicGroupBox				| QGroupBox		|

| 名称		| 文件( \button\\~.css )		| 包含类			|
| :---:		| :---:						| :---:			|
| 上一播放	| Last						| QPushButton	|
| 关闭音频	| Mute						| QPushButton	|
| 下一播放	| Next						| QPushButton	|
| 暂停播放	| Pause						| QPushButton	|
| 中止播放	| Stop						| QPushButton	|
| 关闭字幕	| Subtitle					| QPushButton	|

| 名称		| 文件( \label\\~.css )		| 包含类			|
| :---:		| :---:						| :---:			|
| 显示器ID	| DesktopID					| QLabel		|
| 速度标签	| SpeedLabel				| QLabel		|
| 音量标签	| VolumeLabel				| QLabel		|

| 名称		| 文件( \lineEdit\\~.css )	| 包含类			|
| :---:		| :---:						| :---:			|
| 文件名		| FileName					| QLineEdit		|
| 速度显示	| SpeedDisplay				| QLineEdit		|
| 时间显示	| TimeDisplay				| QLineEdit		|
| 音量显示	| VolumeDisplay				| QLineEdit		|

| 名称		| 文件( \slider\\~.css )		| 包含类			|
| :---:		| :---:						| :---:			|
| 时间调整	| PositionSlider			| QSlider		|
| 速度调整	| SpeedSlider				| QSlider		|
| 音量调整	| VolumeSlider				| QSlider		|

### 文件组( css\fileGroup\ )

| 名称				| 文件( ~.css )					| 包含类			|
| :---:				| :---:							| :---:			|
| 文件组				| FileGroupBox					| QGroupBox		|

| 名称				| 文件( \button\\~.css )			| 包含类			|
| :---:				| :---:							| :---:			|
| 清空面板信息		| ClearInfo						| QPushButton	|
| 打开播放列表		| OpenPlaylist					| QPushButton	|
| 刷新显示			| RefreshDisplay				| QPushButton	|
| 选择文件夹			| SelectFolder					| QPushButton	|

| 名称				| 文件( \comboBox\\~.css )		| 包含类			|
| :---:				| :---:							| :---:			|
| 播放模式选择		| PlaymodeBox					| QComboBox		|

| 名称				| 文件( \label\\~.css )			| 包含类			|
| :---:				| :---:							| :---:			|
| 播放模式标签		| PlaymodeLabel					| QLabel		|

| 名称				| 文件( \lineEdit\\~.css )		| 包含类			|
| :---:				| :---:							| :---:			|
| 文件夹路径			| FolderPath					| QLineEdit		|

| 名称				| 文件( \messageBox\\~.css )		| 包含类			|
| :---:				| :---:							| :---:			|
| 清空面板信息警告	| ClearInfoWarn					| QMessageBox	|

### 终端组( css\terminalGroup\ )

| 名称				| 文件( ~.css )				| 包含类			|
| :---:				| :---:						| :---:			|
| 终端组				| TerminalGroupBox			| QGroupBox		|

| 名称				| 文件( \button\\~.css )		| 包含类			|
| :---:				| :---:						| :---:			|
| 更新界面样式按钮	| UpdatePanelButton			| QPushButton	|

| 名称				| 文件( \comboBox\\~.css )	| 包含类			|
| :---:				| :---:						| :---:			|
| 开机自启动选择		| AutobootBox				| QComboBox		|
| 当前面板选择		| PanelBox					| QComboBox		|

| 名称				| 文件( \label\\~.css )		| 包含类			|
| :---:				| :---:						| :---:			|
| 开机自启动标签		| AutobootLabel				| QComboBox		|
| 当前面板标签		| PanelLabel				| QComboBox		|
| 更新界面样式标签	| UpdatePanelLabel			| QComboBox		|

### 系统托盘( css\trayIcon\ )

| 名称		| 文件( ~.css )	| 包含类		|
| :---:		| :---:			| :---:		|
| 关于菜单	| AboutMenu		| QMenu		|
| 主菜单		| MainMenu		| QMenu		|

---

## 已知的问题

### 请勿在程序运行期间修改系统时间

*程序会异常卡死，原因不明*  

修改系统时间的例子: **无主之地3的黑市贩卖机Bug**

### 仅支持 Windows 64位系统, Linux系统暂不支持(没用过)

程序播放视频时将占用至少 **100 MB** 大小的运行内存  

如有多个屏幕播放视频, 建议拥有至少 **32 GB** 大小的运行内存  

---