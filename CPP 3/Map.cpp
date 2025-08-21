#include "Map.h"

Map::Map()
{
    this->root = nullptr;
}
Map::~Map()
{
    // TODO: Free any dynamically allocated memory if necessary
    clearTree(root); // Recursively delete all nodes
    root = nullptr;  // Set root to nullptr for safety
}

void Map::clearTree(MapNode *node)
{
    if (!node)
        return;

    // Recursively delete left and right subtrees
    clearTree(node->left);
    clearTree(node->right);

    // Delete the current node
    delete node;
}

int Map::calculateMinMapDepthAccess(int playerDepth, int totalShaperTreeHeight, int totalMapDepth)
{
    return (int)totalMapDepth * ((double)playerDepth / totalShaperTreeHeight);
}

void Map::initializeMap(std::vector<Isle *> isles)
{
    // TODO: Insert innitial isles to the tree
    for (Isle *isle : isles) {
        insert(isle);
    }

    // Then populate with Goldium and Einstainium items
    populateWithItems();
}

MapNode *Map::rotateRight(MapNode *current)
{
    // TODO: Perform right rotation according to AVL

    MapNode *newRoot = current->left;
    current->left = newRoot->right;
    newRoot->right = current;

    current->height = 1 + std::max(height(current->left), height(current->right));
    newRoot->height = 1 + std::max(height(newRoot->left), height(newRoot->right));

    // return necessary new root
    return newRoot;
}

MapNode *Map::rotateLeft(MapNode *current)
{
    // TODO: Perform left rotation according to AVL

    MapNode *newRoot = current->right;
    current->right = newRoot->left;
    newRoot->left = current;

    current->height = 1 + std::max(height(current->left), height(current->right));
    newRoot->height = 1 + std::max(height(newRoot->left), height(newRoot->right));

    // return necessary new root
    return newRoot;
    
}

int calculateMinMapDepthAccess(int playerDepth, int totalShaperTreeHeight, int totalMapDepth)
{
    return (int)totalMapDepth * ((double)playerDepth / totalShaperTreeHeight);
}

int Map::height(MapNode *node)
{
    // TODO: Return height of the node
    if (node == nullptr)
            return -1;
    return node->height;
}
int Map::balanceFactor(MapNode* node)
{
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
}

