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

    // Create main controller and connect callbacks
    mpMainController = std::make_unique<MainController>(&ui, mpPokemonService, this);
    mpMainController->setBattleRefreshCallback([&]() { mpBattleController->refresh(); });
    mpMainController->setMusicPlayCallback([&]() { mpMusicService->playMusic("./Resources/battle.mp3"); });

    // Create battle controller
    mpBattleController = std::make_unique<BattleController>(&ui, mpPokemonService, this);

    PokemonLogger& logger = PokemonLogger::getInstance();
}

void Pokemon::init() {
    // Create file reader
    auto pFileReader = std::make_shared<FileReader>();

    // Create move data parser and move DAO
    auto pMoveDataParser = std::make_shared<MoveDataParser>();
    auto pMoveDao = std::make_shared<MoveDao>(pFileReader, pMoveDataParser);

    // Create game data parser and game DAO
    auto pGameDataParser = std::make_shared<GameDataParser>();
    auto pGameDao = std::make_shared<GameDao>(pFileReader, pGameDataParser);

    // Create Pokemon data parser and Pokemon DAO
    auto pPokemonDataParser = std::make_shared<PokemonDataParser>();
    auto pPokemonDao = std::make_shared<PokemonDao>(pFileReader, pPokemonDataParser);

    // Create test data parser and test data DAO
    auto pTestDataParser = std::make_shared<TestDataParser>();
    auto pTestDataDao = std::make_shared<TestDataDao>(pFileReader, pTestDataParser);

    // Create damage mode, additional effect mode, and potion mode
    auto pDamageMode = std::make_shared<DamageMode>();
    auto pAdditionalEffectMode = std::make_shared<AdditionalEffectMode>();
    auto pPotionMode = std::make_shared<PotionMode>();

    // Create Pokemon mode with dependencies
    auto pPokemonMode = std::make_shared<PokemonMode>(pDamageMode, pAdditionalEffectMode, pPotionMode);

    // Create player mode with Pokemon mode
    auto pPlayerMode = std::make_shared<PlayerMode>(pPokemonMode);

    // Create Pokemon service with DAOs and player mode
    mpPokemonService = std::make_shared<PokemonService>(pMoveDao, pGameDao, pPokemonDao, pTestDataDao, pPlayerMode);

    // Create music mode and music service
    auto pMusicMode = std::make_shared<MusicMode>();
    mpMusicService = std::make_shared<MusicService>(pMusicMode);
}
