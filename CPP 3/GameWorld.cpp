#include "GameWorld.h"

GameWorld::GameWorld() : mapTree(), shaperTree() {}

void GameWorld::initializeGame(std::vector<Isle *> places, std::vector<RealmShaper *> players)
{
    shaperTree.initializeTree(players);
    mapTree.initializeMap(places);
}

Map& GameWorld::getMapTree()
{
    return mapTree;
}
ShaperTree& GameWorld::getShaperTree()
{
    return shaperTree;
}

bool GameWorld::hasAccess(RealmShaper *realmShaper, Isle *isle)
{
    bool hasAccess = false;

    // TODO: Check if the realmShaper has access to explore the isle
    // Get necessary depth values
    int playerDepth = shaperTree.getDepth(realmShaper);
    int totalShaperTreeHeight = shaperTree.getDepth();
    int totalMapDepth = mapTree.getDepth();

    if (playerDepth == -1) {
        std::cout << "[Access Control] " << "RealmShaper not found!" << std::endl;
        return false;
    }

    // Use mapTree.calculateMinMapDepthAccess
    int minAccessDepth = mapTree.calculateMinMapDepthAccess(playerDepth, totalShaperTreeHeight, totalMapDepth);
    int isleDepth = mapTree.getIsleDepth(isle);

    hasAccess = isleDepth <= minAccessDepth;
    return hasAccess;
}

void GameWorld::exploreArea(RealmShaper *realmShaper, Isle *isle)
{
    // TODO:
    // Check if realmShaper has access
    if (!hasAccess(realmShaper, isle)) {
        std::cout << "[Explore Area] " << realmShaper->getName() << " does not have access to explore area " << *isle << std::endl;
        return;
    }

    // If realmShaper has access
    // Visit isle, 
    // collect item,
    realmShaper->collectItem(isle->getItem());
    if(mapTree.findNode(realmShaper->getIsland())) {
        Isle *past = mapTree.findIsle(realmShaper->getIsland());
        past->decreaseShaperCount();
    }
    std::cout << "[Explore Area] " << realmShaper->getName() << " visited " << isle->getName() << std::endl;
    std::cout << "[Energy] " << realmShaper->getName() << "'s new energy level is " << realmShaper->getEnergyLevel() << std::endl;

    // check overcrowding for Isle, 
    if (!isle->increaseShaperCount()) {
        std::cout << "[Overcrowding] " << isle->getName() << " self-destructed, it will be removed from the map" << std::endl;
        // delete Isle if necessary
        mapTree.remove(isle); // Remove the isle from the map
    }

    // You will need to implement a mechanism to keep track of how many realm shapers are at an Isle at the same time
    // There are more than one ways to do this, so it has been left completely to you
    // Use shaperCount, but that alone will not be enough,
    // you will likely need to add attributes that are not currently defined
    // to RealmShaper or Isle or other classes depending on your implementation
}

void GameWorld::craft(RealmShaper *shaper, const std::string &isleName){
    // TODO: Check energy and craft new isle if possible
    if (!shaper->hasEnoughEnergy()) {
        std::cout << "[Energy] " << shaper->getName() << " does not have enough energy points: " << shaper->getEnergyLevel() << std::endl;
        return;
    }

    std::cout << "[Energy] " << shaper->getName() << " has enough energy points: " << shaper->getEnergyLevel() << std::endl;

    Isle *newIsle = new Isle(isleName);
    mapTree.insert(newIsle);
    shaper->loseEnergy();

    std::cout << "[Craft] " << shaper->getName() << " crafted new Isle " << isleName << std::endl;
}

void GameWorld::displayGameState()
{
    // mapTree.displayMap();
    // shaperTree.displayTree();
}

// TODO: Implement functions to read and parse Access and Duel logs

void GameWorld::processGameEvents(const std::string &accessLogs, const std::string &duelLogs)
{
    // TODO:
    // Read logs
    std::ifstream accessFile(accessLogs);
    std::ifstream duelFile(duelLogs);

    if (!accessFile.is_open() || !duelFile.is_open()) {
        std::cerr << "Error opening logs!" << std::endl;
        return;
    }

    
    std::string accessLine, duelLine;
    int accessCount = 0;

    while (std::getline(accessFile, accessLine)) {
        std::istringstream ss(accessLine);
        std::string shaperName, isleName;
        ss >> shaperName >> isleName;

        RealmShaper *shaper = shaperTree.findPlayer(shaperName);
        Isle *isle = mapTree.findIsle(isleName);

        // This function should call exploreArea and craft functions
        if (shaper && isle) {
            exploreArea(shaper, isle);
            accessCount++;
            // Use displayGameState();
            displayGameState();
        } else if (shaper && !isle) {
            craft(shaper, isleName);
            accessCount++;
            // Use displayGameState();
            displayGameState();
        }

        // For every 5 access, 1 duel happens
        if (accessCount % 5 == 0 && !duelFile.eof()) {
            std::getline(duelFile, duelLine);
            std::istringstream duelStream(duelLine);
            std::string challengerName;
            bool result;

            duelStream >> challengerName >> result;

            RealmShaper *challenger = shaperTree.findPlayer(challengerName);

            if (challenger) {
                shaperTree.duel(challenger, result);
                // Use displayGameState();
                displayGameState();
            }
        }
    }

    // If there are still duel logs left after every access happens duels happens one after other
    while (std::getline(duelFile, duelLine)) {
        std::istringstream duelStream(duelLine);
        std::string challengerName;
        bool result;

        duelStream >> challengerName >> result;

        RealmShaper *challenger = shaperTree.findPlayer(challengerName);

        if (challenger) {
            shaperTree.duel(challenger, result);
            // Use displayGameState();
            displayGameState();
        }
        
    }

    accessFile.close();
    duelFile.close();
    }   

void GameWorld::saveGameState(const std::string &currentIsles, const std::string &currentWorld, const std::string &currentShapers, const std::string &currentPlayerTree)
{
    mapTree.writeIslesToFile(currentIsles);
    mapTree.writeToFile(currentWorld);
    shaperTree.writeToFile(currentPlayerTree);
    shaperTree.writeShapersToFile(currentShapers);
}