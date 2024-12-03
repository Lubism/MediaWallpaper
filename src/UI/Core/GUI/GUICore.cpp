#include"UI/Panel/Terminal/TerminalPanel.hpp"
#include"UI/Panel/Playlist/PlaylistPanel.hpp"
#include"UI/Panel/Display/DisplayPanel.hpp"
#include"UI/Panel/Basic/BasicPanel.hpp"
#include"UI/Panel/File/FilePanel.hpp"

#include"UI/Data/Translator/Translator.hpp"

#include"GUICore.hpp"

using namespace UI;

GUICore::~GUICore()
{
}

void GUICore::allocation()
{
	Terminal = new TerminalPanel(this);
	Playlist = new PlaylistPanel(this);
	Display = new DisplayPanel(this);
	Basic = new BasicPanel(this);
	File = new FilePanel(this);
}

void GUICore::connection()
{
	this->fileConnection();
	this->basicConnection();
	this->displayConnection();
	this->playlistConnection();
	this->terminalConnection();
}

void GUICore::initialization()
{
	this->addTab(Basic, "Basic");
	this->addTab(File, "File");

	this->addTab(Playlist, "Playlist");
	this->addTab(Display, "Display");

	this->addTab(Terminal, "Terminal");
}

void GUICore::fileConnection()
{
	connect(File, &FilePanel::directorySelected, this, [&](const QString& path) {
		emit this->loadFile(path);
		});

	connect(File, &FilePanel::atFullscreen, this, [&](int mode) {
		Info.AtFullscreen = mode;
		emit this->sendInfo(Info);
		});
	connect(File, &FilePanel::playmode, this, [&](int mode) {
		Info.Playmode = mode;
		emit this->sendInfo(Info);
		});
	connect(File, &FilePanel::atFocus, this, [&](int mode) {
		Info.AtFocus = mode;
		emit this->sendInfo(Info);
		});

	connect(File, &FilePanel::updatePlaylist, this, [&]() {
		emit this->updatePlaylist();
		});
	connect(File, &FilePanel::loadConfig, this, [&]() {
		emit this->loadConfig();
		});
	connect(File, &FilePanel::clearInfo, this, [&]() {
		emit this->clearInfo();
		});
}

void GUICore::basicConnection()
{
	connect(Basic, &BasicPanel::subtitle, this, [&](bool value) {
		Info.Subtitle = value;
		emit this->sendInfo(Info);
		});
	connect(Basic, &BasicPanel::volume, this, [&](double value) {
		Info.Volume = value;
		emit this->sendInfo(Info);
		});
	connect(Basic, &BasicPanel::speed, this, [&](double value) {
		Info.Speed = value;
		emit this->sendInfo(Info);
		});
	connect(Basic, &BasicPanel::pause, this, [&](bool value) {
		Info.Pause = value;
		emit this->sendInfo(Info);
		});
	connect(Basic, &BasicPanel::mute, this, [&](bool value) {
		Info.Mute = value;
		emit this->sendInfo(Info);
		});
	connect(Basic, &BasicPanel::time, this, [&](double value) {
		Info.Position = value;
		emit this->sendInfo(Info);
		});

	connect(Basic, &BasicPanel::last, this, [&]() {
		emit this->last();
		});
	connect(Basic, &BasicPanel::next, this, [&]() {
		emit this->next();
		});
	connect(Basic, &BasicPanel::stop, this, [&]() {
		emit this->stop();
		});
}

