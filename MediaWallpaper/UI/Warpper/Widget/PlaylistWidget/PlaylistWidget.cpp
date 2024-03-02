#include"UI/Warpper/Data/Translator/Translator.hpp"
#include"UI/Warpper/Data/StyleSheet.hpp"
#include<QListWidget>
#include<QGridLayout>

#include"PlaylistWidget.hpp"

using namespace UI;

void PlaylistWidget::updateStyleSheet()
{
	StyleSheet::Set(this, "PlaylistWidget");
}

void PlaylistWidget::updateLanguage()
{
	auto receive = [](const QString& name) {return Translator::Acquire("PlaylistGroup", name); };
	if (!Translator::TranslationAvaliable()) return;
	this->setWindowTitle(receive("Playlist"));
}
