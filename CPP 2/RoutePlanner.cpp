#include "RoutePlanner.h"
#include <iostream>
#include <fstream>
using namespace std;

// Array to help you out with name of the cities in order
const std::string cities[81] = { 
    "Adana", "Adiyaman", "Afyon", "Agri", "Amasya", "Ankara", "Antalya", "Artvin", "Aydin", "Balikesir", "Bilecik", 
    "Bingol", "Bitlis", "Bolu", "Burdur", "Bursa", "Canakkale", "Cankiri", "Corum", "Denizli", "Diyarbakir", "Edirne", 
    "Elazig", "Erzincan", "Erzurum", "Eskisehir", "Gaziantep", "Giresun", "Gumushane", "Hakkari", "Hatay", "Isparta", 
    "Mersin", "Istanbul", "Izmir", "Kars", "Kastamonu", "Kayseri", "Kirklareli", "Kirsehir", "Kocaeli", "Konya", "Kutahya", 
    "Malatya", "Manisa", "Kaharamanmaras", "Mardin", "Mugla", "Mus", "Nevsehir", "Nigde", "Ordu", "Rize", "Sakarya", 
    "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdag", "Tokat", "Trabzon", "Tunceli", "Urfa", "Usak", "Van", "Yozgat", 
    "Zonguldak", "Aksaray", "Bayburt", "Karaman", "Kirikkale", "Batman", "Sirnak", "Bartin", "Ardahan", "Igdir", 
    "Yalova", "Karabuk", "Kilis", "Osmaniye", "Duzce" 
};

// Constructor to initialize and load constraints
RoutePlanner::RoutePlanner(const std::string& distance_data, const std::string& priority_data, const std::string& restricted_data, int maxDistance)
    : maxDistance(maxDistance), totalDistanceCovered(0), numPriorityProvinces(0), numWeatherRestrictedProvinces(0) {

    // TO DO:
    // Load map data from file
    map.loadDistanceData(distance_data);
    
    // Mark all provinces as unvisited initially
    map.resetVisited();
    route.clear();

    // Load priority provinces
    loadPriorityProvinces(priority_data);

    // Load restricted provinces
    loadWeatherRestrictedProvinces(restricted_data);

}

// Load priority provinces from txt file to an array of indices
void RoutePlanner::loadPriorityProvinces(const std::string& filename) {
    // TODO: Your code here
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the Priority file!";
        return;
    }

    std::string line;
    numPriorityProvinces = 0; // Reset the count of priority provinces

    while (std::getline(file, line) && numPriorityProvinces < MAX_PRIORITY_PROVINCES) {
        // Extract the province index from the line
        size_t openParen = line.find('(');
        size_t closeParen = line.find(')');

        if (openParen != std::string::npos && closeParen != std::string::npos) {
            int index = std::stoi(line.substr(openParen + 1, closeParen - openParen - 1));
            priorityProvinces[numPriorityProvinces++] = index;
        }
    }

    file.close();
}

// Load weather-restricted provinces from txt file to an array of indices
void RoutePlanner::loadWeatherRestrictedProvinces(const std::string& filename) {
    // TODO: Your code here
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the Weather file!";
        return;
    }

    std::string line;
    numWeatherRestrictedProvinces = 0; // Reset the count of priority provinces

    while (std::getline(file, line) && numWeatherRestrictedProvinces < MAX_WEATHER_RESTRICTED_PROVINCES) {
        // Extract the province index from the line
        size_t openParen = line.find('(');
        size_t closeParen = line.find(')');

        if (openParen != std::string::npos && closeParen != std::string::npos) {
            int index = std::stoi(line.substr(openParen + 1, closeParen - openParen - 1));
            weatherRestrictedProvinces[numWeatherRestrictedProvinces++] = index;
        }
    }

    file.close();
}

// Checks if a province is a priority province
bool RoutePlanner::isPriorityProvince(int province) const {
    // TODO: Your code here
    for (int i = 0; i < numPriorityProvinces; ++i) {
        if (priorityProvinces[i] == province) {
            return true;
        }
    }
    return false;
}

// Checks if a province is weather-restricted
bool RoutePlanner::isWeatherRestricted(int province) const {
    // TODO: Your code here
    for (int i = 0; i < numWeatherRestrictedProvinces; ++i) {
        if (weatherRestrictedProvinces[i] == province) {
            return true;
        }
    }
    return false;
}

