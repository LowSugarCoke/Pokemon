#include "Pokemon.h"

#include <iostream>

#include "moveEntity.h"
#include "gameEntity.h"
#include "pokemonEntity.h"
#include "moveDao.h"
#include "gameDao.h"
#include "pokemonDao.h"
#include "pokemonBo.h"
#include "playerMode.h"
#include "pokemonMode.h"
#include "fileReader.h"
#include "moveDataParser.h"
#include "gameDataParser.h"
#include "pokemonDataParser.h"
#include "pokemonService.h"
#include "damageMode.h"
#include "additionalEffectMode.h"
#include "pokemonLogger.h"

Pokemon::Pokemon(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    mpMainController = std::make_unique<MainController>(&ui, this);
    mpBattleController = std::make_unique<BattleController>(&ui, this);

    init();

    PokemonLogger& logger = PokemonLogger::getInstance();
    logger.debug("Hello world");

    std::string moveFilePath = "MoveLib.txt";
    std::string pokemonFilePath = "PokemonLib.txt";
    std::string gameFilePath = "GameData.txt";

    mpPokemonService->loadData(moveFilePath, pokemonFilePath, gameFilePath);

    //mpPokemonService->swapPokemon(1);

    mpPokemonService->battle(0);
    std::cout << mpPokemonService->getBattleDailog() << std::endl;
}


void Pokemon::init() {
    auto pFileReader = std::make_shared<FileReader>();
    auto pMoveDataParser = std::make_shared<MoveDataParser>();
    auto pMoveDao = std::make_shared<MoveDao>(pFileReader, pMoveDataParser);

    auto pGameDataParser = std::make_shared<GameDataParser>();
    auto pGameDao = std::make_shared<GameDao>(pFileReader, pGameDataParser);

    auto pPokemonDataParser = std::make_shared<PokemonDataParser>();
    auto pPokemonDao = std::make_shared <PokemonDao>(pFileReader, pPokemonDataParser);

    auto pDamageMode = std::make_shared<DamageMode>();
    auto pAdditionalEffectMode = std::make_shared<AdditionalEffectMode>();
    auto pPokemonMode = std::make_shared<PokemonMode>(pDamageMode, pAdditionalEffectMode);

    auto pPlayerMode = std::make_shared<PlayerMode>(pPokemonMode);

    mpPokemonService = std::make_unique<PokemonService>(pMoveDao, pGameDao, pPokemonDao, pPlayerMode);
}