MapNode* Map::minValueNode(MapNode* node)
{
    MapNode* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

MapNode *Map::insert(MapNode *node, Isle *isle)
{
    if (!node) {
        return new MapNode(isle);
    }

    // TODO: Recursively insert isle to the tree
    if (height(node->left) <= height(node->right)) {
        node->left = insert(node->left, isle);
    } else {
        node->right = insert(node->right, isle);
    }

    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = balanceFactor(node);

    if (balance > 1) {
        if (!rebalanceOccurred) {
            rebalanceCount++;
            if (rebalanceCount == 3) {
                dropItemBFS();
                rebalanceCount = 0;
            }
            rebalanceOccurred = true;
        }
        if (height(node->left->left) >= height(node->left->right)) {
            return rotateRight(node);
        }
        else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    if (balance < -1) {
        if (!rebalanceOccurred) {
            rebalanceCount++;
            if (rebalanceCount == 3) {
                dropItemBFS();
                rebalanceCount = 0;
            }
            rebalanceOccurred = true;
        }
        if (height(node->right->right) >= height(node->right->left)) {
            return rotateLeft(node);
        }
        else {
            node->right = rotateRight(node->right);
            return rotateLeft(node); // Right-Left case
        }
    }

    // returns inserted node
    return node;
}

void Map::insert(Isle *isle)
{
    rebalanceOccurred = false;
    root = insert((root), isle);
    

    // you might need to insert some checks / functions here depending on your implementation
}

MapNode *Map::remove(MapNode *node, Isle *isle)
{
    // TODO: Recursively delete isle from the tree
    // Will be called if there is overcrowding

    if (!node) {
        return nullptr;
    }

    if (*isle < *(node->isle))
    {
        node->left = remove(node->left, isle);
    }
    else if (*isle > *(node->isle))
    {
        node->right = remove(node->right, isle);
    }
    else
    {
        // Node to delete found
        if (!node->left || !node->right)
        {
            // Node with one or no children
            MapNode *temp = node->left ? node->left : node->right;
            delete node;
            return temp; // Return the non-null child or nullptr
        }
        else
        {
            // Node with two children: Replace with the rightmost node of the left subtree
            MapNode *temp = node->left;
            while (temp->right)
            {
                temp = temp->right;
            }

            // Replace node's data with the rightmost child's data
            node->isle = temp->isle;

            // Remove the duplicate node from the left subtree
            node->left = remove(node->left, temp->isle);
        }
    }

    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = balanceFactor(node);

    if (balance > 1) {
        if (!rebalanceOccurred) {
            rebalanceCount++;
            if (rebalanceCount == 3) {
                dropItemBFS();
                rebalanceCount = 0;
            }
            rebalanceOccurred = true;
        }
        if (height(node->left->left) >= height(node->left->right)) {
            return rotateRight(node);
        }
        else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    if (balance < -1) {
        if (!rebalanceOccurred) {
            rebalanceCount++;
            if (rebalanceCount == 3) {
                dropItemBFS();
                rebalanceCount = 0;
            }
            rebalanceOccurred = true;
        }
        return rotateLeft(node);
        if (height(node->right->right) >= height(node->right->left)) {
            return rotateLeft(node);
        }
        else {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    // returns node
    return node;
}

void Map::remove(Isle *isle)
{
    rebalanceOccurred = false;
    root = remove((root), isle);
    // you might need to insert some checks / functions here depending on your implementation
}

MapNode *Map::remove(MapNode *node)
{
    rebalanceOccurred = false;
    root = remove((root), node->isle);
    return root;
}

void Map::preOrderItemDrop(MapNode *current, int &count)
{
    // TODO: Drop EINSTEINIUM according to rules
    if (current == nullptr) {
        return;
    }


    // Process current node
    count++;
    if (count % 5 == 0)
    {
        current->isle->setItem(EINSTEINIUM);
        std::cout << "[Item Drop] " << "EINSTEINIUM dropped on Isle: " << current->isle->getName() << std::endl;
    }

    preOrderItemDrop(current->left, count);
    preOrderItemDrop(current->right, count);
}

// to Display the values by Post Order Method .. left - right - node
void Map::postOrderItemDrop(MapNode *current, int &count)
{
    // TODO: Drop GOLDIUM according to rules
    if (current == nullptr) {
        return;
    }

    postOrderItemDrop(current->left, count);
    postOrderItemDrop(current->right, count);

    // Process current node
    count++;
    if (count % 3 == 0) {
        current->isle->setItem(GOLDIUM);
        std::cout << "[Item Drop] " << "GOLDIUM dropped on Isle: " << current->isle->getName() << std::endl;
    }
}

MapNode *Map::findFirstEmptyIsle(MapNode *node)
{
    // TODO: Find first Isle with no item
    if (node == nullptr) {
        return nullptr;
    }

    std::queue<MapNode *> queue;
    queue.push(node);

    while (!queue.empty()) {
        MapNode *current = queue.front();
        queue.pop();

        // Check if the Isle has no items
        if (current->isle->getItem() == EMPTY) {
            return current;
        }

        // Enqueue left and right children
        if (current->left)
            queue.push(current->left);
        if (current->right)
            queue.push(current->right);
    }

    return nullptr;
}

void Map::dropItemBFS()
{
    // TODO: Drop AMAZONITE according to rules
    MapNode *targetNode = findFirstEmptyIsle(root);

    if (targetNode) {
        targetNode->isle->setItem(AMAZONITE);
        std::cout << "[BFS Drop] " << "AMAZONITE dropped on Isle: " << targetNode->isle->getName() << std::endl;
    }
    else {
        std::cout << "[BFS Drop] " << "No eligible Isle found for AMAZONITE drop." << std::endl;
    }
}

void Map::displayMap()
{
    std::cout << "[World Map]" << std::endl;
    display(root, 0, 0);
}

int Map::getDepth(MapNode *node)
{
    // TODO: Return node depth if found, else
    if (!root || !node) {
        return -1;
    }

    int depth = 0;
    MapNode *current = root;

    while (current) {
        if (current == node) {
            return depth;
        }

        if (*node->isle < *current->isle) {
            current = current->left;
        } else {
            current = current->right;
        }

        depth++;
    }

    return -1;
}

// Function to calculate the depth of a specific node in the AVL tree
int Map::getIsleDepth(Isle *isle)
{
    // TODO: Return node depth by isle if found, else
    if (!root || !isle) {
        return -1;
    }

    int depth = 0;
    MapNode *current = root;

    while (current) {
        if (*current->isle == *isle) {
            return depth;
        }

        if (*isle < *current->isle) {
            current = current->left;
        } else {
            current = current->right;
        }

        depth++;
    }
    return -1;
}

int Map::getDepth()
{
    // TODO: Return max|total depth of tree
    std::queue<MapNode *> queue;
    queue.push(root);
    int height = 0;

    while (!queue.empty()) {
        int size = queue.size();

        for (int i = 0; i < size; i++) {
            MapNode* curr = queue.front();
            queue.pop();
            if (curr->left) queue.push(curr->left);
            if (curr->right) queue.push(curr->right);
        }

        height++;
    }
    return -1;
}

void Map::populateWithItems()
{
    // TODO: Distribute first GOLDIUM than EINSTEINIUM
    int count = 0;
    postOrderItemDrop(root, count);

    count = 0;
    preOrderItemDrop(root, count);
}

Isle *Map::findIsle(Isle isle)
{
    // TODO: Find isle by value
    MapNode *node = findNode(isle);
    if (node) {
        return node->isle;
    }
    return nullptr;
}

Isle *Map::findIsle(std::string name)
{
    // TODO: Find isle by name
    MapNode *node = findNode(name);
    if (node) {
        return node->isle;
    }
    return nullptr;
}

MapNode *Map::findNode(Isle isle)
{
    // TODO: Find node by value
    return findNodeRecursive(root, isle);
}

MapNode *Map::findNode(std::string name)
{
    // TODO: Find node by name
    return findNodeRecursive(root, name);
}
// Recursive helper function to search by Isle
MapNode *Map::findNodeRecursive(MapNode *node, Isle isle)
{
    if (!node) {
        return nullptr;
    }

    if (*node->isle == isle) {
        return node;
    }

    MapNode *leftResult = findNodeRecursive(node->left, isle);
    if (leftResult) {
        return leftResult;
    }

    return findNodeRecursive(node->right, isle);
}

// Recursive helper function to search by name
MapNode *Map::findNodeRecursive(MapNode *node, std::string name)
{
    if (!node) {
        return nullptr;
    }

    if (node->isle->getName() == name) {
        return node;
    }

    MapNode *leftResult = findNodeRecursive(node->left, name);
    if (leftResult) {
        return leftResult;
    }

    return findNodeRecursive(node->right, name);
}

void Map::display(MapNode *current, int depth, int state)
{
    // SOURCE:

    if (current->left)
        display(current->left, depth + 1, 1);

    for (int i = 0; i < depth; i++)
        printf("     ");

    if (state == 1) // left
        printf("   ┌───");
    else if (state == 2) // right
        printf("   └───");

    std::cout << "[" << *current->isle << "] - (" << current->height << ")\n"
              << std::endl;

    if (current->right)
        display(current->right, depth + 1, 2);
}

void Map::writeToFile(const std::string &filename)
{
    // TODO: Write the tree to filename output level by level
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "[Output] Failed to open file: " << filename << std::endl;
        return;
    }

    // Queue for level-order traversal
    std::queue<MapNode *> queue;
    queue.push(root);

    while (!queue.empty())
    {
        int levelSize = queue.size(); // Number of nodes in the current level
        for (int i = 0; i < levelSize; ++i)
        {
            MapNode *current = queue.front();
            queue.pop();

            if (current)
            {
                outFile << current->isle->getName() << " ";
                queue.push(current->left);
                queue.push(current->right);
            }
            else
            {
                outFile << "NULL ";
            }
        }

        outFile << std::endl; // Move to the next level
    }

    outFile.close();
}

void Map::writeIslesToFile(const std::string &filename)
{
    // TODO: Write Isles to output file in alphabetical order
    // Use 
    std::ofstream outFile(filename);
    MapNode *current = root;
    std::stack<MapNode *> stack;

    while (current != nullptr || !stack.empty())
    {
        while (current != nullptr)
        {
            stack.push(current);
            current = current->left;
        }

        current = stack.top();
        stack.pop();

        outFile << current->isle->getName() << std::endl;

        current = current->right;
    }

    outFile.close();
    std::cout << "[Output] " << "Isles have been written to " << filename << " in in alphabetical order." << std::endl;
}