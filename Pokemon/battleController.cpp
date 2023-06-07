#include "battleController.h"

#include <string>
#include <unordered_map>

#include "pokemonService.h"

std::unordered_map<std::string, std::string> pokemonPicMap{
    {"Venusaur",":/Pokemom/Resources/venusaur.png"},
    {"Charizard", ":/Pokemom/Resources/charizard.png"},
    {"Blastoise", ":/Pokemom/Resources/blastoise.png"}
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
    void updateLog();
    Ui::PokemonClass* ui;
    std::shared_ptr<PokemonService> mpPokemonService;
};

BattleControllerPrivate::BattleControllerPrivate(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService)
    :ui(ui)
    , mpPokemonService(pPokemonService)
{

}

void BattleControllerPrivate::updateLog() {
    auto log = mpPokemonService->getBattleDailog();

    QTextCursor cursor = ui->text_edit_battle_content->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->text_edit_battle_content->setTextCursor(cursor);

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
}

void BattleControllerPrivate::showSelectBagBtn() {
    ui->tb_battle_select_bag_1->show();
    ui->tb_battle_select_bag_2->show();
    ui->tb_battle_select_bag_3->show();
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

    ui->tb_battle_select_bag_1->setIcon(QIcon(":/Pokemom/Resources/potion-red.png"));
    ui->tb_battle_select_bag_1->setText("HP plus");
    ui->tb_battle_select_bag_1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tb_battle_select_bag_1->hide();
    ui->tb_battle_select_bag_2->hide();
    ui->tb_battle_select_bag_3->hide();

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

}

void BattleController::onPBBattleBattleClicked() {

    mpPrivate->hideSceneBtn();

    mpPrivate->showMoveBtn();
    ui->pb_battle_back->show();
}

void BattleController::onPBBattleBackClicked() {
    mpPrivate->hideMoveBtn();
    mpPrivate->hideSelectPokemonBtn();
    mpPrivate->hideSelectBagBtn();
    ui->pb_battle_back->hide();

    mpPrivate->showSceneBtn();
}

void BattleController::onPBBattlePokemonClicked() {
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
    mpPrivate->hideSceneBtn();
    mpPrivate->hideMoveBtn();

    mpPrivate->showSelectBagBtn();
    ui->pb_battle_back->show();
}

void BattleController::onPBBattleMove1Clicked() {
    mpPrivate->mpPokemonService->battle(0);
    mpPrivate->updateLog();
    refresh();
}
void BattleController::onPBBattleMove2Clicked() {
    mpPrivate->mpPokemonService->battle(1);
    mpPrivate->updateLog();
    refresh();
}
void BattleController::onPBBattleMove3Clicked() {
    mpPrivate->mpPokemonService->battle(2);
    mpPrivate->updateLog();
    refresh();
}
void BattleController::onPBBattleMove4Clicked() {
    mpPrivate->mpPokemonService->battle(3);
    mpPrivate->updateLog();
    refresh();
}

void BattleController::onTBBattleSelectPokemon1Clicked() {
    ui->pb_battle_back->hide();
    mpPrivate->hideSelectPokemonBtn();
    mpPrivate->showSceneBtn();
    mpPrivate->mpPokemonService->swapPokemon(0);
    refresh();
}
void BattleController::onTBBattleSelectPokemon2Clicked() {
    ui->pb_battle_back->hide();
    mpPrivate->hideSelectPokemonBtn();
    mpPrivate->showSceneBtn();
    mpPrivate->mpPokemonService->swapPokemon(1);
    refresh();
}
void BattleController::onTBBattleSelectPokemon3Clicked() {
    ui->pb_battle_back->hide();
    mpPrivate->hideSelectPokemonBtn();
    mpPrivate->showSceneBtn();
    mpPrivate->mpPokemonService->swapPokemon(2);
    refresh();
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



}
