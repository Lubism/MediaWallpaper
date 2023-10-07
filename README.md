# MediaWallpaper 视频壁纸播放器

## *将播放视频投射在桌面上的播放器*

---

## 原理及依赖

播放器投射原理同 **墙纸引擎**( *Wallpaper Engine* )  

用户交互层依赖*Qt*图形库(版本 *5.15.5*)  

媒体播放层依赖*mpv*视频播放库  

使用 C++ 编写(C++ 11)

---

## 基本

支持多个屏幕同时播放，开机自启动，自定义CSS样式表，以及程序运行期间更新界面CSS样式  

程序退出时会自动保存当前播放的关键数据(时间、音量等)  

主窗口和播放列表窗口支持窗口大小记忆  

支持时间、速度、音量调整  

支持音频开关及字幕开关  

## 关于样式表

CSS样式表存放于程序根目录的 ***resources\css*** 文件夹中  

以下是读取CSS样式的图形控件:  

### 窗口

| 名称 | 文件( \widget\\~.css ) | 包含类 |
| :---: | :---: | :---: |
| 主窗口 | MainWindow | QWidget |
| 页面窗口 | PageWidget | QWidget |
| 面板窗口 | PanelWidget | QStackedWidget |
| 播放列表窗口 | PlaylistWidget | QWidget, QListWidget |

### 基本组( css\basicGroup\ )

| 名称 | 文件( ~.css ) | 包含类 |
| :---: | :---: | :---: |
| 基本组 | BasicGroupBox | QGroupBox |

| 名称 | 文件( \button\\~.css ) | 包含类 |
| :---: | :---: | :---: |
| 上一播放 | Last | QPushButton |
| 关闭音频 | Mute | QPushButton |
| 下一播放 | Next | QPushButton |
| 暂停播放 | Pause | QPushButton |
| 中止播放 | Stop | QPushButton |
| 关闭字幕 | Subtitle | QPushButton |

| 名称 | 文件( \label\\~.css ) | 包含类 |
| :---: | :---: | :---: |
| 显示器ID | DesktopID | QLabel |
| 速度标签 | SpeedLabel | QLabel |
| 音量标签 | VolumeLabel | QLabel |

| 名称 | 文件( \lineEdit\\~.css ) | 包含类 |
| :---: | :---: | :---: |
| 文件名 | FileName | QLineEdit |
| 速度显示 | SpeedDisplay | QLineEdit |
| 时间显示 | TimeDisplay | QLineEdit |
| 音量显示 | VolumeDisplay | QLineEdit |

| 名称 | 文件( \slider\\~.css ) | 包含类 |
| :---: | :---: | :---: |
| 时间调整 | PositionSlider | QSlider |
| 速度调整 | SpeedSlider | QSlider |
| 音量调整 | VolumeSlider | QSlider |

### 文件组( css\fileGroup\ )

| 名称 | 文件( ~.css ) | 包含类 |
| :---: | :---: | :---: |
| 文件组 | FileGroupBox | QGroupBox |

| 名称 | 文件( \button\\~.css ) | 包含类 |
| :---: | :---: | :---: |
| 清空面板信息 | ClearInfo | QPushButton |
| 打开播放列表 | OpenPlaylist | QPushButton |
| 刷新显示 | RefreshDisplay | QPushButton |
| 选择文件夹 | SelectFolder | QPushButton |

| 名称 | 文件( \comboBox\\~.css ) | 包含类 |
| :---: | :---: | :---: |
| 播放模式选择 | PlaymodeBox | QComboBox |

| 名称 | 文件( \label\\~.css ) | 包含类 |
| :---: | :---: | :---: |
| 播放模式标签 | PlaymodeLabel | QLabel |

| 名称 | 文件( \lineEdit\\~.css ) | 包含类 |
| :---: | :---: | :---: |
| 文件夹路径 | FolderPath | QLineEdit |

| 名称 | 文件( \messageBox\\~.css ) | 包含类 |
| :---: | :---: | :---: |
| 清空面板信息警告 | ClearInfoWarn | QMessageBox |

### 终端组( css\terminalGroup\ )

| 名称 | 文件( ~.css ) | 包含类 |
| :---: | :---: | :---: |
| 终端组 | TerminalGroupBox | QGroupBox |

| 名称 | 文件( \button\\~.css ) | 包含类 |
| :---: | :---: | :---: |
| 更新界面样式按钮 | UpdatePanelButton | QPushButton |

| 名称 | 文件( \comboBox\\~.css ) | 包含类 |
| :---: | :---: | :---: |
| 开机自启动选择 | AutobootBox | QComboBox |
| 当前面板选择 | PanelBox | QComboBox |

| 名称 | 文件( \label\\~.css ) | 包含类 |
| :---: | :---: | :---: |
| 开机自启动标签 | AutobootLabel | QComboBox |
| 当前面板标签 | PanelLabel | QComboBox |
| 更新界面样式标签 | UpdatePanelLabel | QComboBox |

### 系统托盘( css\trayIcon\ )

| 名称 | 文件( ~.css ) | 包含类 |
| :---: | :---: | :---: |
| 关于菜单 | AboutMenu | QMenu |
| 主菜单 | MainMenu | QMenu |

---

## 已知的问题

**请勿在程序运行期间修改系统时间**  
*程序会异常卡死，原因不明*  

修改系统时间的例子：**无主之地3的黑市贩卖机Bug**

---