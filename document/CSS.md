# 关于样式表

CSS样式表存放于程序根目录的 ***resources\css*** 文件夹中  

这些样式表会在程序启动时读取一次, 可点击 **更新界面样式** 按钮读取更新  

**以下是读取CSS样式的图形控件:**  

## 窗口

| 名称			| 文件( \widget\\~.css )		| 包含类					|
| :---:			| :---:						| :---:					|
| 主窗口			| MainWindow				| QWidget				|
| 页面窗口		| PageWidget				| QWidget				|
| 播放窗口		| MediaWidget				| QWidget				|
| 面板窗口		| PanelWidget				| QStackedWidget		|
| 播放列表窗口	| PlaylistWidget			| QWidget, QListWidget	|

## 基本组( css\basicGroup\ )

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

## 文件组( css\fileGroup\ )

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

## 终端组( css\terminalGroup\ )

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

## 系统托盘( css\trayIcon\ )

| 名称		| 文件( ~.css )	| 包含类		|
| :---:		| :---:			| :---:		|
| 关于菜单	| AboutMenu		| QMenu		|
| 主菜单		| MainMenu		| QMenu		|