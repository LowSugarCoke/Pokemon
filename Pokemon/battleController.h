#pragma once

#include <memory>

#include <QObject>

#include "ui_Pokemon.h"

class PokemonService;
class BattleControllerPrivate;
class BattleController : public QObject
{
    Q_OBJECT

public:
    BattleController(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService, QObject* parent = nullptr);
    void refresh();


private:
    Ui::PokemonClass* ui;
    std::unique_ptr< BattleControllerPrivate> mpPrivate;
    void connection();

private slots:
    void onPBBattleBattleClicked();
    void onPBBattleBackClicked();
    void onPBBattlePokemonClicked();
    void onPBBattleBagClicked();

    void onPBBattleMove1Clicked();
    void onPBBattleMove2Clicked();
    void onPBBattleMove3Clicked();
    void onPBBattleMove4Clicked();

    void onTBBattleSelectPokemon1Clicked();
    void onTBBattleSelectPokemon2Clicked();
    void onTBBattleSelectPokemon3Clicked();

    void onTBBattleSelectBag1Clicked();
    void onTBBattleSelectBag2Clicked();
    void onTBBattleSelectBag3Clicked();
    void onTBBattleSelectBag4Clicked();



};
