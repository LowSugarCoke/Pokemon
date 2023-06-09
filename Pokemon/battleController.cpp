#include "battleController.h"

#include <string>
#include <unordered_map>
#include <iostream>

#include <QMessageBox>

#include "pokemonService.h"

// Constants representing status conditions
const static std::string PSN = "PSN";
const static std::string BRN = "BRN";
const static std::string PAR = "PAR";

// Map of Pokemon names to their corresponding picture paths
std::unordered_map<std::string, std::string> pokemonPicMap{
    {"Venusaur",":/Pokemom/Resources/venusaur.png"},
    {"Charizard", ":/Pokemom/Resources/charizard.png"},
    {"Blastoise", ":/Pokemom/Resources/blastoise.png"}
};

// Constants representing potion names
static const std::string kPotion = "Potion";
static const std::string kSuperPotion = "Super Potion";
static const std::string kHyperPotion = "Hyper Potion";
static const std::string kMaxPotion = "Max Potion";

// Map of potion names to their corresponding picture paths
std::unordered_map<std::string, std::string> potionPicMap{
    {"Potion", ":/Pokemom/Resources/potion.png"},
    {"Super Potion", ":/Pokemom/Resources/super-potion.png"},
    {"Hyper Potion", ":/Pokemom/Resources/hyper-potion.png"},
    {"Max Potion", ":/Pokemom/Resources/max-potion.png"}
};

// Map of Pokemon types to their corresponding picture paths
std::unordered_map<std::string, std::string> typePicMap{
    {"Fire", ":/Pokemom/Resources/type-fire.png"},
    {"Water", ":/Pokemom/Resources/type-water.png"},
    {"Grass", ":/Pokemom/Resources/type-grass.png"},
    {"Poison", ":/Pokemom/Resources/type-poison.png"},
    {"Flying", ":/Pokemom/Resources/type-flying.png"},
    {"Dragon", ":/Pokemom/Resources/type-dragon.png"},
    {"Steel", ":/Pokemom/Resources/type-steel.png"},
};

// Paths for Pokemon ball images
std::string pokemonBallLive = ":/Pokemom/Resources/ball.png";
std::string pokemonBallFaint = ":/Pokemom/Resources/ball-gray.png";

// Enumeration representing the game state
enum class GameState {
    Normal,
    Battle,
    Pokemon,
    Bag,
    Fainting
};

class BattleControllerPrivate :QObject {
public:
    /**
    * Constructor for the BattleControllerPrivate class.
    *
    * Intent: Initializes a BattleControllerPrivate object.
    * Pre: The ui pointer must point to a valid Ui::PokemonClass object. The pPokemonService pointer must point to a valid PokemonService object.
    * Post: A BattleControllerPrivate object is created.
    *
    * \param ui A pointer to the Ui::PokemonClass object.
    * \param pPokemonService A shared pointer to the PokemonService object.
    */
    BattleControllerPrivate(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService);

    /**
     * Hides the move button.
     *
     * Intent: Hides the move button in the user interface.
     * Pre: None.
     * Post: The move button is hidden.
     */
    void hideMoveBtn();

    /**
     * Shows the move button.
     *
     * Intent: Shows the move button in the user interface.
     * Pre: None.
     * Post: The move button is shown.
     */
    void showMoveBtn();

    /**
     * Hides the scene button.
     *
     * Intent: Hides the scene button in the user interface.
     * Pre: None.
     * Post: The scene button is hidden.
     */
    void hideSceneBtn();

    /**
     * Shows the scene button.
     *
     * Intent: Shows the scene button in the user interface.
     * Pre: None.
     * Post: The scene button is shown.
     */
    void showSceneBtn();

    /**
     * Hides the select Pokemon button.
     *
     * Intent: Hides the select Pokemon button in the user interface.
     * Pre: None.
     * Post: The select Pokemon button is hidden.
     */
    void hideSelectPokemonBtn();

    /**
     * Shows the select Pokemon button.
     *
     * Intent: Shows the select Pokemon button in the user interface.
     * Pre: None.
     * Post: The select Pokemon button is shown.
     */
    void showSelectPokemonBtn();

    /**
     * Hides the select bag button.
     *
     * Intent: Hides the select bag button in the user interface.
     * Pre: None.
     * Post: The select bag button is hidden.
     */
    void hideSelectBagBtn();

    /**
     * Shows the select bag button.
     *
     * Intent: Shows the select bag button in the user interface.
     * Pre: None.
     * Post: The select bag button is shown.
     */
    void showSelectBagBtn();

