#include "PokemonController.h"

class PokemonControllerPrivate :QObject {
public:
	PokemonControllerPrivate(Ui::PokemonClass* ui);
	QString getOpenFileName();
	void updateBattleButtonState();
	
	
	Ui::PokemonClass* ui;
};

PokemonControllerPrivate::PokemonControllerPrivate(Ui::PokemonClass* ui)
:ui(ui)
{

}

QString PokemonControllerPrivate::getOpenFileName() {
	return QFileDialog::getOpenFileName(nullptr,
		tr("Open File"), "",
		tr("All Files (*)"));
}

void PokemonControllerPrivate::updateBattleButtonState() {
	bool allLabelsHaveContent = !(ui->lbl_pokemon->text().isEmpty() ||
		ui->lbl_move->text().isEmpty() ||
		ui->lbl_game->text().isEmpty());

	ui->pb_battle->setEnabled(allLabelsHaveContent);
}

PokemonController::PokemonController(Ui::PokemonClass* ui, QObject* parent)
	: QObject(parent)
	, ui(ui)
	, mpPrivate(std::make_unique<PokemonControllerPrivate>(ui))
{
	connection();
}

void PokemonController::connection() {
	connect(ui->pb_test_case, &QPushButton::clicked, this, &PokemonController::on_pb_test_case_clicked);
	connect(ui->pb_pokemom, &QPushButton::clicked, this, &PokemonController::on_pb_pokemon_clicked);
	connect(ui->pb_move, &QPushButton::clicked, this, &PokemonController::on_pb_move_clicked);
	connect(ui->pb_game, &QPushButton::clicked, this, &PokemonController::on_pb_game_clicked);
}

void PokemonController::on_pb_test_case_clicked()
{
	auto fileName = mpPrivate->getOpenFileName();

	if (!fileName.isEmpty()) {
		QFileInfo fileInfo(fileName);
		ui->lbl_test_case->setText(fileInfo.fileName());
	}
}

void PokemonController::on_pb_pokemon_clicked() {
	auto fileName = mpPrivate->getOpenFileName();

	if (!fileName.isEmpty()) {
		QFileInfo fileInfo(fileName);
		ui->lbl_pokemon->setText(fileInfo.fileName());
	}
	mpPrivate->updateBattleButtonState();
}
void PokemonController::on_pb_move_clicked() {
	auto fileName = mpPrivate->getOpenFileName();

	if (!fileName.isEmpty()) {
		QFileInfo fileInfo(fileName);
		ui->lbl_move->setText(fileInfo.fileName());
	}
	mpPrivate->updateBattleButtonState();
}
void PokemonController::on_pb_game_clicked() {
	auto fileName = mpPrivate->getOpenFileName();

	if (!fileName.isEmpty()) {
		QFileInfo fileInfo(fileName);
		ui->lbl_game->setText(fileInfo.fileName());
	}
	mpPrivate->updateBattleButtonState();
}
void PokemonController::on_pb_battle_case_clicked() {
	// TODO: Move to the battle scene
}


