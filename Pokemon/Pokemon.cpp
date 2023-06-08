#include "Pokemon.h"

#include <iostream>

#include "moveEntity.h"
#include "gameEntity.h"
#include "pokemonEntity.h"
#include "moveDao.h"
#include "gameDao.h"
#include "pokemonDao.h"
#include "testDataDao.h"
#include "pokemonBo.h"
#include "playerMode.h"
#include "pokemonMode.h"
#include "potionMode.h"
#include "fileReader.h"
#include "moveDataParser.h"
#include "gameDataParser.h"
#include "pokemonDataParser.h"
#include "testDataParser.h"
#include "pokemonService.h"
#include "damageMode.h"
#include "additionalEffectMode.h"
#include "pokemonLogger.h"
#include "musicMode.h"

Pokemon::Pokemon(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    init();


    mpMainController = std::make_unique<MainController>(&ui, mpPokemonService, this);
    mpMainController->setBattleRefreshCallback([&]() {mpBattleController->refresh(); });
    mpMainController->setMusicPlayCallback([&]() {    mpMusicService->playMusic("./Resources/battle.mp3"); });
    mpBattleController = std::make_unique<BattleController>(&ui, mpPokemonService, this);



    PokemonLogger& logger = PokemonLogger::getInstance();


}


void Pokemon::init() {
    auto pFileReader = std::make_shared<FileReader>();
    auto pMoveDataParser = std::make_shared<MoveDataParser>();
    auto pMoveDao = std::make_shared<MoveDao>(pFileReader, pMoveDataParser);

    auto pGameDataParser = std::make_shared<GameDataParser>();
    auto pGameDao = std::make_shared<GameDao>(pFileReader, pGameDataParser);

    auto pPokemonDataParser = std::make_shared<PokemonDataParser>();
    auto pPokemonDao = std::make_shared <PokemonDao>(pFileReader, pPokemonDataParser);

    auto pTestDataParser = std::make_shared<TestDataParser>();
    auto pTestDataDao = std::make_shared<TestDataDao>(pFileReader, pTestDataParser);

    auto pDamageMode = std::make_shared<DamageMode>();
    auto pAdditionalEffectMode = std::make_shared<AdditionalEffectMode>();
    auto pPotionMode = std::make_shared<PotionMode>();
    auto pPokemonMode = std::make_shared<PokemonMode>(pDamageMode, pAdditionalEffectMode, pPotionMode);

    auto pPlayerMode = std::make_shared<PlayerMode>(pPokemonMode);

    mpPokemonService = std::make_shared<PokemonService>(pMoveDao, pGameDao, pPokemonDao, pTestDataDao, pPlayerMode);

    auto pMusicMode = std::make_shared<MusicMode>();
    mpMusicService = std::make_shared<MusicService>(pMusicMode);
}
