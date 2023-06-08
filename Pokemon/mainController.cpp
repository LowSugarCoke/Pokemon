#include "mainController.h"
#include "pokemonService.h"

#include <map>

#include <QMessageBox>




class MainControllerPrivate :QObject {
public:
    MainControllerPrivate(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService);

    std::shared_ptr<PokemonService> mpPokemonService;

    QString getOpenFileName();
    void updateBattleButtonState();

    std::string mTestFile;
    std::string mGameFile;
    std::string mPokemonFile;
    std::string mMoveFile;
    std::function<void()> mBattleRefresh;
    std::function<void()> mSetTest;
    Ui::PokemonClass* ui;
};

MainControllerPrivate::MainControllerPrivate(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService)
    :ui(ui)
    , mpPokemonService(pPokemonService)
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

MainController::MainController(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService, QObject* parent)
    : QObject(parent)
    , ui(ui)
    , mpPrivate(std::make_unique<MainControllerPrivate>(ui, pPokemonService))
{
    connection();

    // For test
    mpPrivate->mGameFile = "GameData.txt";
    mpPrivate->mPokemonFile = "PokemonLib.txt";
    mpPrivate->mMoveFile = "MoveLib.txt";

}

void MainController::connection() {
    connect(ui->pb_test_case, &QPushButton::clicked, this, &MainController::onPBTestCaseClicked);
    connect(ui->pb_pokemon, &QPushButton::clicked, this, &MainController::onPBPokemonClicked);
    connect(ui->pb_move, &QPushButton::clicked, this, &MainController::onPBMoveClicked);
    connect(ui->pb_game, &QPushButton::clicked, this, &MainController::onPBGameClicked);
    connect(ui->pb_battle, &QPushButton::clicked, this, &MainController::onPBBattleCaseClicked);
}

void MainController::onPBTestCaseClicked()
{
    auto fileName = mpPrivate->getOpenFileName();

    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        ui->lbl_test_case->setText(fileInfo.fileName());
        mpPrivate->mTestFile = fileName.toStdString();
    }
    mpPrivate->mpPokemonService->loadTestData(mpPrivate->mTestFile);

}

void MainController::onPBPokemonClicked() {
    auto fileName = mpPrivate->getOpenFileName();

    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        ui->lbl_pokemon->setText(fileInfo.fileName());
        mpPrivate->mPokemonFile = fileName.toStdString();
    }
    mpPrivate->updateBattleButtonState();
}
void MainController::onPBMoveClicked() {
    auto fileName = mpPrivate->getOpenFileName();

    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        ui->lbl_move->setText(fileInfo.fileName());
        mpPrivate->mMoveFile = fileName.toStdString();
    }
    mpPrivate->updateBattleButtonState();
}
void MainController::onPBGameClicked() {
    auto fileName = mpPrivate->getOpenFileName();

    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        ui->lbl_game->setText(fileInfo.fileName());
        mpPrivate->mGameFile = fileName.toStdString();
    }
    mpPrivate->updateBattleButtonState();
}
void MainController::onPBBattleCaseClicked() {
    if (mpPrivate->mTestFile != "") {
        ui->stackedWidget->setCurrentWidget(ui->page_battle);
        mpPrivate->mBattleRefresh();
        ui->stackedWidget->setCurrentWidget(ui->page_battle);
        return;
    }
    bool loadDataResult = mpPrivate->mpPokemonService->loadData(mpPrivate->mMoveFile, mpPrivate->mPokemonFile, mpPrivate->mGameFile);
    mpPrivate->mBattleRefresh();

    ui->stackedWidget->setCurrentWidget(ui->page_battle);
    if (!loadDataResult) {
        QMessageBox::critical(0, "Load Data Error", "Failed to load data.");
        return;
    }
}


void MainController::setBattleRefreshCallback(const std::function<void()>& kpFunction) {
    mpPrivate->mBattleRefresh = kpFunction;
}

void MainController::myTest() {
    onPBBattleCaseClicked();
}

void MainController::setBattleSetTestCallback(const std::function<void()>& kpFunction) {
    mpPrivate->mSetTest = kpFunction;
}
