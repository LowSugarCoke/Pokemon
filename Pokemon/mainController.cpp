#include "mainController.h"
#include "pokemonService.h"
#include <map>
#include <QMessageBox>

// Class definition for MainControllerPrivate
class MainControllerPrivate : QObject
{
public:

    /**
     * Constructor for MainControllerPrivate class.
     * \param ui Pointer to the UI instance of the PokemonClass.
     * \param pPokemonService Pointer to the PokemonService instance.
     * Intent: Initialize a MainControllerPrivate object.
     * Pre: The `ui` and `pPokemonService` parameters must be valid pointers.
     * Post: A MainControllerPrivate object is created.
     */
    MainControllerPrivate(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService);

    /**
     * Get the selected file name from the file dialog.
     * \return The selected file name as a QString.
     * Intent: Retrieve the selected file name from the file dialog.
     * Pre: The file dialog should be opened and a file should be selected.
     * Post: The selected file name is returned as a QString.
     */
    QString getOpenFileName();

    /**
     * Update the state of the battle button based on the current game state.
     * Intent: Update the state of the battle button in the UI based on the current game state.
     * Pre: The UI elements related to the battle button should be initialized.
     * Post: The state of the battle button is updated in the UI.
     */
    void updateBattleButtonState();

    // Pointer to a PokemonService object
    std::shared_ptr<PokemonService> mpPokemonService;

    // Variables to store various file names
    std::string mTestFile;
    std::string mGameFile;
    std::string mPokemonFile;
    std::string mMoveFile;

    // Callback functions for refreshing the battle and playing music
    std::function < void() > mBattleRefresh;
    std::function < void() > mMusicPlay;

    // Pointer to the UI
    Ui::PokemonClass* ui;
};
MainControllerPrivate::MainControllerPrivate(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService) : ui(ui), mpPokemonService(pPokemonService) {}

/**
 * Get the selected file name from the file dialog.
 * \return The selected file name as a QString.
 * Intent: Prompt the user to select a file and return the selected file name.
 * Pre: None.
 * Post: The selected file name is returned as a QString.
 */
QString MainControllerPrivate::getOpenFileName()
{
    return QFileDialog::getOpenFileName(nullptr,
        tr("Open File"), "",
        tr("All Files (*)"));
}

/**
 * Update the state of the battle button based on the current game state.
 * Intent: Update the state of the battle button in the UI based on the availability of required labels.
 * Pre: The UI elements related to the battle button should be initialized.
 * Post: The state of the battle button is updated in the UI.
 */
void MainControllerPrivate::updateBattleButtonState()
{
    bool allLabelsHaveContent = !(ui->lbl_pokemon->text().isEmpty() ||
        ui->lbl_move->text().isEmpty() ||
        ui->lbl_game->text().isEmpty());

    ui->pb_battle->setEnabled(allLabelsHaveContent);
}

/**
 * Constructor for MainController class.
 * \param ui Pointer to the UI instance of the PokemonClass.
 * \param pPokemonService Pointer to the PokemonService instance.
 * \param parent Pointer to the parent QObject.
 * Intent: Initialize a MainController object.
 * Pre: The `ui` and `pPokemonService` parameters must be valid pointers.
 * Post: A MainController object is created.
 */
MainController::MainController(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService, QObject* parent) : QObject(parent), ui(ui), mpPrivate(std::make_unique<MainControllerPrivate>(ui, pPokemonService))
{
    connection();

    // For test
    mpPrivate->mGameFile = "GameData.txt";
    mpPrivate->mPokemonFile = "PokemonLib.txt";
    mpPrivate->mMoveFile = "MoveLib.txt";
}

/**
 * Connect the UI button signals to their respective slots.
 * Intent: Connect the signals of UI buttons to their corresponding slots.
 * Pre: The UI buttons and their corresponding slots must be defined.
 * Post: The signals and slots are connected.
 */
void MainController::connection()
{
    connect(ui->pb_test_case, &QPushButton::clicked, this, &MainController::onPBTestCaseClicked);
    connect(ui->pb_pokemon, &QPushButton::clicked, this, &MainController::onPBPokemonClicked);
    connect(ui->pb_move, &QPushButton::clicked, this, &MainController::onPBMoveClicked);
    connect(ui->pb_game, &QPushButton::clicked, this, &MainController::onPBGameClicked);
    connect(ui->pb_battle, &QPushButton::clicked, this, &MainController::onPBBattleCaseClicked);
}

