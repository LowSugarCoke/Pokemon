#pragma once

#include <memory>

#include <QObject>

#include "ui_Pokemon.h"

class BattleControllerPrivate;
class BattleController : public QObject
{
    Q_OBJECT

public:
    BattleController(Ui::PokemonClass* ui, QObject* parent = nullptr);

private:
    Ui::PokemonClass* ui;
    std::unique_ptr< BattleControllerPrivate> mpPrivate;
    void connection();


private slots:

};
