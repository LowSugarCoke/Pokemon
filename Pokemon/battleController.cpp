#include "battleController.h"

#include <string>
#include <unordered_map>
#include <iostream>

#include <QMessageBox>

#include "pokemonService.h"

const static std::string PSN = "PSN";
const static std::string BRN = "BRN";
const static std::string PAR = "PAR";

std::unordered_map<std::string, std::string> pokemonPicMap{
    {"Venusaur",":/Pokemom/Resources/venusaur.png"},
    {"Charizard", ":/Pokemom/Resources/charizard.png"},
    {"Blastoise", ":/Pokemom/Resources/blastoise.png"}
};

static const std::string kPotion = "Potion";
static const std::string kSuperPotion = "Super Potion";
static const std::string kHyperPotion = "Hyper Potion";
static const std::string kMaxPotion = "Max Potion";

std::unordered_map<std::string, std::string> potionPicMap{
    {"Potion", ":/Pokemom/Resources/potion.png"},
    {"Super Potion", ":/Pokemom/Resources/super-potion.png"},
    {"Hyper Potion", ":/Pokemom/Resources/hyper-potion.png"},
    {"Max Potion", ":/Pokemom/Resources/max-potion.png"}
};

std::unordered_map<std::string, std::string> typePicMap{
    {"Fire", ":/Pokemom/Resources/type-fire.png"},
    {"Water", ":/Pokemom/Resources/type-water.png"},
    {"Grass", ":/Pokemom/Resources/type-grass.png"},
    {"Poison", ":/Pokemom/Resources/type-poison.png"},
    {"Flying", ":/Pokemom/Resources/type-flying.png"},
    {"Dragon", ":/Pokemom/Resources/type-dragon.png"},
    {"Steel", ":/Pokemom/Resources/type-steel.png"},
};

std::string pokemonBallLive = ":/Pokemom/Resources/ball.png";
std::string pokemonBallFaint = ":/Pokemom/Resources/ball-gray.png";


enum class GameState {
    Normal,
    Battle,
    Pokemon,
    Bag,
    Fainting
};

class BattleControllerPrivate :QObject {
public:
    BattleControllerPrivate(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService);
    void hideMoveBtn();
    void showMoveBtn();
    void hideSceneBtn();
    void showSceneBtn();
    void hideSelectPokemonBtn();
    void showSelectPokemonBtn();
    void hideSelectBagBtn();
    void showSelectBagBtn();
    void showType();
    void hideType();
    void showPP();
    void hidePP();
    void updateLog();
    void myPokemonFaint();
    void oppositingPokemonFaint();
    void winOrLose();
    void unablePP();

    Ui::PokemonClass* ui;
    std::shared_ptr<PokemonService> mpPokemonService;
    GameState mGameState;
    int mPotionSelectNum;
};

BattleControllerPrivate::BattleControllerPrivate(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService)
    :ui(ui)
    , mpPokemonService(pPokemonService)
{
    mPotionSelectNum = 0;
}

void BattleControllerPrivate::winOrLose() {
    auto nowStatus = mpPokemonService->isWinOrLose(); // 0 is not yet, 1 is win, 2 is lose
    if (nowStatus == 1) {
        QMessageBox::information(nullptr /*parent widget*/, "Battle Result", "Congratulations, you won the battle!");
        ui->stackedWidget->setCurrentWidget(ui->page_main);
    }
    else if (nowStatus == 2) {
        QMessageBox::information(nullptr /*parent widget*/, "Battle Result", "Unfortunately, you lost the battle. Better luck next time!");
        ui->stackedWidget->setCurrentWidget(ui->page_main);
    }
    else {
        // The battle is still ongoing. You can choose to do nothing here.
    }
}

void BattleControllerPrivate::unablePP() {
    auto currentPP = mpPokemonService->getCurrentPokemonPowerPoints();
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

    }
}

