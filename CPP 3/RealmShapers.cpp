#include "RealmShapers.h"
#include <cmath>
#include <algorithm>

ShaperTree::ShaperTree()
{
}

ShaperTree::~ShaperTree()
{
    // TODO: Free any dynamically allocated memory if necessary
    for (RealmShaper* shaper : realmShapers) {
        delete shaper;
    }
    realmShapers.clear();
}

void ShaperTree::initializeTree(std::vector<RealmShaper *> shapers)
{
    // TODO: Insert innitial shapers to the tree
    for (RealmShaper *shaper: shapers) {
        insert(shaper);
    }
}

int ShaperTree::getSize()
{
    // TODO: Return number of shapers in the tree
    return realmShapers.size();
}

std::vector<RealmShaper *> ShaperTree::getTree()
{
    return realmShapers;
}

bool ShaperTree::isValidIndex(int index)
{
    bool isValid = false;

    // TODO: Check if the index is valid in the tree
    if (index >= 0 && index < realmShapers.size()) {
        isValid = true;
    }

    return isValid;
}

void ShaperTree::insert(RealmShaper *shaper)
{
    // TODO: Insert shaper to the tree
    realmShapers.push_back(shaper);
}

int ShaperTree::remove(RealmShaper *shaper)
{
    // TODO: Remove the player from tree if it exists
    int index = findIndex(shaper);
    if (index == -1) {
        // else
        return -1;
    }

    // Make sure tree protects its form (complate binary tree) after deletion of a node
    realmShapers.erase(realmShapers.begin() + index);

    // return index if found and removed
    return index;
}

int ShaperTree::findIndex(RealmShaper *shaper)
{
    // return index in the tree if found
    for (int i = 0; i < realmShapers.size(); ++i) {
        if (*realmShapers[i] == *shaper) {
            return i;
        }
    }

    // else
    return -1;
}

int ShaperTree::getDepth(RealmShaper *shaper)
{
    // return depth of the node in the tree if found
    int index = findIndex(shaper);
    if (index == -1) {
        // else
        return -1;
    }
    
    return static_cast<int>(std::floor(std::log2(index + 1)));
}

int ShaperTree::getDepth()
{
    // return total|max depth|height of the tree
    if (realmShapers.empty()) {
        return 0;
    }

    return static_cast<int>(std::floor(std::log2(realmShapers.size())));
}

RealmShaper ShaperTree::duel(RealmShaper *challenger, bool result)
{
    // TODO: Implement duel logic, return the victor
    RealmShaper *parent = getParent(challenger);

    if (result) {
        challenger->gainHonour();
        parent->loseHonour();
        std::cout << "[Duel] " << challenger->getName() << " won the duel" << std::endl;
    } else {
        parent->gainHonour();
        challenger->loseHonour();
        std::cout << "[Duel] " << challenger->getName() << " lost the duel" << std::endl;
    }

    std::cout << "[Honour] " << "New honour points: ";
    std::cout << challenger->getName() << "-" << challenger->getHonour() << " ";
    std::cout << parent->getName() << "-" << parent->getHonour() << std::endl;

    if (challenger->getHonour() < 0) {
        std::cout << "[Duel] " << challenger->getName() << " lost all honour, delete" << std::endl; 
        remove(challenger);
    }

    if (parent->getHonour() < 0) {
        std::cout << "[Duel] " << parent->getName() << " lost all honour, delete" << std::endl; 
        remove(parent);
    }

    if (result) {
        replace(challenger, parent);
        return *challenger;
    } else {
        return *parent;
    }
}

RealmShaper *ShaperTree::getParent(RealmShaper *shaper)
{
    RealmShaper *parent = nullptr;

    // TODO: return parent of the shaper
    int index = findIndex(shaper);
    if (index <= 0 || !isValidIndex(index)) {
        parent = nullptr;
    }
    
    int parentIndex = (index - 1) / 2;
    if (isValidIndex(parentIndex)) {
        parent = realmShapers[parentIndex];
    }

    return parent;
}

void ShaperTree::replace(RealmShaper *player_low, RealmShaper *player_high)
{
    // TODO: Change player_low and player_high's positions on the tree
    int lowIndex = findIndex(player_low);
    int highIndex = findIndex(player_high);

    if (lowIndex != -1 && highIndex != -1) {
        std::swap(realmShapers[lowIndex], realmShapers[highIndex]);
    }
}

RealmShaper *ShaperTree::findPlayer(RealmShaper shaper)
{
    RealmShaper *foundShaper = nullptr;

    // TODO: Search shaper by object
    for (RealmShaper *node : realmShapers) {
        if (*node == shaper) {
            // Return the shaper if found 
            foundShaper = node;
        }
    }

    // Return nullptr if shaper not found
    return foundShaper;
}