void GUICore::displayConnection()
{
	connect(Display, &DisplayPanel::brightness, this, [&](long long value) {
		Info.Display.Brightness = value;
		emit this->sendInfo(Info);
		});
	connect(Display, &DisplayPanel::saturation, this, [&](long long value) {
		Info.Display.Saturation = value;
		emit this->sendInfo(Info);
		});
	connect(Display, &DisplayPanel::contrast, this, [&](long long value) {
		Info.Display.Contrast = value;
		emit this->sendInfo(Info);
		});
	connect(Display, &DisplayPanel::rotate, this, [&](long long value) {
		Info.Display.Rotate = value;
		emit this->sendInfo(Info);
		});
	connect(Display, &DisplayPanel::gamma, this, [&](long long value) {
		Info.Display.Gamma = value;
		emit this->sendInfo(Info);
		});
	connect(Display, &DisplayPanel::hue, this, [&](long long value) {
		Info.Display.Hue = value;
		emit this->sendInfo(Info);
		});

	connect(Display, &DisplayPanel::align, this, [&](double halign, double valign) {
		Info.Display.HAlign = halign;
		Info.Display.VAlign = valign;
		emit this->sendInfo(Info);
		});
	connect(Display, &DisplayPanel::aspectRatio, this, [&](double value) {
		Info.Display.AspectRatio = value;
		emit this->sendInfo(Info);
		});
	connect(Display, &DisplayPanel::panscan, this, [&](double value) {
		Info.Display.Panscan = value;
		emit this->sendInfo(Info);
		});

	connect(Display, &DisplayPanel::flip, this, [&](bool hflip, bool vflip) {
		Info.Display.HFlip = hflip;
		Info.Display.VFlip = vflip;
		emit this->sendInfo(Info);
		});
}

void GUICore::playlistConnection()
{
	connect(Playlist, &PlaylistPanel::fileSelected, this, [&](int index) {
		Info.Index = index;
		emit this->sendInfo(Info);
		});
}

void GUICore::terminalConnection()
{
	connect(Terminal, &TerminalPanel::selectMonitor, this, [&](int index) {
		emit this->selectMonitor(index);
		});
	connect(Terminal, &TerminalPanel::updateStyleSheet, this, [&]() {
		emit this->updateStyleSheet();
		});
	connect(Terminal, &TerminalPanel::updateLanguage, this, [&]() {
		emit this->updateLanaguage();
		});
	connect(Terminal, &TerminalPanel::updatePlaylist, this, [&]() {
		emit this->updatePlaylist();
		});
	connect(Terminal, &TerminalPanel::loadAllConfig, this, [&]() {
		emit this->loadAllConfig();
		});
}

void GUICore::importPlaylist(const std::vector<QString>& playlist)
{
	Playlist->importList(playlist);
}

void GUICore::receiveInfo(const StreamInfo& info)
{
	Basic->setMonitorID(QString::number(info.MonitorID));
	Basic->setTime(info.Duration, info.Position);

	Basic->setSubtitle(info.Subtitle);
	Basic->setPause(info.Pause);
	Basic->setMute(info.Mute);

	Basic->setFileName(info.Name);
	Basic->setVolume(info.Volume);
	Basic->setSpeed(info.Speed);

	File->setAtFullscreen(info.AtFullscreen);
	File->setDirectory(info.Directory);
	File->setPlaymode(info.Playmode);
	File->setAtFocus(info.AtFocus);

	Playlist->setCurrentIndex(info.Index);

	auto& dpy = info.Display;

	Display->setBrightness(dpy.Brightness);
	Display->setSaturation(dpy.Saturation);
	Display->setContrast(dpy.Contrast);

	Display->setRotate(dpy.Rotate);
	Display->setGamma(dpy.Gamma);
	Display->setHue(dpy.Hue);

	Display->setAspectRatio(dpy.AspectRatio);
	Display->setPanscan(dpy.Panscan);

	Display->setAlign(dpy.HAlign, dpy.VAlign);
	Display->setFlip(dpy.HFlip, dpy.VFlip);

	Info = info;
}

void GUICore::setMonitor(int index)
{
	Terminal->setMonitor(index);
}

void GUICore::doUpdateStyleSheet()
{
	Terminal->doUpdateStyleSheet();
	Playlist->updateStyleSheet();
	Display->updateStyleSheet();
	Basic->updateStyleSheet();
	File->updateStyleSheet();
}

void GUICore::doUpdateLanguage()
{
	this->setTabText(0, Translator::Acquire("BasicPanel", "Basic"));
	this->setTabText(1, Translator::Acquire("FilePanel", "File"));

	this->setTabText(2, Translator::Acquire("PlaylistPanel", "Playlist"));
	this->setTabText(3, Translator::Acquire("DisplayPanel", "Display"));

	this->setTabText(4, Translator::Acquire("TerminalPanel", "Terminal"));

	Terminal->doUpdateLanguage();
	Display->updateLanguage();
	Basic->updateLanguage();
	File->updateLanguage();
}

void GUICore::readInfo()
{
	Terminal->readInfo();
}
