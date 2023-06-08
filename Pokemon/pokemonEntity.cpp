#include "pokemonEntity.h"

class PokemonEntityPrivate {
public:
    std::string mName;
    std::vector<TYPE> mTypeVec;
    PokemonStats mStats;
};

// Default constructor
PokemonEntity::PokemonEntity()
    : mpPrivate(std::make_unique<PokemonEntityPrivate>())
{
    // Initialize the name, stats, and type vector to default values
    mpPrivate->mName = "";
    mpPrivate->mStats.attack = 0;
    mpPrivate->mStats.defense = 0;
    mpPrivate->mStats.hp = 0;
    mpPrivate->mStats.specialAttack = 0;
    mpPrivate->mStats.specialDefence = 0;
    mpPrivate->mStats.speed = 0;
}

// Parameterized constructor
PokemonEntity::PokemonEntity(const std::string& kName, const std::vector<TYPE>& kTypeVec, const PokemonStats& kStats)
    : mpPrivate(std::make_unique<PokemonEntityPrivate>())
{
    // Set the name, type vector, and stats using the provided parameters
    setName(kName);
    mpPrivate->mTypeVec = kTypeVec;
    setStats(kStats);
}

// Copy constructor
PokemonEntity::PokemonEntity(const PokemonEntity& kPokemonEntity)
    : mpPrivate(std::make_unique<PokemonEntityPrivate>(*kPokemonEntity.mpPrivate))
{
    // Perform a deep copy of the private member using the unique pointer
}

// Destructor
PokemonEntity::~PokemonEntity() {
    // Destructor is automatically generated for the unique pointer
}

// Set the name of the Pokemon
void PokemonEntity::setName(const std::string& kName) {
    mpPrivate->mName = kName;
}

// Get the name of the Pokemon
std::string PokemonEntity::getName() const {
    return mpPrivate->mName;
}

// Add a type to the Pokemon's type vector
void PokemonEntity::addType(const TYPE& kType) {
    mpPrivate->mTypeVec.push_back(kType);
}

// Get the type vector of the Pokemon
std::vector<TYPE> PokemonEntity::getTypes() const {
    return mpPrivate->mTypeVec;
}

// Set the stats of the Pokemon
void PokemonEntity::setStats(const PokemonStats& kStats) {
    mpPrivate->mStats = kStats;
}

// Get the stats of the Pokemon
PokemonStats PokemonEntity::getStats() const {
    return mpPrivate->mStats;
}

// Assignment operator
PokemonEntity& PokemonEntity::operator=(const PokemonEntity& kPokemonEntity) {
    if (&kPokemonEntity == this)
        return *this;

    // Assuming that PokemonEntityPrivate has a copy constructor,
    // create a new instance of PokemonEntityPrivate based on 'kPokemonEntity'.
    mpPrivate = std::make_unique<PokemonEntityPrivate>(*kPokemonEntity.mpPrivate);

    return *this;
}