    /**
     * Shows the type.
     *
     * Intent: Shows the type image corresponding to the Pokemon's type in the user interface.
     * Pre: None.
     * Post: The type image is shown.
     */
    void showType();

    /**
     * Hides the type.
     *
     * Intent: Hides the type image in the user interface.
     * Pre: None.
     * Post: The type image is hidden.
     */
    void hideType();

    /**
     * Shows the PP (Power Points).
     *
     * Intent: Shows the current PP of the selected move in the user interface.
     * Pre: None.
     * Post: The PP is shown.
     */
    void showPP();

    /**
     * Hides the PP (Power Points).
     *
     * Intent: Hides the PP in the user interface.
     * Pre: None.
     * Post: The PP is hidden.
     */
    void hidePP();

    /**
     * Updates the log.
     *
     * Intent: Updates the battle log in the user interface with the latest information.
     * Pre: None.
     * Post: The battle log is updated.
     */
    void updateLog();

    /**
     * Handles the situation when the player's Pokemon faints.
     *
     * Intent: Performs the necessary actions when the player's Pokemon faints in battle.
     * Pre: None.
     * Post: The appropriate actions are taken.
     */
    void myPokemonFaint();

    /**
     * Handles the situation when the opposing Pokemon faints.
     *
     * Intent: Performs the necessary actions when the opposing Pokemon faints in battle.
     * Pre: None.
     * Post: The appropriate actions are taken.
     */
    void oppositingPokemonFaint();

    /**
     * Determines if the player has won or lost the battle.
     *
     * Intent: Checks the current status of the battle and displays the appropriate message if the player has won or lost.
     * Pre: None.
     * Post: The battle result is displayed.
     */
    void winOrLose();

    /**
     * Handles the situation when the selected move has insufficient PP.
     *
     * Intent: Performs the necessary actions when the selected move cannot be used due to insufficient PP.
     * Pre: None.
     * Post: The appropriate actions are taken.
     */
    void unablePP();

    Ui::PokemonClass* ui;
    std::shared_ptr<PokemonService> mpPokemonService;
    GameState mGameState;
    int mPotionSelectNum;
    bool mIsTest;
};

BattleControllerPrivate::BattleControllerPrivate(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService)
    :ui(ui)
    , mpPokemonService(pPokemonService)
{
    mPotionSelectNum = 0;
}

void BattleControllerPrivate::winOrLose() {
    // Check the current battle status: 0 means ongoing, 1 means win, 2 means lose
    auto nowStatus = mpPokemonService->isWinOrLose();

    if (nowStatus == 1) {
        // If the player has won the battle, show a congratulations message
        QMessageBox::information(nullptr /*parent widget*/, "Battle Result", "Congratulations, you won the battle!");
    }
    else if (nowStatus == 2) {
        // If the player has lost the battle, show a message
        QMessageBox::information(nullptr /*parent widget*/, "Battle Result", "Unfortunately, you lost the battle. Better luck next time!");
    }
    else {
        // The battle is still ongoing. You can choose to do nothing here.
    }
}

void BattleControllerPrivate::unablePP() {
    // Get the current power points (PP) of the player's Pokémon
    auto currentPP = mpPokemonService->getCurrentPokemonPowerPoints();

    // Disable the corresponding move buttons if the Pokémon has insufficient PP
    if (!currentPP[0]) {
        ui->pb_battle_move_1->setEnabled(false);
    }
    else if (!currentPP[1]) {
        ui->pb_battle_move_2->setEnabled(false);
    }
    else if (!currentPP[2]) {
        ui->pb_battle_move_3->setEnabled(false);
    }
    else if (!currentPP[3]) {
        ui->pb_battle_move_4->setEnabled(false);
    }
    else {
        // All moves have enough power points. You can choose to do nothing here.
    }
}

void BattleControllerPrivate::oppositingPokemonFaint() {
    // Get the current HP status of the opponent's Pokémon
    auto oppositePokemonHp = mpPokemonService->getOppositingPokemonsHp();

    // Load the faint Pokémon ball image
    QPixmap pixmap1(QString::fromStdString(pokemonBallFaint));
    pixmap1 = pixmap1.scaled(ui->lbl_battle_ball_opposite_1->size(), Qt::KeepAspectRatio);

    // Set the faint Pokémon ball image for each opponent's Pokémon if their HP is zero
    if (oppositePokemonHp[0].first == 0) {
        ui->lbl_battle_ball_opposite_1->setPixmap(pixmap1);
    }
    if (oppositePokemonHp[1].first == 0) {
        ui->lbl_battle_ball_opposite_2->setPixmap(pixmap1);
    }
    if (oppositePokemonHp[2].first == 0) {
        ui->lbl_battle_ball_opposite_3->setPixmap(pixmap1);
    }
}

