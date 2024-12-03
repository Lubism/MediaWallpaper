#include"UI/Data/StyleSheet.hpp"

#include"PlaylistPanel.hpp"

using namespace UI;

void PlaylistPanel::importList(const std::vector<QString>& playlist)
{
	this->clear();

	FileCount = playlist.size();
	for (auto& it : playlist)
		this->addItem(it);

	this->setCurrentIndex(0);
}

void PlaylistPanel::updateStyleSheet()
{
	StyleSheet::Set(this, "PlaylistPanel");
}
