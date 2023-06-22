/**************************************************************
 * File : Pokemon.h
 * Author: Jack Lee
 * Create Date: 2023-06-08
 * Editor : Jack Lee
 * Update Date: 2023-06-08
 * Description: This file defines the Pokemon class, which serves as the main window of the application.
 *************************************************************/

#pragma once

#include <memory>
#include <QtWidgets/QMainWindow>
#include "ui_Pokemon.h"
#include "mainController.h"
#include "battleController.h"
#include "pokemonService.h"
#include "musicService.h"

class Pokemon : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructor for the Pokemon class.
     *
     * Intent: Create a new instance of the Pokemon class.
     * Pre: None.
     * Post: An instance of the Pokemon class is created.
     */
    Pokemon(QWidget* parent = Q_NULLPTR);

    /**
     * Initialization function for the Pokemon class.
     *
     * Intent: Perform initialization tasks for the Pokemon class.
     * Pre: None.
     * Post: The Pokemon class is initialized.
     */
    void init();

private:
    Ui::PokemonClass ui;  // UI for the Pokemon class
    std::unique_ptr<MainController> mpMainController;  // Main controller for the application
    std::unique_ptr<BattleController> mpBattleController;  // Battle controller for the application
    std::shared_ptr<PokemonService> mpPokemonService;  // Service for managing Pokemon-related operations
    std::shared_ptr<MusicService> mpMusicService;  // Service for playing music in the application
};