void BattleControllerPrivate::myPokemonFaint() {
    // Get the faint status of the player's Pokémon
    auto pokemonsFaintStatus = mpPokemonService->getPokemonsFaintStatus();
    // Get the index of the current Pokémon in the player's team
    auto myPokemonIndex = mpPokemonService->getCurrentPokemonIndex();

    // Disable the corresponding select buttons if the Pokémon has fainted
    if (pokemonsFaintStatus[0]) {
        ui->tb_battle_select_pokemon_1->setEnabled(false);
        // If the current Pokémon has fainted, perform additional actions
        if (myPokemonIndex == 0) {
            showSelectPokemonBtn();
            hideSceneBtn();
            mGameState = GameState::Fainting;

            // Set the faint Pokémon ball image for the current Pokémon
            QPixmap pixmap1(QString::fromStdString(pokemonBallFaint));
            pixmap1 = pixmap1.scaled(ui->lbl_battle_ball_pokemon_1->size(), Qt::KeepAspectRatio);
            ui->lbl_battle_ball_pokemon_1->setPixmap(pixmap1);
        }
    }
    if (pokemonsFaintStatus[1]) {
        ui->tb_battle_select_pokemon_2->setEnabled(false);
        // If the current Pokémon has fainted, perform additional actions
        if (myPokemonIndex == 1) {
            showSelectPokemonBtn();
            hideSceneBtn();
            mGameState = GameState::Fainting;

            // Set the faint Pokémon ball image for the current Pokémon
            QPixmap pixmap1(QString::fromStdString(pokemonBallFaint));
            pixmap1 = pixmap1.scaled(ui->lbl_battle_ball_pokemon_2->size(), Qt::KeepAspectRatio);
            ui->lbl_battle_ball_pokemon_2->setPixmap(pixmap1);
        }
    }
    if (pokemonsFaintStatus[2]) {
        ui->tb_battle_select_pokemon_3->setEnabled(false);
        // If the current Pokémon has fainted, perform additional actions
        if (myPokemonIndex == 2) {
            showSelectPokemonBtn();
            hideSceneBtn();
            mGameState = GameState::Fainting;

            // Set the faint Pokémon ball image for the current Pokémon
            QPixmap pixmap1(QString::fromStdString(pokemonBallFaint));
            pixmap1 = pixmap1.scaled(ui->lbl_battle_ball_pokemon_3->size(), Qt::KeepAspectRatio);
            ui->lbl_battle_ball_pokemon_3->setPixmap(pixmap1);
        }
    }
}

void BattleControllerPrivate::updateLog() {
    // Get the battle dialogue log
    auto log = mpPokemonService->getBattleDailog();

    // Move the text cursor to the end of the text edit field
    QTextCursor cursor = ui->text_edit_battle_content->textCursor();
    cursor.movePosition(QTextCursor::End);

    // Set the font size for the text edit field
    QFont font = ui->text_edit_battle_content->font();
    font.setPointSize(18);
    ui->text_edit_battle_content->setFont(font);

    // Insert the battle dialogue log into the text edit field
    ui->text_edit_battle_content->insertPlainText(QString::fromStdString(log));
    cursor.movePosition(QTextCursor::End);

    // Move the text cursor to the end of the text edit field again
    ui->text_edit_battle_content->setTextCursor(cursor);
}


void BattleControllerPrivate::hideMoveBtn() {
    // Hide the move buttons
    ui->pb_battle_move_1->hide();
    ui->pb_battle_move_2->hide();
    ui->pb_battle_move_3->hide();
    ui->pb_battle_move_4->hide();
}

void BattleControllerPrivate::showMoveBtn() {
    // Show the move buttons
    ui->pb_battle_move_1->show();
    ui->pb_battle_move_2->show();
    ui->pb_battle_move_3->show();
    ui->pb_battle_move_4->show();
}

void BattleControllerPrivate::hideSceneBtn() {
    // Hide the scene buttons
    ui->pb_battle_battle->hide();
    ui->pb_battle_bag->hide();
    ui->pb_battle_pokemon->hide();
    ui->pb_battle_run->hide();
}

