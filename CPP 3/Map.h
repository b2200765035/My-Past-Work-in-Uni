#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <stack>
#include <queue>
#include <cmath>
#include "Isle.h"

struct MapNode
{
    Isle *isle;
    MapNode *left, *right;
    int height = 0;

    MapNode(Isle *isle) : isle(isle), left(nullptr), right(nullptr), height(1) {}
    ~MapNode() {
        // TODO: Free any dynamically allocated memory if necessary
        if (isle) {
            delete isle;
            isle = nullptr;
        }
    }
};

class Map
{
private:
    MapNode *root; // Root node of the tree
    int rebalanceCount = 0; 
    bool rebalanceOccurred = false;

    // Height of a node
    int height(MapNode *node);

    int balanceFactor(MapNode *node);

    MapNode *minValueNode(MapNode *node);

    // AVL Rotations
    MapNode *rotateRight(MapNode *current);
    MapNode *rotateLeft(MapNode *current);

    // Helper functions for recursive AVL insertion and deletion
    // USE THEM
    MapNode *insert(MapNode *node, Isle *isle);
    MapNode *remove(MapNode *node, Isle *isle);

    // Item drop helper functions
    void preOrderItemDrop(MapNode *current, int &count);
    void postOrderItemDrop(MapNode *current, int &count);

public:
    // Constructor declaration
    Map();
    // Destructor
    ~Map();

    void clearTree(MapNode *node);

    // Calculation of minumum depth a player can access at the map
    int calculateMinMapDepthAccess(int playerDepth, int totalShaperTreeHeight, int totalMapDepth);

    // Tree operations
    void insert(Isle *isle);
    void remove(Isle *isle);
    MapNode *remove(MapNode *node);
    /// Search
    Isle *findIsle(Isle isle);
    Isle *findIsle(std::string name);
    MapNode *findNode(Isle isle);
    MapNode *findNodeRecursive(MapNode *node, Isle isle);
    MapNode *findNode(std::string name);

    // Initilize tree from a vector
    void initializeMap(std::vector<Isle *> isles);

    MapNode *findFirstEmptyIsle(MapNode *node);
    

    int getDepth(MapNode *node); // Determines the depth of a node within the tree.
    int getIsleDepth(Isle *isle); // Determines the depth of a isle within the tree.
    int getDepth(); // Total level of the tree

    MapNode *findNodeRecursive(MapNode *node, std::string name);

    // Display tree in terminal
    void display(MapNode *current, int depth, int state);
    void displayMap();

    // Item drop api
    void populateWithItems();
    void dropItemBFS();


    // Write the AVL tree to a file with levels
    void writeToFile(const std::string &filename);
    // Write current Isles to file in alphabetical order
    void writeIslesToFile(const std::string &filename);
};

#endif