// Find shaper by name
RealmShaper *ShaperTree::findPlayer(std::string name)
{
    RealmShaper *foundShaper = nullptr;

    // TODO: Search shaper by name
    for (RealmShaper *shaper : realmShapers) {
        if (shaper->getName() == name) {
            // Return the shaper if found
            foundShaper = shaper;
        }
    }

    // Return nullptr if shaper not found
    return foundShaper;
}

std::vector<std::string> ShaperTree::inOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement inOrderTraversal in tree
    // Add all to a string vector
    // Return the vector

    // Define and implement as many helper functions as necessary for recursive implementation
    inOrderHelper(index, result);
    // Note: Since SheperTree is not an binary search tree,
    // in-order traversal will not give rankings in correct order
    // for correct order you need to implement level-order traversal
    // still you are to implement this function as well
    return result;
}

void ShaperTree::inOrderHelper(int index, std::vector<std::string> &result)
{
    if (!isValidIndex(index)) return;

    int left = 2 * index + 1;
    int right = 2 * index + 2;

    inOrderHelper(left, result);
    result.push_back(realmShapers[index]->getName());
    inOrderHelper(right, result);
}

std::vector<std::string> ShaperTree::preOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement preOrderTraversal in tree
    // Add all to a string vector
    // Return the vector
    preOrderHelper(index, result);
    // Define and implement as many helper functions as necessary for recursive implementation
    return result;
}

void ShaperTree::preOrderHelper(int index, std::vector<std::string> &result)
{
    if (!isValidIndex(index)) return;

    int left = 2 * index + 1;
    int right = 2 * index + 2;

    result.push_back(realmShapers[index]->getName());
    preOrderHelper(left, result);
    preOrderHelper(right, result);
}

std::vector<std::string> ShaperTree::postOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement postOrderTraversal in tree
    // Add all to a string vector
    // Return the vector
    postOrderHelper(index, result);
    // Define and implement as many helper functions as necessary for recursive implementation
    return result;
}

void ShaperTree::postOrderHelper(int index, std::vector<std::string> &result)
{
    if (!isValidIndex(index)) return;

    int left = 2 * index + 1;
    int right = 2 * index + 2;

    postOrderHelper(left, result);
    postOrderHelper(right, result);
    result.push_back(realmShapers[index]->getName());
}

void ShaperTree::preOrderTraversal(int index, std::ofstream &outFile)
{
    // TODO: Implement preOrderTraversal in tree
    // write nodes to output file

    // Define and implement as many helper functions as necessary for recursive implementation
    if (!outFile.is_open()) {
        std::cerr << "[Error] Unable to write to the provided output file." << std::endl;
        return;
    }
    std::vector<std::string> result = {};
    preOrderHelper(index, result);
    int a = 1;

    for(std::string line: result) {
        outFile << a << "\t" << line << "\n";
        index++;
    }
}

void ShaperTree::breadthFirstTraversal(std::ofstream &outFile)
{
    // TODO: Implement level-order traversal
    // write nodes to output file

    // Define and implement as many helper functions as necessary
    if (!outFile.is_open()) {
        std::cerr << "[Error] Unable to write to the provided output file." << std::endl;
        return;
    }

    int index = 1;
    for (RealmShaper *shaper : realmShapers) {
        if (shaper) {
            outFile << index << "\t" << shaper->getName() << "\n";
            index++;
        }
    }

}

void ShaperTree::displayTree()
{
    std::cout << "[Shaper Tree]" << std::endl;
    printTree(0, 0, "");
}

// Helper function to print tree with indentation
void ShaperTree::printTree(int index, int level, const std::string &prefix)
{
    if (!isValidIndex(index))
        return;

    std::cout << prefix << (level > 0 ? "   └---- " : "") << *realmShapers[index] << std::endl;
    int left = 2 * index + 1;  // TODO: Calculate left index
    int right = 2 * index + 2; // TODO: Calculate right index

    if (isValidIndex(left) || isValidIndex(right))
    {
        printTree(left, level + 1, prefix + (level > 0 ? "   │   " : "")); // ╎
        printTree(right, level + 1, prefix + (level > 0 ? "   │   " : ""));
    }
}

void ShaperTree::writeShapersToFile(const std::string &filename)
{
    // TODO: Write the shapers to filename output level by level
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "[Error] Unable to open file: " << filename << std::endl;
        return;
    }

    int index = 1;
    for (RealmShaper *shaper : realmShapers) {
        if (shaper) {
            outFile << index << "\t" << shaper->getName() << "\n";
            index++;
        }
    }

    outFile.close();
    std::cout << "[Output] " << "Shapers have been written to " << filename << " according to rankings." << std::endl;
}

void ShaperTree::writeToFile(const std::string &filename)
{
    // TODO: Write the tree to filename output pre-order
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "[Error] Unable to write to the provided output file." << std::endl;
        return;
    }

    std::vector<std::string> result = preOrderTraversal(0);
    int index = 1;

    for(std::string line: result) {
        outFile << index << "\t" << line << "\n";
        index++;
    }
    std::cout << "[Output] " << "Tree have been written to " << filename << " in pre-order." << std::endl;
}