void BattleControllerPrivate::showSceneBtn() {
    // Show the scene buttons
    ui->pb_battle_battle->show();
    ui->pb_battle_bag->show();
    ui->pb_battle_pokemon->show();
    ui->pb_battle_run->show();
}

void BattleControllerPrivate::hideSelectBagBtn() {
    // Hide the select bag buttons
    ui->tb_battle_select_bag_1->hide();
    ui->tb_battle_select_bag_2->hide();
    ui->tb_battle_select_bag_3->hide();
    ui->tb_battle_select_bag_4->hide();
}

void BattleControllerPrivate::showSelectBagBtn() {
    // Show the select bag buttons
    ui->tb_battle_select_bag_1->show();
    ui->tb_battle_select_bag_2->show();
    ui->tb_battle_select_bag_3->show();
    ui->tb_battle_select_bag_4->show();
}

void BattleControllerPrivate::hideSelectPokemonBtn() {
    // Hide the select Pokemon buttons
    ui->tb_battle_select_pokemon_1->hide();
    ui->tb_battle_select_pokemon_2->hide();
    ui->tb_battle_select_pokemon_3->hide();
}

void BattleControllerPrivate::showSelectPokemonBtn() {
    // Show the select Pokemon buttons
    ui->tb_battle_select_pokemon_1->show();
    ui->tb_battle_select_pokemon_2->show();
    ui->tb_battle_select_pokemon_3->show();
}

void BattleControllerPrivate::showType() {
    // Get the types of the current Pokemon's moves
    auto pokemonTypes = mpPokemonService->getCurrentPokemonMoveTypes();

    // Set the corresponding type icons for each move
    QPixmap pixmapType1(QString::fromStdString(typePicMap[pokemonTypes[0]]));
    pixmapType1 = pixmapType1.scaled(ui->lbl_battle_type_1->size(), Qt::KeepAspectRatio);
    ui->lbl_battle_type_1->setPixmap(pixmapType1);

    QPixmap pixmapType2(QString::fromStdString(typePicMap[pokemonTypes[1]]));
    pixmapType2 = pixmapType2.scaled(ui->lbl_battle_type_2->size(), Qt::KeepAspectRatio);
    ui->lbl_battle_type_2->setPixmap(pixmapType2);

    QPixmap pixmapType3(QString::fromStdString(typePicMap[pokemonTypes[2]]));
    pixmapType3 = pixmapType3.scaled(ui->lbl_battle_type_3->size(), Qt::KeepAspectRatio);
    ui->lbl_battle_type_3->setPixmap(pixmapType3);

    QPixmap pixmapType4(QString::fromStdString(typePicMap[pokemonTypes[3]]));
    pixmapType4 = pixmapType4.scaled(ui->lbl_battle_type_4->size(), Qt::KeepAspectRatio);
    ui->lbl_battle_type_4->setPixmap(pixmapType4);

    // Show the type icons
    ui->lbl_battle_type_1->show();
    ui->lbl_battle_type_2->show();
    ui->lbl_battle_type_3->show();
    ui->lbl_battle_type_4->show();
}

void BattleControllerPrivate::hideType() {
    // Hide the type icons
    ui->lbl_battle_type_1->hide();
    ui->lbl_battle_type_2->hide();
    ui->lbl_battle_type_3->hide();
    ui->lbl_battle_type_4->hide();
}

void BattleControllerPrivate::showPP() {
    // Get the current power points (PP) and max power points of the current Pokemon's moves
    auto currentPP = mpPokemonService->getCurrentPokemonPowerPoints();
    auto maxPP = mpPokemonService->getCurrentPokemonMaxPowerPoints();

    // Update the PP labels with the current and max PP values
    ui->lbl_battle_pp_1->setText(QString::number(currentPP[0]) + "/" + QString::number(maxPP[0]));
    ui->lbl_battle_pp_2->setText(QString::number(currentPP[1]) + "/" + QString::number(maxPP[1]));
    ui->lbl_battle_pp_3->setText(QString::number(currentPP[2]) + "/" + QString::number(maxPP[2]));
    ui->lbl_battle_pp_4->setText(QString::number(currentPP[3]) + "/" + QString::number(maxPP[3]));

    // Show the PP labels
    ui->lbl_battle_pp_1->show();
    ui->lbl_battle_pp_2->show();
    ui->lbl_battle_pp_3->show();
    ui->lbl_battle_pp_4->show();
}

