#include "battleController.h"

class BattleControllerPrivate :QObject {
public:
	BattleControllerPrivate(Ui::PokemonClass* ui);
	void hideMoveBtn();
	void showMoveBtn();
	void hideSceneBtn();
	void showSceneBtn();
	void hideSelectPokemonBtn();
	void showSelectPokemonBtn();

	void hideSelectBagBtn();
	void showSelectBagBtn();

	Ui::PokemonClass* ui;
};

BattleControllerPrivate::BattleControllerPrivate(Ui::PokemonClass* ui)
	:ui(ui)
{

}

void BattleControllerPrivate::hideMoveBtn() {
	ui->pb_battle_move_1->hide();
	ui->pb_battle_move_2->hide();
	ui->pb_battle_move_3->hide();
	ui->pb_battle_move_4->hide();
}

void BattleControllerPrivate::showMoveBtn() {
	ui->pb_battle_move_1->show();
	ui->pb_battle_move_2->show();
	ui->pb_battle_move_3->show();
	ui->pb_battle_move_4->show();
}

void BattleControllerPrivate::hideSceneBtn() {
	ui->pb_battle_battle->hide();
	ui->pb_battle_bag->hide();
	ui->pb_battle_pokemon->hide();
	ui->pb_battle_run->hide();
}

void BattleControllerPrivate::showSceneBtn() {
	ui->pb_battle_battle->show();
	ui->pb_battle_bag->show();
	ui->pb_battle_pokemon->show();
	ui->pb_battle_run->show();
}

void BattleControllerPrivate::hideSelectBagBtn() {
	ui->tb_battle_select_bag_1->hide();
}

void BattleControllerPrivate::showSelectBagBtn() {
	ui->tb_battle_select_bag_1->show();
}

void BattleControllerPrivate::hideSelectPokemonBtn() {
	ui->tb_battle_select_pokemon_1->hide();
}

void BattleControllerPrivate::showSelectPokemonBtn() {
	ui->tb_battle_select_pokemon_1->show();

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

	ui->tb_battle_select_pokemon_1->setIcon(QIcon(":/Pokemom/Resources/pikachu.png"));  
	ui->tb_battle_select_pokemon_1->setText("Hello, world!");
	ui->tb_battle_select_pokemon_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); 
	ui->tb_battle_select_pokemon_1->hide();

	ui->tb_battle_select_bag_1->setIcon(QIcon(":/Pokemom/Resources/potion-red.png"));
	ui->tb_battle_select_bag_1->setText("HP plus");
	ui->tb_battle_select_bag_1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	ui->tb_battle_select_bag_1->hide();
	
}

void BattleController::connection() {
	connect(ui->pb_battle_battle, &QPushButton::clicked, this, &BattleController::on_pb_battle_battle_clicked);
	connect(ui->pb_battle_back, &QPushButton::clicked, this, &BattleController::on_pb_battle_back_clicked);
	connect(ui->pb_battle_pokemon, &QPushButton::clicked, this, &BattleController::on_pb_battle_pokemon_clicked);
	connect(ui->pb_battle_bag, &QPushButton::clicked, this, &BattleController::on_pb_battle_bag_clicked);
	
}

void BattleController::on_pb_battle_battle_clicked() {
	
	mpPrivate->hideSceneBtn();

	mpPrivate->showMoveBtn();
	ui->pb_battle_back->show();
}

void BattleController::on_pb_battle_back_clicked() {
	mpPrivate->hideMoveBtn();
	mpPrivate->hideSelectPokemonBtn();
	mpPrivate->hideSelectBagBtn();
	ui->pb_battle_back->hide();

	mpPrivate->showSceneBtn();
}

void BattleController::on_pb_battle_pokemon_clicked() {
	mpPrivate->hideSceneBtn();
	mpPrivate->hideMoveBtn();

	mpPrivate->showSelectPokemonBtn();
	ui->pb_battle_back->show();
}

void BattleController::on_pb_battle_bag_clicked() {
	mpPrivate->hideSceneBtn();
	mpPrivate->hideMoveBtn();
	
	mpPrivate->showSelectBagBtn();
	ui->pb_battle_back->show();
}