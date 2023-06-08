/**************************************************************
 * File : battleController.h
 * Author: ´å¶Ç´¼ B11130034
 * Create Date: 2023-06-08
 * Editor : ´å¶Ç´¼ B11130034
 * Update Date: 2023-06-08
 * Description: This file contains the declaration of the BattleController class, which is responsible for
 * controlling the battle logic and user interface interactions in a Pokemon game.
 *************************************************************/

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
    /**
    * Intent: Constructs a BattleController object.
    * Pre: The ui pointer must point to a valid Ui::PokemonClass object. The pPokemonService pointer must point to a valid PokemonService object.
    * Post: A BattleController object is created.
    */
    BattleController(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService, QObject* parent = nullptr);

    /**
    * Intent: Refreshes the battle interface.
    * Pre: None.
    * Post: The battle interface is updated.
    */
    void refresh();

private:
    Ui::PokemonClass* ui;
    std::unique_ptr<BattleControllerPrivate> mpPrivate;

    /**
    * Intent: Establishes the necessary signal-slot connections.
    * Pre: None.
    * Post: The signal-slot connections are established.
    */
    void connection();

private slots:

    /**
     * Intent: Handles the event when the "Battle" button is clicked.
     * Pre: None.
     * Post: The battle sequence is initiated.
     */
    void onPBBattleBattleClicked();

    /**
     * Intent: Handles the event when the "Back" button is clicked.
     * Pre: None.
     * Post: The player is taken back to the previous screen.
     */
    void onPBBattleBackClicked();

    /**
     * Intent: Handles the event when the "Pokemon" button is clicked.
     * Pre: None.
     * Post: The player's Pokemon are displayed.
     */
    void onPBBattlePokemonClicked();

    /**
     * Intent: Handles the event when the "Bag" button is clicked.
     * Pre: None.
     * Post: The player's bag is displayed.
     */
    void onPBBattleBagClicked();

    /**
     * Intent: Handles the event when the first move button is clicked.
     * Pre: None.
     * Post: The move is executed.
     */
    void onPBBattleMove1Clicked();

    /**
     * Intent: Handles the event when the second move button is clicked.
     * Pre: None.
     * Post: The move is executed.
     */
    void onPBBattleMove2Clicked();
    /**
     * Intent: Handles the event when the third move button is clicked.
     * Pre: None.
     * Post: The move is executed.
     */
    void onPBBattleMove3Clicked();
    /**
     * Intent: Handles the event when the fourth move button is clicked.
     * Pre: None.
     * Post: The move is executed.
     */
    void onPBBattleMove4Clicked();

    /**
     * Intent: Handles the event when the first Pokemon in the team is selected.
     * Pre: None.
     * Post: The Pokemon is selected for battle.
     */
    void onTBBattleSelectPokemon1Clicked();
    /**
     * Intent: Handles the event when the second Pokemon in the team is selected.
     * Pre: None.
     * Post: The Pokemon is selected for battle.
     */
    void onTBBattleSelectPokemon2Clicked();

    /**
     * Intent: Handles the event when the third Pokemon in the team is selected.
     * Pre: None.
     * Post: The Pokemon is selected for battle.
     */
    void onTBBattleSelectPokemon3Clicked();

    /**
     * Intent: Handles the event when the first item in the bag is selected.
     * Pre: None.
     * Post: The item is selected for use.
     */
    void onTBBattleSelectBag1Clicked();

    /**
     * Intent: Handles the event when the second item in the bag is selected.
     * Pre: None.
     * Post: The item is selected for use.
     */
    void onTBBattleSelectBag2Clicked();
    /**
     * Intent: Handles the event when the third item in the bag is selected.
     * Pre: None.
     * Post: The item is selected for use.
     */
    void onTBBattleSelectBag3Clicked();
    /**
     * Intent: Handles the event when the fourth item in the bag is selected.
     * Pre: None.
     * Post: The item is selected for use.
     */
    void onTBBattleSelectBag4Clicked();


};