void BattleControllerPrivate::hidePP() {
    // Hide the PP labels
    ui->lbl_battle_pp_1->hide();
    ui->lbl_battle_pp_2->hide();
    ui->lbl_battle_pp_3->hide();
    ui->lbl_battle_pp_4->hide();
}

BattleController::BattleController(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService, QObject* parent)
    : QObject(parent)
    , ui(ui)
    , mpPrivate(std::make_unique<BattleControllerPrivate>(ui, pPokemonService))
{
    connection();

    ui->pb_battle_back->hide();
    ui->text_edit_battle_content->setFontPointSize(15);

    ui->tb_battle_select_pokemon_1->hide();
    ui->tb_battle_select_pokemon_2->hide();
    ui->tb_battle_select_pokemon_3->hide();

    ui->tb_battle_select_bag_1->hide();
    ui->tb_battle_select_bag_2->hide();
    ui->tb_battle_select_bag_3->hide();
    ui->tb_battle_select_bag_4->hide();

    ui->lbl_battle_opposite_PSN->hide();
    ui->lbl_battle_opposite_BRN->hide();
    ui->lbl_battle_opposite_PAR->hide();

    mpPrivate->hideType();
    mpPrivate->hidePP();
}

void BattleController::connection() {
    // Connect the button click signals to their respective slots
    connect(ui->pb_battle_battle, &QPushButton::clicked, this, &BattleController::onPBBattleBattleClicked);
    connect(ui->pb_battle_back, &QPushButton::clicked, this, &BattleController::onPBBattleBackClicked);
    connect(ui->pb_battle_pokemon, &QPushButton::clicked, this, &BattleController::onPBBattlePokemonClicked);
    connect(ui->pb_battle_bag, &QPushButton::clicked, this, &BattleController::onPBBattleBagClicked);
    connect(ui->pb_battle_move_1, &QPushButton::clicked, this, &BattleController::onPBBattleMove1Clicked);
    connect(ui->pb_battle_move_2, &QPushButton::clicked, this, &BattleController::onPBBattleMove2Clicked);
    connect(ui->pb_battle_move_3, &QPushButton::clicked, this, &BattleController::onPBBattleMove3Clicked);
    connect(ui->pb_battle_move_4, &QPushButton::clicked, this, &BattleController::onPBBattleMove4Clicked);

    connect(ui->tb_battle_select_pokemon_1, &QPushButton::clicked, this, &BattleController::onTBBattleSelectPokemon1Clicked);
    connect(ui->tb_battle_select_pokemon_2, &QPushButton::clicked, this, &BattleController::onTBBattleSelectPokemon2Clicked);
    connect(ui->tb_battle_select_pokemon_3, &QPushButton::clicked, this, &BattleController::onTBBattleSelectPokemon3Clicked);

    connect(ui->tb_battle_select_bag_1, &QPushButton::clicked, this, &BattleController::onTBBattleSelectBag1Clicked);
    connect(ui->tb_battle_select_bag_2, &QPushButton::clicked, this, &BattleController::onTBBattleSelectBag2Clicked);
    connect(ui->tb_battle_select_bag_3, &QPushButton::clicked, this, &BattleController::onTBBattleSelectBag3Clicked);
    connect(ui->tb_battle_select_bag_4, &QPushButton::clicked, this, &BattleController::onTBBattleSelectBag4Clicked);

    connect(ui->pb_battle_run, &QPushButton::clicked, this, &BattleController::onPBBattleRunClicked);
}

void BattleController::onPBBattleBattleClicked() {
    mpPrivate->mGameState = GameState::Battle;

    mpPrivate->hideSceneBtn();

    mpPrivate->showType();
    mpPrivate->unablePP();
    mpPrivate->showPP();
    mpPrivate->showMoveBtn();
    ui->pb_battle_back->show();
}

void BattleController::onPBBattleBackClicked() {
    mpPrivate->mGameState = GameState::Normal;

    mpPrivate->hideMoveBtn();
    mpPrivate->hideSelectPokemonBtn();
    mpPrivate->hideSelectBagBtn();
    ui->pb_battle_back->hide();

    mpPrivate->hideType();
    mpPrivate->hidePP();
    mpPrivate->showSceneBtn();
}