/**
 * Slot for the "Test Case" button click event.
 * Intent: Handle the click event of the "Test Case" button.
 * Pre: The button should be clicked.
 * Post: The test case file is loaded and the UI is updated accordingly.
 */
void MainController::onPBTestCaseClicked()
{
    auto fileName = mpPrivate->getOpenFileName();

    if (!fileName.isEmpty())
    {
        QFileInfo fileInfo(fileName);
        ui->lbl_test_case->setText(fileInfo.fileName());
        mpPrivate->mTestFile = fileName.toStdString();
    }

    mpPrivate->mpPokemonService->loadTestData(mpPrivate->mTestFile);
}

/**
 * Slot for the "Pokemon" button click event.
 * Intent: Handle the click event of the "Pokemon" button.
 * Pre: The button should be clicked.
 * Post: The Pokemon file is loaded and the UI is updated accordingly.
 */
void MainController::onPBPokemonClicked()
{
    auto fileName = mpPrivate->getOpenFileName();

    if (!fileName.isEmpty())
    {
        QFileInfo fileInfo(fileName);
        ui->lbl_pokemon->setText(fileInfo.fileName());
        mpPrivate->mPokemonFile = fileName.toStdString();
    }

    mpPrivate->updateBattleButtonState();
}

/**
 * Slot for the "Move" button click event.
 * Intent: Handle the click event of the "Move" button.
 * Pre: The button should be clicked.
 * Post: The Move file is loaded and the UI is updated accordingly.
 */
void MainController::onPBMoveClicked()
{
    auto fileName = mpPrivate->getOpenFileName();

    if (!fileName.isEmpty())
    {
        QFileInfo fileInfo(fileName);
        ui->lbl_move->setText(fileInfo.fileName());
        mpPrivate->mMoveFile = fileName.toStdString();
    }

    mpPrivate->updateBattleButtonState();
}

/**
 * Slot for the "Game" button click event.
 * Intent: Handle the click event of the "Game" button.
 * Pre: The button should be clicked.
 * Post: The Game file is loaded and the UI is updated accordingly.
 */
void MainController::onPBGameClicked()
{
    auto fileName = mpPrivate->getOpenFileName();

    if (!fileName.isEmpty())
    {
        QFileInfo fileInfo(fileName);
        ui->lbl_game->setText(fileInfo.fileName());
        mpPrivate->mGameFile = fileName.toStdString();
    }

    mpPrivate->updateBattleButtonState();
}

/**
 * Slot for the "Battle" button click event.
 * Intent: Handle the click event of the "Battle" button.
 * Pre: The button should be clicked.
 * Post: The battle functionality is initiated and the UI is updated accordingly.
 */
void MainController::onPBBattleCaseClicked()
{
    mpPrivate->mMusicPlay();

    if (mpPrivate->mTestFile != "")
    {
        ui->stackedWidget->setCurrentWidget(ui->page_battle);
        mpPrivate->mBattleRefresh();
        return;
    }

    bool loadDataResult = mpPrivate->mpPokemonService->loadData(mpPrivate->mMoveFile, mpPrivate->mPokemonFile, mpPrivate->mGameFile);
    mpPrivate->mBattleRefresh();

    ui->stackedWidget->setCurrentWidget(ui->page_battle);
    if (!loadDataResult)
    {
        QMessageBox::critical(0, "Load Data Error", "Failed to load data.");
        return;
    }
}

/**
 * Set the callback function for refreshing the battle UI.
 * \param kpFunction The callback function for refreshing the battle UI.
 * Intent: Set the callback function for refreshing the battle UI.
 * Pre: The callback function must be a valid function pointer.
 * Post: The callback function is set.
 */
void MainController::setBattleRefreshCallback(const std::function < void() >& kpFunction)
{
    mpPrivate->mBattleRefresh = kpFunction;
}

/**
 * Invoke the battle functionality.
 * Intent: Invoke the battle functionality.
 * Pre: None.
 * Post: The battle functionality is invoked.
 */
void MainController::myTest()
{
    onPBBattleCaseClicked();
}

/**
 * Set the callback function for playing music.
 * \param kpFunction The callback function for playing music.
 * Intent: Set the callback function for playing music.
 * Pre: The callback function must be a valid function pointer.
 * Post: The callback function is set.
 */
void MainController::setMusicPlayCallback(const std::function < void() >& kpFunction)
{
    mpPrivate->mMusicPlay = kpFunction;
}
