/**************************************************************
 * File : mainController.h
 * Author: ´å¶Ç´¼ B11130034
 * Create Date: 2023-06-08
 * Editor : ´å¶Ç´¼ B11130034
 * Update Date: 2023-06-08
 * Description: This header file defines the MainController class which is responsible for handling main
 * user interactions in the Pokemon game. It interfaces with the game's UI and the PokemonService.
 * The class contains methods for setting up various callback functions for battle refresh,
 * test cases, music play etc. It also contains methods to handle button click events for test case,
 * Pokemon, move, game and battle case operations. The 'connection' method establishes connections
 * between UI signals and MainController slots.
 *************************************************************/

#pragma once

#include <memory>
#include <functional>

#include <QObject>
#include <QFileDialog>
#include <vector>

#include "ui_Pokemon.h"

class PokemonService;
class MainControllerPrivate;
class MainController : public QObject
{
    Q_OBJECT

public:

    /**
     * Intent : Construct a MainController object.
     * Pre: ui is the main UI for the application, pPokemonService provides services related to Pokemon operations.
     * Post: A MainController object is created.
     */
    MainController(Ui::PokemonClass* ui, std::shared_ptr<PokemonService> pPokemonService, QObject* parent = nullptr);

    /**
     * Intent : Set the callback function for refreshing the battle scene.
     * Pre: kpFunction is a valid callback function.
     * Post: The callback function for refreshing the battle scene is set.
     */
    void setBattleRefreshCallback(const std::function<void()>& kpFunction);

    /**
     * Intent : Perform a test.
     * Pre: The conditions for the test are met.
     * Post: The test is performed.
     */
    void myTest();

    /**
     * Intent : Set the callback function for a test in battle settings.
     * Pre: kpFunction is a valid callback function.
     * Post: The callback function for a test in battle settings is set.
     */
    void setBattleSetTestCallback(const std::function<void()>& kpFunction);

    /**
     * Intent : Set the callback function for playing music.
     * Pre: kpFunction is a valid callback function.
     * Post: The callback function for playing music is set.
     */
    void setMusicPlayCallback(const std::function<void()>& kpFunction);

private:
    Ui::PokemonClass* ui;
    std::unique_ptr<MainControllerPrivate> mpPrivate;

    /**
     * Intent : Establish the connections between UI signals and MainController slots.
     * Pre: A MainController object has been created.
     * Post: All necessary connections are made.
     */
    void connection();


private slots:

    /**
     * Intent : Handle the event when the test case button is clicked.
     * Pre: The test case button has been clicked.
     * Post: The test case is initiated.
     */
    void onPBTestCaseClicked();

    /**
     * Intent : Handle the event when the Pokemon button is clicked.
     * Pre: The Pokemon button has been clicked.
     * Post: The Pokemon selection screen is displayed.
     */
    void onPBPokemonClicked();

    /**
     * Intent : Handle the event when the move button is clicked.
     * Pre: The move button has been clicked.
     * Post: The move selection screen is displayed.
     */
    void onPBMoveClicked();

    /**
     * Intent : Handle the event when the game button is clicked.
     * Pre: The game button has been clicked.
     * Post: The game scene is displayed.
     */
    void onPBGameClicked();

    /**
     * Intent : Handle the event when the battle case button is clicked.
     * Pre: The battle case button has been clicked.
     * Post: The battle case is initiated or displayed.
     */
    void onPBBattleCaseClicked();
};