// Begins the route exploration from the starting point
void RoutePlanner::exploreRoute(int startingCity) {
    // TODO: Your code here
    
    // Start at the designated province (Ankara).
    // Push this starting point onto the Stack to track the journey and add it into the route.
    stack.push(startingCity);
    route.push_back(startingCity);

    // Mark the starting province as visited to avoid revisits.
    map.markAsVisited(startingCity);

    // Explore the neighbors of the starting city.,
    exploreFromProvince(startingCity);

    // If exploration is not complete, continue to exploring from last visited city.
    while (!isExplorationComplete()) {
        if (!queue.isEmpty()) {
            int nextCity = queue.dequeue();
            exploreFromProvince(nextCity);
        } else if (!stack.isEmpty()) {
            // Backtrack if no cities in queue
            backtrack();
            if (!stack.isEmpty()) {
                int nextCity = stack.peek();
                exploreFromProvince(nextCity);
            }
        }
    }
}

// Helper function to explore from a specific province
void RoutePlanner::exploreFromProvince(int province) {
    // TODO: Your code here
    // For each current province on the journey, enqueue all reachable, unvisited neighboring provinces.
    // Use enqueueNeighbors to populate the Queue with neighboring provinces,
    // prioritizing provinces in the priority provinces array (they should be dequeued first).
    enqueueNeighbors(province);

    // Dequeue each province from the Queue.
    // For each dequeued province:

        // Check if it is within the defined distance limit, if it is not a whether-restricted zone and if it hasn’t been visited.
        // If valid, it becomes part of the route. Push the province onto the Stack, mark it as visited, and explore its neighbors further.

    

    // Dequeue provinces and explore them
    while (!queue.isEmpty()) {
        int neighbor = queue.dequeue();
        // Check if the neighbor is within constraints
        if (map.isWithinRange(province, neighbor, maxDistance) && !map.visited[neighbor]) {

            // Mark the neighbor as visited
            map.markAsVisited(neighbor);

            // Add the province to the route and Stack
            stack.push(neighbor);
            route.push_back(neighbor);
            totalDistanceCovered += map.getDistance(province, neighbor);

            // Explore its neighbors
            enqueueNeighbors(neighbor);
        }
    }
}

void RoutePlanner::enqueueNeighbors(int province) {
    // TO DO: Enqueue priority & non-priority neighbors to the queue according to given constraints
    for (int i = 0; i < MAX_SIZE; ++i) {
        // Only looking through provinces within the max distance
        if (map.isWithinRange(province, i, maxDistance)) {
            // Skipping self and visited
            if (i == province || map.visited[i]) {
                continue;
            }

            // Skipping restricted provinces
            if (isWeatherRestricted(i)) {
                cout << "Province " << cities[i] << " is weather-restricted. Skipping." << endl;
                continue; 
            }

            // Enqueueing the rest
            if (isPriorityProvince(i)) {
                // Priority
                queue.enqueuePriority(i);
            } else {
                // Others
                queue.enqueue(i);
            }

        }
    }
}

void RoutePlanner::backtrack() {
    // If you reach a dead-end province 
    // TODO: Your code here
    int previousProvince = stack.pop();
}

bool RoutePlanner::isExplorationComplete() const {
    // TODO: Your code here
    return (stack.isEmpty() && queue.isEmpty());
}

void RoutePlanner::displayResults() const {
    // TODO: Your code here

    if (route.empty()) {
        cout << "No route was taken.\n";
        return;
    }

    // Display "Journey Completed!" message
    cout << "----------------------------" << endl;
    cout << "Journey Completed!" << endl;
    cout << "----------------------------" << endl;

    // Display the total number of provinces visited
    cout << "Total Number of Provinces Visited: " << map.countVisitedProvinces() << endl;

    // Display the total distance covered
    cout << "Total Distance Covered: " << totalDistanceCovered << " km" << endl;

    // Display the route in the order visited
    cout << "Route Taken:" << endl;

    for (int i = 0; i < route.size(); i++) {
        cout << cities[route[i]];
        if (i < route.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
    cout << endl;

    // Priority Province Summary
    int visitedPriority = 0;
    for(int i = 0; i < numPriorityProvinces; i++) {
        cout << cities[priorityProvinces[i]];
        if (map.isVisited(priorityProvinces[i])) {
            cout << " (Visited)" << endl;
            visitedPriority++;
        } else {
            cout << " (Not Visited)" << endl;
        }
    }

    cout << endl;
    cout << "Total Priority Provinces Visited: " << visitedPriority << " out of 5" << endl;
    if(visitedPriority < numPriorityProvinces) {
        cout << "Warning: Not all priority provinces were visited." << endl;
    } else {
        cout << "Success: All priority provinces were visited." << endl;
    }
}
