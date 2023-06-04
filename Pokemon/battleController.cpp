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
	ui->text_edit_battle_content->setFontPointSize(15);
	ui->text_edit_battle_content->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Nulla porttitor massa id neque aliquam vestibulum morbi blandit cursus. Magna etiam tempor orci eu lobortis elementum. Eget lorem dolor sed viverra. Tincidunt dui ut ornare lectus sit amet. Aliquam purus sit amet luctus venenatis lectus magna. Malesuada fames ac turpis egestas maecenas pharetra. Rhoncus aenean vel elit scelerisque. Felis imperdiet proin fermentum leo vel orci. Viverra nam libero justo laoreet sit amet cursus sit amet. Adipiscing enim eu turpis egestas pretium aenean pharetra magna ac. At auctor urna nunc id cursus metus aliquam. Faucibus vitae aliquet nec ullamcorper sit amet risus nullam eget. Tincidunt nunc pulvinar sapien et ligula ullamcorper malesuada. Lorem mollis aliquam ut porttitor leo a diam sollicitudin.");
}

void BattleController::connection() {

}