void BattleController::onPBBattlePokemonClicked() {
    mpPrivate->mGameState = GameState::Pokemon;

    mpPrivate->hideSceneBtn();
    mpPrivate->hideMoveBtn();

    auto myPokemonsName = mpPrivate->mpPokemonService->getPokemonsName();
    auto myHp = mpPrivate->mpPokemonService->getPokemonsHp();

    // Set the icons and text for the select Pokemon buttons based on the player's available Pokemon
    ui->tb_battle_select_pokemon_1->setIcon(QIcon(QString::fromStdString(pokemonPicMap[myPokemonsName[0]])));
    ui->tb_battle_select_pokemon_1->setText(QString::fromStdString(myPokemonsName[0]) + QString::number(myHp[0].first) + "/" + QString::number(myHp[0].second));
    ui->tb_battle_select_pokemon_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    ui->tb_battle_select_pokemon_2->setIcon(QIcon(QString::fromStdString(pokemonPicMap[myPokemonsName[1]])));
    ui->tb_battle_select_pokemon_2->setText(QString::fromStdString(myPokemonsName[1]) + QString::number(myHp[1].first) + "/" + QString::number(myHp[1].second));
    ui->tb_battle_select_pokemon_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    ui->tb_battle_select_pokemon_3->setIcon(QIcon(QString::fromStdString(pokemonPicMap[myPokemonsName[2]])));
    ui->tb_battle_select_pokemon_3->setText(QString::fromStdString(myPokemonsName[2]) + QString::number(myHp[2].first) + "/" + QString::number(myHp[2].second));
    ui->tb_battle_select_pokemon_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    mpPrivate->showSelectPokemonBtn();
    ui->pb_battle_back->show();
}

void BattleController::onPBBattleBagClicked() {
    mpPrivate->mGameState = GameState::Bag;

    mpPrivate->hideSceneBtn();
    mpPrivate->hideMoveBtn();

    auto potionsName = mpPrivate->mpPokemonService->getPotionsName();

    // Set the icons and text for the select bag buttons based on the available potions
    ui->tb_battle_select_bag_1->setIcon(QIcon(QString::fromStdString(potionPicMap[potionsName[0]])));
    ui->tb_battle_select_bag_1->setText(QString::fromStdString(potionsName[0]));
    ui->tb_battle_select_bag_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    ui->tb_battle_select_bag_2->setIcon(QIcon(QString::fromStdString(potionPicMap[potionsName[1]])));
    ui->tb_battle_select_bag_2->setText(QString::fromStdString(potionsName[1]));
    ui->tb_battle_select_bag_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    ui->tb_battle_select_bag_3->setIcon(QIcon(QString::fromStdString(potionPicMap[potionsName[2]])));
    ui->tb_battle_select_bag_3->setText(QString::fromStdString(potionsName[2]));
    ui->tb_battle_select_bag_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    ui->tb_battle_select_bag_4->setIcon(QIcon(QString::fromStdString(potionPicMap[potionsName[3]])));
    ui->tb_battle_select_bag_4->setText(QString::fromStdString(potionsName[3]));
    ui->tb_battle_select_bag_4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    mpPrivate->showSelectBagBtn();
    ui->pb_battle_back->show();
}

void BattleController::onPBBattleMove1Clicked() {
    mpPrivate->hideMoveBtn();
    mpPrivate->hideType();
    mpPrivate->hidePP();
    ui->pb_battle_back->hide();
    mpPrivate->showSceneBtn();

    // Perform the battle action associated with move 1
    if (mpPrivate->mIsTest) {
        mpPrivate->mpPokemonService->battle(0);
    }
    else {
        mpPrivate->mpPokemonService->battle(0);
    }

    mpPrivate->updateLog();
    mpPrivate->mGameState = GameState::Normal;

    refresh();
}

void BattleController::onPBBattleMove2Clicked() {
    mpPrivate->hideMoveBtn();
    mpPrivate->hideType();
    mpPrivate->hidePP();
    ui->pb_battle_back->hide();
    mpPrivate->showSceneBtn();

    // Perform the battle action associated with move 2
    mpPrivate->mpPokemonService->battle(1);
    mpPrivate->updateLog();
    mpPrivate->mGameState = GameState::Normal;

    refresh();
}

void BattleController::onPBBattleMove3Clicked() {
    mpPrivate->hideMoveBtn();
    mpPrivate->hideType();
    mpPrivate->hidePP();
    ui->pb_battle_back->hide();
    mpPrivate->showSceneBtn();

    // Perform the battle action associated with move 3
    mpPrivate->mpPokemonService->battle(2);
    mpPrivate->updateLog();
    mpPrivate->mGameState = GameState::Normal;

    refresh();
}

