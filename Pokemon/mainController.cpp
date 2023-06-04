#include "mainController.h"

class MainControllerPrivate :QObject {
public:
	MainControllerPrivate(Ui::PokemonClass* ui);
	QString getOpenFileName();
	void updateBattleButtonState();
	
	
	Ui::PokemonClass* ui;
};

MainControllerPrivate::MainControllerPrivate(Ui::PokemonClass* ui)
:ui(ui)
{

}

QString MainControllerPrivate::getOpenFileName() {
	return QFileDialog::getOpenFileName(nullptr,
		tr("Open File"), "",
		tr("All Files (*)"));
}

void MainControllerPrivate::updateBattleButtonState() {
	bool allLabelsHaveContent = !(ui->lbl_pokemon->text().isEmpty() ||
		ui->lbl_move->text().isEmpty() ||
		ui->lbl_game->text().isEmpty());

	ui->pb_battle->setEnabled(allLabelsHaveContent);
}

MainController::MainController(Ui::PokemonClass* ui, QObject* parent)
	: QObject(parent)
	, ui(ui)
	, mpPrivate(std::make_unique<MainControllerPrivate>(ui))
{
	connection();
}

void MainController::connection() {
	connect(ui->pb_test_case, &QPushButton::clicked, this, &MainController::on_pb_test_case_clicked);
	connect(ui->pb_pokemon, &QPushButton::clicked, this, &MainController::on_pb_pokemon_clicked);
	connect(ui->pb_move, &QPushButton::clicked, this, &MainController::on_pb_move_clicked);
	connect(ui->pb_game, &QPushButton::clicked, this, &MainController::on_pb_game_clicked);
	connect(ui->pb_battle, &QPushButton::clicked, this, &MainController::on_pb_battle_case_clicked);
}

void MainController::on_pb_test_case_clicked()
{
	auto fileName = mpPrivate->getOpenFileName();

	if (!fileName.isEmpty()) {
		QFileInfo fileInfo(fileName);
		ui->lbl_test_case->setText(fileInfo.fileName());
	}
}

void MainController::on_pb_pokemon_clicked() {
	auto fileName = mpPrivate->getOpenFileName();

	if (!fileName.isEmpty()) {
		QFileInfo fileInfo(fileName);
		ui->lbl_pokemon->setText(fileInfo.fileName());
	}
	mpPrivate->updateBattleButtonState();
}
void MainController::on_pb_move_clicked() {
	auto fileName = mpPrivate->getOpenFileName();

	if (!fileName.isEmpty()) {
		QFileInfo fileInfo(fileName);
		ui->lbl_move->setText(fileInfo.fileName());
	}
	mpPrivate->updateBattleButtonState();
}
void MainController::on_pb_game_clicked() {
	auto fileName = mpPrivate->getOpenFileName();

	if (!fileName.isEmpty()) {
		QFileInfo fileInfo(fileName);
		ui->lbl_game->setText(fileInfo.fileName());
	}
	mpPrivate->updateBattleButtonState();
}
void MainController::on_pb_battle_case_clicked() {
	ui->stackedWidget->setCurrentWidget(ui->page_battle);
}