void BattleControllerPrivate::oppositingPokemonFaint() {
    if (mpPokemonService->getOppositingPokemonHp() == 0) {

        auto oppositingPokemonIndex = mpPokemonService->getCurrentOppositingPokemonIndex();

        QPixmap pixmap1(QString::fromStdString(pokemonBallFaint));
        pixmap1 = pixmap1.scaled(ui->lbl_battle_ball_opposite_1->size(), Qt::KeepAspectRatio);
        if (oppositingPokemonIndex == 0) {
            ui->lbl_battle_ball_opposite_1->setPixmap(pixmap1);
        }
        else if (oppositingPokemonIndex == 1) {
            ui->lbl_battle_ball_opposite_2->setPixmap(pixmap1);
        }
        else {
            ui->lbl_battle_ball_opposite_3->setPixmap(pixmap1);
        }

        mpPokemonService->swapOppositingPokemon();


    }
}

void BattleControllerPrivate::myPokemonFaint() {
    auto pokemonsFaintStatus = mpPokemonService->getPokemonsFaintStatus();
    auto myPokemonIndex = mpPokemonService->getCurrentPokemonIndex();

    if (pokemonsFaintStatus[0]) {
        ui->tb_battle_select_pokemon_1->setEnabled(false);
        if (myPokemonIndex == 0) {
            showSelectPokemonBtn();
            hideSceneBtn();
            mGameState = GameState::Fainting;

            QPixmap pixmap1(QString::fromStdString(pokemonBallFaint));
            pixmap1 = pixmap1.scaled(ui->lbl_battle_ball_pokemon_1->size(), Qt::KeepAspectRatio);
            ui->lbl_battle_ball_pokemon_1->setPixmap(pixmap1);
        }
    }
    if (pokemonsFaintStatus[1]) {
        ui->tb_battle_select_pokemon_2->setEnabled(false);
        if (myPokemonIndex == 1) {
            showSelectPokemonBtn();
            hideSceneBtn();
            mGameState = GameState::Fainting;

            QPixmap pixmap1(QString::fromStdString(pokemonBallFaint));
            pixmap1 = pixmap1.scaled(ui->lbl_battle_ball_pokemon_2->size(), Qt::KeepAspectRatio);
            ui->lbl_battle_ball_pokemon_2->setPixmap(pixmap1);
        }
    }
    if (pokemonsFaintStatus[2]) {
        ui->tb_battle_select_pokemon_3->setEnabled(false);
        if (myPokemonIndex == 2) {
            showSelectPokemonBtn();
            hideSceneBtn();
            mGameState = GameState::Fainting;

            QPixmap pixmap1(QString::fromStdString(pokemonBallFaint));
            pixmap1 = pixmap1.scaled(ui->lbl_battle_ball_pokemon_3->size(), Qt::KeepAspectRatio);
            ui->lbl_battle_ball_pokemon_3->setPixmap(pixmap1);
        }
    }
}

void BattleControllerPrivate::updateLog() {
    auto log = mpPokemonService->getBattleDailog();

    QTextCursor cursor = ui->text_edit_battle_content->textCursor();
    cursor.movePosition(QTextCursor::End);

    ui->text_edit_battle_content->setTextCursor(cursor);

    QFont font = ui->text_edit_battle_content->font();
    font.setPointSize(18);
    ui->text_edit_battle_content->setFont(font);

    ui->text_edit_battle_content->insertPlainText(QString::fromStdString(log));
    cursor.movePosition(QTextCursor::End);

    ui->text_edit_battle_content->setTextCursor(cursor);
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
    ui->tb_battle_select_bag_2->hide();
    ui->tb_battle_select_bag_3->hide();
    ui->tb_battle_select_bag_4->hide();
}

void BattleControllerPrivate::showSelectBagBtn() {
    ui->tb_battle_select_bag_1->show();
    ui->tb_battle_select_bag_2->show();
    ui->tb_battle_select_bag_3->show();
    ui->tb_battle_select_bag_4->show();
}

void BattleControllerPrivate::hideSelectPokemonBtn() {
    ui->tb_battle_select_pokemon_1->hide();
    ui->tb_battle_select_pokemon_2->hide();
    ui->tb_battle_select_pokemon_3->hide();

}

void BattleControllerPrivate::showSelectPokemonBtn() {
    ui->tb_battle_select_pokemon_1->show();
    ui->tb_battle_select_pokemon_2->show();
    ui->tb_battle_select_pokemon_3->show();
}

