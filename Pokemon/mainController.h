#pragma once

#include <memory>
#include <functional>

#include <QObject>
#include <QFileDialog>

#include "ui_Pokemon.h"

class PokemonService;
class MainControllerPrivate;
class MainController : public QObject
{
    Q_OBJECT

public:
    MainController(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService, QObject* parent = nullptr);
    void setBattleRefreshCallback(const std::function<void()>& kpFunction);
    void test();

private:
    Ui::PokemonClass* ui;
    std::unique_ptr< MainControllerPrivate> mpPrivate;
    void connection();


private slots:
    void onPBTestCaseClicked();
    void onPBPokemonClicked();
    void onPBMoveClicked();
    void onPBGameClicked();
    void onPBBattleCaseClicked();

};