void BattleController::onPBBattleMove4Clicked() {
    mpPrivate->hideMoveBtn();
    mpPrivate->hideType();
    mpPrivate->hidePP();
    ui->pb_battle_back->hide();
    mpPrivate->showSceneBtn();

    // Perform the battle action associated with move 4
    mpPrivate->mpPokemonService->battle(3);
    mpPrivate->updateLog();
    mpPrivate->mGameState = GameState::Normal;

    refresh();
}

void BattleController::onTBBattleSelectPokemon1Clicked() {
    ui->pb_battle_back->hide();
    mpPrivate->hideSelectPokemonBtn();
    mpPrivate->hideSelectBagBtn();
    mpPrivate->showSceneBtn();

    // Perform the corresponding action based on the current game state and selected Pokemon
    if (mpPrivate->mGameState == GameState::Pokemon) {
        mpPrivate->mpPokemonService->swapPokemon(0);
    }
    else if (mpPrivate->mGameState == GameState::Bag) {
        mpPrivate->mpPokemonService->usePotion(0, mpPrivate->mPotionSelectNum);
    }
    else if (mpPrivate->mGameState == GameState::Fainting) {
        mpPrivate->mpPokemonService->faintingSwapPokemon(0);
    }
    mpPrivate->mGameState = GameState::Normal;

    refresh();
    mpPrivate->winOrLose();
    mpPrivate->oppositingPokemonFaint();
    mpPrivate->myPokemonFaint();
    refresh();

    mpPrivate->updateLog();
}

void BattleController::onTBBattleSelectPokemon2Clicked() {
    ui->pb_battle_back->hide();
    mpPrivate->hideSelectPokemonBtn();
    mpPrivate->hideSelectBagBtn();
    mpPrivate->showSceneBtn();

    // Perform the corresponding action based on the current game state and selected Pokemon
    if (mpPrivate->mGameState == GameState::Pokemon) {
        mpPrivate->mpPokemonService->swapPokemon(1);
    }
    else if (mpPrivate->mGameState == GameState::Bag) {
        mpPrivate->mpPokemonService->usePotion(1, mpPrivate->mPotionSelectNum);
    }
    else if (mpPrivate->mGameState == GameState::Fainting) {
        mpPrivate->mpPokemonService->faintingSwapPokemon(1);
    }
    mpPrivate->mGameState = GameState::Normal;

    refresh();
    mpPrivate->winOrLose();
    mpPrivate->oppositingPokemonFaint();
    mpPrivate->myPokemonFaint();
    refresh();

    mpPrivate->updateLog();
}

void BattleController::onTBBattleSelectPokemon3Clicked() {
    ui->pb_battle_back->hide();
    mpPrivate->hideSelectPokemonBtn();
    mpPrivate->hideSelectBagBtn();
    mpPrivate->showSceneBtn();

    // Perform the corresponding action based on the current game state and selected Pokemon
    if (mpPrivate->mGameState == GameState::Pokemon) {
        mpPrivate->mpPokemonService->swapPokemon(2);
    }
    else if (mpPrivate->mGameState == GameState::Bag) {
        mpPrivate->mpPokemonService->usePotion(2, mpPrivate->mPotionSelectNum);
    }
    else if (mpPrivate->mGameState == GameState::Fainting) {
        mpPrivate->mpPokemonService->faintingSwapPokemon(2);
    }
    mpPrivate->mGameState = GameState::Normal;

    refresh();
    mpPrivate->winOrLose();
    mpPrivate->oppositingPokemonFaint();
    mpPrivate->myPokemonFaint();
    refresh();

    mpPrivate->updateLog();
}

