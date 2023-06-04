#pragma once

#include <memory>

#include <QObject>
#include <QFileDialog>

#include "ui_Pokemon.h"

class PokemonControllerPrivate;
class PokemonController : public QObject
{
    Q_OBJECT

public: 
    PokemonController(Ui::PokemonClass* ui, QObject* parent = nullptr);

private:
    Ui::PokemonClass* ui;
    std::unique_ptr< PokemonControllerPrivate> mpPrivate;
    void connection();
    

private slots:
    void on_pb_test_case_clicked();
    void on_pb_pokemon_clicked();
    void on_pb_move_clicked();
    void on_pb_game_clicked();
    void on_pb_battle_case_clicked();

};
