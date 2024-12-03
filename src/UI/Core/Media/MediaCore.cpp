#include"UI/Data/ShellWindow/ShellWindow.hpp"
#include"UI/Data/StyleSheet.hpp"

#include"UI/Panel/Media/MediaPanel.hpp"

#include"MediaCore.hpp"

using namespace UI;

MediaCore::~MediaCore()
{
	for (auto& it : Panels)
		delete it;

	Panel = nullptr;
	ShellWindow::RefreshDisplay();
}

void MediaCore::allocation()
{
	int len = ShellWindow::ScreenCount();
	for (auto it = 0; it < len; ++it) {
		Panels.push_back(new MediaPanel(it));
	}

	Panel = Panels.at(0);
}

void MediaCore::emitExportPlaylist()
{
	emit this->exportPlaylist(
		Panel->playlist()
	);
}

void MediaCore::receiveInfo(const StreamInfo& info)
{
	if (Panel == nullptr) return;
	Panel->setStreamInfo(info);
}

const StreamInfo& MediaCore::sendInfo()
{
	if (Panel == nullptr) return EmptyInfo;
	return Panel->streamInfo();
}

void MediaCore::updateStyleSheet()
{
	for (auto& it : Panels) it->updateStyleSheet();
}

void MediaCore::loadFile(const QString& path)
{
	if (Panel == nullptr) return;
	Panel->loadFile(path);

	if (Panel->isFileLoaded())
		Panel->play();

	emit this->exportPlaylist(Panel->playlist());
}

void MediaCore::setMonitor(int desktopID)
{
	if (desktopID < 0 || desktopID >= ShellWindow::ScreenCount())
		return;

	if (!Locker.try_lock()) return;

	Panel = Panels.at(desktopID);
	DesktopID = desktopID;

	Locker.unlock();
	this->emitExportPlaylist();
}

void MediaCore::checkWindowState()
{
	auto info = ShellWindow::AcqiureState();
	if (info.first < 0)
		return;

	Panels.at(info.first)->checkWindowState(
		info.second);
}

void MediaCore::updatePlaylist()
{
	if (Panel == nullptr)
		return;

	Panel->updatePlaylist();
	this->emitExportPlaylist();
}

void MediaCore::loadAllConfig()
{
	for (auto& it : Panels)
		it->loadConfig();
}

void MediaCore::loadConfig()
{
	if (Panel == nullptr) return;
	Panel->loadConfig();
}

bool MediaCore::isRunning() const
{
	bool result = false;

	for (const auto& it : Panels)
	{
		result |= it->isFileLoaded();
	}

	return result;
}

void MediaCore::saveInfo() const
{
	for (const auto& it : Panels)
		it->saveInfo();
}

void MediaCore::clearInfo()
{
	if (Panel == nullptr)
		return;

	Panel->clearInfo();
	this->emitExportPlaylist();
}

void MediaCore::readInfo()
{
	for (auto& it : Panels) it->readInfo();
	if (Panel == nullptr) return;
	this->emitExportPlaylist();
}

void MediaCore::last()
{
	if (Panel == nullptr) return;
	Panel->last();
}

void MediaCore::next()
{
	if (Panel == nullptr) return;
	Panel->next();
}

void MediaCore::stop()
{
	if (Panel == nullptr) return;
	Panel->stop();
}