void BattleController::refresh() {
    // Update the UI elements with the latest battle information

    // Update player's Pokemon information
    auto myPokemonName = mpPrivate->mpPokemonService->getPokemonsName();
    auto myPokemonIndex = mpPrivate->mpPokemonService->getCurrentPokemonIndex();
    ui->lbl_battle_player_pokemon->setText(QString::fromStdString(myPokemonName[myPokemonIndex]));

    auto myHp = mpPrivate->mpPokemonService->getPokemonsHp();
    ui->lbl_battle_player_pokemon_blood->setText(QString::number(myHp[myPokemonIndex].first) + "/" + QString::number(myHp[myPokemonIndex].second));

    QPixmap pixmap1(QString::fromStdString(pokemonPicMap[myPokemonName[myPokemonIndex]]));
    pixmap1 = pixmap1.scaled(ui->lbl_battle_player_pokemon_name->size(), Qt::KeepAspectRatio);
    ui->lbl_battle_player_pokemon_name->setPixmap(pixmap1);

    // Update opponent's Pokemon information
    auto oppositingPokemonName = mpPrivate->mpPokemonService->getOppositingPokemonsName();
    auto oppositingPokemonIndex = mpPrivate->mpPokemonService->getCurrentOppositingPokemonIndex();
    ui->lbl_battle_opposite_pokemon->setText(QString::fromStdString(oppositingPokemonName[oppositingPokemonIndex]));

    auto oppositingHp = mpPrivate->mpPokemonService->getOppositingPokemonsHp();
    ui->lbl_battle_opposite_pokemon_blood->setText(QString::number(oppositingHp[oppositingPokemonIndex].first) + "/" + QString::number(oppositingHp[oppositingPokemonIndex].second));

    QPixmap pixmap2(QString::fromStdString(pokemonPicMap[oppositingPokemonName[oppositingPokemonIndex]]));
    pixmap2 = pixmap2.scaled(ui->lbl_battle_player_pokemon_name->size(), Qt::KeepAspectRatio);
    ui->lbl_battle_opposite_pokemon_name->setPixmap(pixmap2);

    // Update move buttons
    auto myPokemonMoves = mpPrivate->mpPokemonService->getCurrentPokemonMoves();
    ui->pb_battle_move_1->setText(QString::fromStdString(myPokemonMoves[0]));
    ui->pb_battle_move_2->setText(QString::fromStdString(myPokemonMoves[1]));
    ui->pb_battle_move_3->setText(QString::fromStdString(myPokemonMoves[2]));
    ui->pb_battle_move_4->setText(QString::fromStdString(myPokemonMoves[3]));

    // Update additional effect labels
    ui->lbl_battle_pokemon_PSN->hide();
    ui->lbl_battle_pokemon_BRN->hide();
    ui->lbl_battle_pokemon_PAR->hide();
    auto additionalEffect = mpPrivate->mpPokemonService->getCurrentPokemonAdditionalEffect();
    for (auto& effect : additionalEffect) {
        if (effect == PSN) {
            ui->lbl_battle_pokemon_PSN->show();
        }
        else if (effect == BRN) {
            ui->lbl_battle_pokemon_BRN->show();
        }
        else if (effect == PAR) {
            ui->lbl_battle_pokemon_PAR->show();
        }
    }

    ui->lbl_battle_opposite_PSN->hide();
    ui->lbl_battle_opposite_BRN->hide();
    ui->lbl_battle_opposite_PAR->hide();
    auto oppositingAdditionalEffect = mpPrivate->mpPokemonService->getOppositingPokemonAdditionalEffect();
    for (auto& effect : oppositingAdditionalEffect) {
        if (effect == PSN) {
            ui->lbl_battle_opposite_PSN->show();
        }
        else if (effect == BRN) {
            ui->lbl_battle_opposite_BRN->show();
        }
        else if (effect == PAR) {
            ui->lbl_battle_opposite_PAR->show();
        }
    }

    // Check battle status
    mpPrivate->winOrLose();
    mpPrivate->oppositingPokemonFaint();
    mpPrivate->myPokemonFaint();

    // Update battle log
    mpPrivate->updateLog();
}

void BattleController::onTBBattleSelectBag1Clicked() {
    // Select the first bag item and show the select Pokemon buttons
    mpPrivate->showSelectPokemonBtn();
    mpPrivate->mPotionSelectNum = 0;
}

void BattleController::onTBBattleSelectBag2Clicked() {
    // Select the second bag item and show the select Pokemon buttons
    mpPrivate->showSelectPokemonBtn();
    mpPrivate->mPotionSelectNum = 1;
}

void BattleController::onTBBattleSelectBag3Clicked() {
    // Select the third bag item and show the select Pokemon buttons
    mpPrivate->showSelectPokemonBtn();
    mpPrivate->mPotionSelectNum = 2;
}

void BattleController::onTBBattleSelectBag4Clicked() {
    // Select the fourth bag item and show the select Pokemon buttons
    mpPrivate->showSelectPokemonBtn();
    mpPrivate->mPotionSelectNum = 3;
}

void BattleController::onPBBattleRunClicked() {
    ui->stackedWidget->setCurrentWidget(ui->page_main);
}
