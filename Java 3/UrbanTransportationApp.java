import java.io.Serializable;
import java.util.*;

class UrbanTransportationApp implements Serializable {
    static final long serialVersionUID = 99L;
    TransportationGraph graph;
    
    public HyperloopTrainNetwork readHyperloopTrainNetwork(String filename) {
        HyperloopTrainNetwork hyperloopTrainNetwork = new HyperloopTrainNetwork();
        hyperloopTrainNetwork.readInput(filename);
        return hyperloopTrainNetwork;
    }

    /**
     * Function calculate the fastest route from the user's desired starting point to 
     * the desired destination point, taking into consideration the hyperloop train
     * network. 
     * @return List of RouteDirection instances
     */

    public Map<String, Double> dijkstra(TransportationGraph graph, String startNode) {
        // Initialize distances map to keep track of shortest distances from startNode
        Map<String, Double> distances = new HashMap<>();
        // Initialize priority queue for selecting nodes with the smallest tentative distance
        PriorityQueue<String> queue = new PriorityQueue<>(Comparator.comparingDouble(distances::get));

        // Initialize distances to infinity for all nodes except startNode
        for (String node : graph.getNodes()) {
            distances.put(node, node.equals(startNode) ? 0.0 : Double.POSITIVE_INFINITY);
        }

        // Add startNode to priority queue
        queue.add(startNode);

        // Main loop
        while (!queue.isEmpty()) {
            // Get node with the smallest tentative distance
            String currentNode = queue.poll();
            double currentDistance = distances.get(currentNode);

            // Update distances for neighboring nodes
            for (Map.Entry<String, Double> neighborEntry : graph.getNeighbors(currentNode).entrySet()) {
                String neighborNode = neighborEntry.getKey();
                double edgeWeight = neighborEntry.getValue();
                double newDistance = currentDistance + edgeWeight;

                // If newDistance is smaller, update distances and add neighbor to queue
                if (newDistance < distances.get(neighborNode)) {
                    distances.put(neighborNode, newDistance);
                    queue.add(neighborNode);
                }
            }
        }

        return distances;
    }

    public List<RouteDirection> getFastestRouteDirections(HyperloopTrainNetwork network) {
        // Construct the graph
        TransportationGraph graph = constructGraph(network);

        // Run Dijkstra's algorithm to find shortest paths
        Map<String, Double> shortestDistances = dijkstra(graph, network.startPoint.description);

        // Convert shortest distances to route directions
        List<RouteDirection> routeDirections = new ArrayList<>();


        String keyArray[] = shortestDistances.keySet().toArray(new String[0]);
        Collection<Double> values =  shortestDistances.values();
        Double valArray[] = values.toArray(new Double[0]);
        for (int i = 0; i < shortestDistances.size(); i++) {
            RouteDirection routeDirection = new RouteDirection(network.startPoint.description, keyArray[i], valArray[i], false);
            if (i == 0){
                routeDirection.startStationName = network.startPoint.description;
                routeDirection.endStationName = keyArray[i];
                routeDirection.duration = valArray[i];
                routeDirection.trainRide = false;
            }else{
                String source[] = keyArray[i-1].split(" ", 2);
                String arr[] = keyArray[i].split(" ", 2);
                if(source[0].equals(arr[0])){
                    routeDirection.startStationName = keyArray[i-1];
                    routeDirection.endStationName = keyArray[i];
                    routeDirection.duration = valArray[i];
                    routeDirection.trainRide = true;
                }else{
                    routeDirection.startStationName = keyArray[i-1];
                    routeDirection.endStationName = keyArray[i];
                    routeDirection.duration = valArray[i];
                    routeDirection.trainRide = false;
                }
            }
                routeDirections.add(routeDirection);

        }

        return routeDirections;
    }


