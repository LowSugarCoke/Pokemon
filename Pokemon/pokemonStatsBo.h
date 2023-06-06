#pragma once

#include <memory>

class MoveEntity;
class PokemonEntity;
class PokemonStatsBoPrivate;
class PokemonStatsBo {
public:
    PokemonStatsBo();
    PokemonStatsBo(const PokemonStatsBo& kPokemonStatsBo);

    ~PokemonStatsBo();

    void setPokemonEntity(const PokemonEntity& kPokemonEntity);
    void addMoveEntity(const MoveEntity& kMoveEntity);


private:
    std::unique_ptr<PokemonStatsBoPrivate> mpPrivate;
};
