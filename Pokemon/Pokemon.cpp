#include "Pokemon.h"

#include "PokemonController.h"

Pokemon::Pokemon(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // �Ыؤ@�� PokemonController�A�ñN ui �ǻ�����
    mpPokemonController = std::make_unique<PokemonController>(&ui, this);

}
