#include "Pokemon.h"

Pokemon::Pokemon(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    mpMainController = std::make_unique<MainController>(&ui, this);
    mpBattleController = std::make_unique<BattleController>(&ui, this);
}