    private TransportationGraph constructGraph(HyperloopTrainNetwork network) {
        TransportationGraph graph = new TransportationGraph();

        // Add stations to the graph
        graph.addStation(network.startPoint.description);
        graph.addStation(network.destinationPoint.description);
        for (TrainLine line : network.lines) {
            for (Station station : line.trainLineStations) {
                graph.addStation(station.description);
            }
        }

        // Add connections between stations
        for (TrainLine line : network.lines) {
            List<Station> stations = line.trainLineStations;
            for (int i = 0; i < stations.size() - 1; i++) {
                Station currentStation = stations.get(i);
                Station nextStation = stations.get(i + 1);
                double distance = calculateDistance(currentStation.coordinates, nextStation.coordinates);
                graph.addConnection(currentStation.description, nextStation.description, calculateTravelTime(distance,network.averageWalkingSpeed));

                // Add connections to adjacent stations in other train lines
                for (TrainLine otherLine : network.lines) {
                    if (otherLine != line) {
                        for (Station otherStation : otherLine.trainLineStations) {
                            double otherDistance = calculateDistance(currentStation.coordinates, otherStation.coordinates);
                            graph.addConnection(currentStation.description, otherStation.description, calculateTravelTime(otherDistance,network.averageWalkingSpeed));
                        }
                    }
                }
            }
        }

        // Add train connections between stations within the same train line
        for (TrainLine line : network.lines) {
            List<Station> stations = line.trainLineStations;
            for (int i = 0; i < stations.size() - 1; i++) {
                Station currentStation = stations.get(i);
                Station nextStation = stations.get(i + 1);
                double distance = calculateDistance(currentStation.coordinates, nextStation.coordinates);
                graph.addConnection(currentStation.description, nextStation.description, calculateTravelTime(distance,network.averageTrainSpeed));
            }
        }

        // Add connections from start station to reachable stations
        for (TrainLine line : network.lines) {
            List<Station> stations = line.trainLineStations;
            for (Station station : stations) {
                double distance = calculateDistance(network.startPoint.coordinates, station.coordinates);
                graph.addConnection(network.startPoint.description, station.description, calculateTravelTime(distance,network.averageWalkingSpeed));
            }
        }

        // Add connections from reachable stations to destination station
        for (TrainLine line : network.lines) {
            List<Station> stations = line.trainLineStations;
            for (Station station : stations) {
                double distance = calculateDistance(station.coordinates, network.destinationPoint.coordinates);
                graph.addConnection(station.description, network.destinationPoint.description, calculateTravelTime(distance,network.averageWalkingSpeed));
            }
        }

        return graph;
    }

    private double calculateDistance(Point p1, Point p2) {
        double ac = Math.abs(p2.y - p1.y);
        double cb = Math.abs(p2.x - p1.x);

        return Math.hypot(ac, cb);
    }

    private double calculateTravelTime(double distance, double speed) {
        return distance/ speed;
    }


    /**
     * Function to print the route directions to STDOUT
     */
    public void printRouteDirections(List<RouteDirection> directions) {
        
        // TODO: Your code goes here

    }
}

class StationNode {
    String name;
    List<StationEdge> connections;

    public StationNode(String name) {
        this.name = name;
        this.connections = new ArrayList<>();
    }
}

class StationEdge {
    StationNode destination;
    double weight; // Time or distance

    public StationEdge(StationNode destination, double weight) {
        this.destination = destination;
        this.weight = weight;
    }
}

class TransportationGraph {
    Map<String, StationNode> stations;

    public TransportationGraph() {
        this.stations = new HashMap<>();
    }

    public Set<String> getNodes() {
        return stations.keySet();
    }

    public Map<String, Double> getNeighbors(String stationName) {
        Map<String, Double> neighbors = new HashMap<>();
        StationNode stationNode = stations.get(stationName);
        if (stationNode != null) {
            for (StationEdge edge : stationNode.connections) {
                neighbors.put(edge.destination.name, edge.weight);
            }
        }
        return neighbors;
    }

    public void addStation(String name) {
        stations.put(name, new StationNode(name));
    }

    public void addConnection(String source, String destination, double weight) {
        StationNode sourceNode = stations.get(source);
        StationNode destNode = stations.get(destination);
        if (sourceNode != null && destNode != null) {
            sourceNode.connections.add(new StationEdge(destNode, weight));
            destNode.connections.add(new StationEdge(sourceNode, weight)); // Assuming bidirectional connections
        }
    }
}