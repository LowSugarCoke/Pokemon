#pragma once

#include <memory>

#include <QObject>
#include <QFileDialog>

#include "ui_Pokemon.h"

class MainControllerPrivate;
class MainController : public QObject
{
    Q_OBJECT

public: 
    MainController(Ui::PokemonClass* ui, QObject* parent = nullptr);

private:
    Ui::PokemonClass* ui;
    std::unique_ptr< MainControllerPrivate> mpPrivate;
    void connection();
    

private slots:
    void on_pb_test_case_clicked();
    void on_pb_pokemon_clicked();
    void on_pb_move_clicked();
    void on_pb_game_clicked();
    void on_pb_battle_case_clicked();

};
