#include "Pokemon.h"

#include "PokemonController.h"

Pokemon::Pokemon(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // 創建一個 PokemonController，並將 ui 傳遞給它
    mpPokemonController = std::make_unique<PokemonController>(&ui, this);

}
