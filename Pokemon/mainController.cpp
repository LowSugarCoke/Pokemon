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

    // Pointer to a PokemonService object
    std::shared_ptr<PokemonService> mpPokemonService;

    // Variables to store various file names
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
    connect(ui->pb_battle, &QPushButton::clicked, this, &MainController::onPBBattleCaseClicked);
    connect(ui->pb_quit, &QPushButton::clicked, this, &MainController::onPBQuitClicked);
}


/**
 * Slot for the "Battle" button click event.
 * Intent: Handle the click event of the "Battle" button.
 * Pre: The button should be clicked.
 * Post: The battle functionality is initiated and the UI is updated accordingly.
 */
void MainController::onPBBattleCaseClicked()
{
    bool loadDataResult = mpPrivate->mpPokemonService->loadData(mpPrivate->mMoveFile, mpPrivate->mPokemonFile, mpPrivate->mGameFile);
    if (!loadDataResult)
    {
        QMessageBox::critical(0, "Load Data Error", "Failed to load data.");
        return;
    }

    mpPrivate->mMusicPlay();
    ui->stackedWidget->setCurrentWidget(ui->page_battle);
    mpPrivate->mBattleRefresh();
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


void MainController::onPBQuitClicked() {
    QCoreApplication::quit();
}