void BattleControllerPrivate::showType() {
    auto pokemonTypes = mpPokemonService->getCurrentPokemonMoveTypes();


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

    ui->lbl_battle_type_1->show();
    ui->lbl_battle_type_2->show();
    ui->lbl_battle_type_3->show();
    ui->lbl_battle_type_4->show();

}
void BattleControllerPrivate::hideType() {

    ui->lbl_battle_type_1->hide();
    ui->lbl_battle_type_2->hide();
    ui->lbl_battle_type_3->hide();
    ui->lbl_battle_type_4->hide();
}

void BattleControllerPrivate::showPP() {
    auto currentPP = mpPokemonService->getCurrentPokemonPowerPoints();
    auto maxPP = mpPokemonService->getCurrentPokemonMaxPowerPoints();

    ui->lbl_battle_pp_1->setText(QString::number(currentPP[0]) + "/" + QString::number(maxPP[0]));
    ui->lbl_battle_pp_2->setText(QString::number(currentPP[1]) + "/" + QString::number(maxPP[1]));
    ui->lbl_battle_pp_3->setText(QString::number(currentPP[2]) + "/" + QString::number(maxPP[2]));
    ui->lbl_battle_pp_4->setText(QString::number(currentPP[3]) + "/" + QString::number(maxPP[3]));

    ui->lbl_battle_pp_1->show();
    ui->lbl_battle_pp_2->show();
    ui->lbl_battle_pp_3->show();
    ui->lbl_battle_pp_4->show();
}
void BattleControllerPrivate::hidePP() {

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
    mpPrivate->mpPokemonService->battle(0);
    mpPrivate->updateLog();
    mpPrivate->mGameState = GameState::Normal;

    refresh();
    mpPrivate->winOrLose();
    mpPrivate->oppositingPokemonFaint();
    mpPrivate->myPokemonFaint();
    refresh();

}
void BattleController::onPBBattleMove2Clicked() {
    mpPrivate->hideMoveBtn();
    mpPrivate->hideType();
    mpPrivate->hidePP();
    ui->pb_battle_back->hide();
    mpPrivate->showSceneBtn();
    mpPrivate->mpPokemonService->battle(1);
    mpPrivate->updateLog();
    mpPrivate->mGameState = GameState::Normal;

    refresh();
    mpPrivate->winOrLose();
    mpPrivate->oppositingPokemonFaint();
    mpPrivate->myPokemonFaint();
    refresh();
}
void BattleController::onPBBattleMove3Clicked() {
    mpPrivate->hideMoveBtn();
    mpPrivate->hideType();
    mpPrivate->hidePP();
    ui->pb_battle_back->hide();
    mpPrivate->showSceneBtn();
    mpPrivate->mpPokemonService->battle(2);
    mpPrivate->updateLog();
    mpPrivate->mGameState = GameState::Normal;

    refresh();
    mpPrivate->winOrLose();
    mpPrivate->oppositingPokemonFaint();
    mpPrivate->myPokemonFaint();
    refresh();
}
void BattleController::onPBBattleMove4Clicked() {
    mpPrivate->hideMoveBtn();
    mpPrivate->hideType();
    mpPrivate->hidePP();
    ui->pb_battle_back->hide();
    mpPrivate->showSceneBtn();
    mpPrivate->mpPokemonService->battle(3);
    mpPrivate->updateLog();
    mpPrivate->mGameState = GameState::Normal;

    refresh();
    mpPrivate->winOrLose();
    mpPrivate->oppositingPokemonFaint();
    mpPrivate->myPokemonFaint();
    refresh();
}

