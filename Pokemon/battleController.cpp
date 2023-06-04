#include "battleController.h"

class BattleControllerPrivate :QObject {
public:
	BattleControllerPrivate(Ui::PokemonClass* ui);
	

	Ui::PokemonClass* ui;
};

BattleControllerPrivate::BattleControllerPrivate(Ui::PokemonClass* ui)
	:ui(ui)
{

}

BattleController::BattleController(Ui::PokemonClass* ui, QObject* parent)
	: QObject(parent)
	, ui(ui)
	, mpPrivate(std::make_unique<BattleControllerPrivate>(ui))
{
	connection();

	ui->pb_battle_back->hide();
}

void BattleController::connection() {

}
