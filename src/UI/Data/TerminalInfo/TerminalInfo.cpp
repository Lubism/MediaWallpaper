#include"TerminalInfo.hpp"

using namespace UI;

const QString TerminalInfo::Path = "./mediaData/TerminalInfo.json";
JsonIO::Map TerminalInfo::Map = JsonIO::Map();

QString TerminalInfo::Lang = QString();
QString TerminalInfo::Font = QString();
bool TerminalInfo::Startup = false;

int TerminalInfo::Fontsize = 10;
int TerminalInfo::Height = 280;
int TerminalInfo::Width = 660;