void BattleController::onTBBattleSelectPokemon1Clicked() {

    ui->pb_battle_back->hide();
    mpPrivate->hideSelectPokemonBtn();
    mpPrivate->hideSelectBagBtn();
    mpPrivate->showSceneBtn();

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
    auto myPokemonName = mpPrivate->mpPokemonService->getPokemonsName();
    auto myPokemonIndex = mpPrivate->mpPokemonService->getCurrentPokemonIndex();
    ui->lbl_battle_player_pokemon->setText(QString::fromStdString(myPokemonName[myPokemonIndex]));

    auto oppositingPokemonName = mpPrivate->mpPokemonService->getOppositingPokemonsName();
    auto oppositingPokemonIndex = mpPrivate->mpPokemonService->getCurrentOppositingPokemonIndex();
    ui->lbl_battle_opposite_pokemon->setText(QString::fromStdString(oppositingPokemonName[oppositingPokemonIndex]));

    auto myHp = mpPrivate->mpPokemonService->getPokemonsHp();
    ui->lbl_battle_player_pokemon_blood->setText(QString::number(myHp[myPokemonIndex].first) + "/"
        + QString::number(myHp[myPokemonIndex].second));

    auto oppositingHp = mpPrivate->mpPokemonService->getOppositingPokemonsHp();
    ui->lbl_battle_opposite_pokemon_blood->setText(QString::number(oppositingHp[oppositingPokemonIndex].first) + "/"
        + QString::number(oppositingHp[oppositingPokemonIndex].second));

    ui->tb_battle_select_pokemon_1->setIcon(QIcon(QString::fromStdString(pokemonPicMap[myPokemonName[0]])));
    ui->tb_battle_select_pokemon_1->setText(QString::fromStdString(myPokemonName[0]) + QString::number(myHp[0].first) + "/" + QString::number(myHp[0].second));
    ui->tb_battle_select_pokemon_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    ui->tb_battle_select_pokemon_2->setIcon(QIcon(QString::fromStdString(pokemonPicMap[myPokemonName[1]])));
    ui->tb_battle_select_pokemon_2->setText(QString::fromStdString(myPokemonName[1]) + QString::number(myHp[1].first) + "/" + QString::number(myHp[1].second));
    ui->tb_battle_select_pokemon_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    ui->tb_battle_select_pokemon_3->setIcon(QIcon(QString::fromStdString(pokemonPicMap[myPokemonName[2]])));
    ui->tb_battle_select_pokemon_3->setText(QString::fromStdString(myPokemonName[2]) + QString::number(myHp[2].first) + "/" + QString::number(myHp[2].second));
    ui->tb_battle_select_pokemon_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    QPixmap pixmap1(QString::fromStdString(pokemonPicMap[myPokemonName[myPokemonIndex]]));
    pixmap1 = pixmap1.scaled(ui->lbl_battle_player_pokemon_name->size(), Qt::KeepAspectRatio);
    ui->lbl_battle_player_pokemon_name->setPixmap(pixmap1);


    QPixmap pixmap2(QString::fromStdString(pokemonPicMap[oppositingPokemonName[oppositingPokemonIndex]]));
    pixmap2 = pixmap2.scaled(ui->lbl_battle_player_pokemon_name->size(), Qt::KeepAspectRatio);
    ui->lbl_battle_opposite_pokemon_name->setPixmap(pixmap2);


    auto myPokemonMoves = mpPrivate->mpPokemonService->getCurrentPokemonMoves();
    ui->pb_battle_move_1->setText(QString::fromStdString(myPokemonMoves[0]));
    ui->pb_battle_move_2->setText(QString::fromStdString(myPokemonMoves[1]));
    ui->pb_battle_move_3->setText(QString::fromStdString(myPokemonMoves[2]));
    ui->pb_battle_move_4->setText(QString::fromStdString(myPokemonMoves[3]));

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




}

void BattleController::onTBBattleSelectBag1Clicked() {
    mpPrivate->showSelectPokemonBtn();
    mpPrivate->mPotionSelectNum = 0;
}
void BattleController::onTBBattleSelectBag2Clicked() {
    mpPrivate->showSelectPokemonBtn();
    mpPrivate->mPotionSelectNum = 1;
}
void BattleController::onTBBattleSelectBag3Clicked() {
    mpPrivate->showSelectPokemonBtn();
    mpPrivate->mPotionSelectNum = 2;

}
void BattleController::onTBBattleSelectBag4Clicked() {
    mpPrivate->showSelectPokemonBtn();
    mpPrivate->mPotionSelectNum = 3;
}
