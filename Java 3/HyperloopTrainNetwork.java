import java.io.IOException;
import java.io.Serializable;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class HyperloopTrainNetwork implements Serializable {
    static final long serialVersionUID = 11L;
    public double averageTrainSpeed;
    public final double averageWalkingSpeed = 1000 / 6.0;;
    public int numTrainLines;
    public Station startPoint;
    public Station destinationPoint;
    public List<TrainLine> lines;

    /**
     * Method with a Regular Expression to extract integer numbers from the fileContent
     * @return the result as int
     */
    public int getIntVar(String varName, String fileContent) {
        Pattern p = Pattern.compile("[\\t ]*" + varName + "[\\t ]*=[\\t ]*([0-9]+)");
        Matcher m = p.matcher(fileContent);
        m.find();
        return Integer.parseInt(m.group(1));
    }

    /**
     * Write the necessary Regular Expression to extract string constants from the fileContent
     * @return the result as String
     */
    public String getStringVar(String varName, String fileContent) {
        // TODO: Your code goes here
        Pattern p = Pattern.compile("[\\t ]*" + varName + "[\\t ]*=[\\t ]*[\\u0022]([a-zA-Z]+)");
        Matcher m = p.matcher(fileContent);
        m.find();
        return m.group(1);
    }

    /**
     * Write the necessary Regular Expression to extract floating point numbers from the fileContent
     * Your regular expression should support floating point numbers with an arbitrary number of
     * decimals or without any (e.g. 5, 5.2, 5.02, 5.0002, etc.).
     * @return the result as Double
     */
    public Double getDoubleVar(String varName, String fileContent) {
        // TODO: Your code goes here
        Pattern p = Pattern.compile("[\\t ]*" + varName + "[\\t ]*=[\\t ]*([0-9]+.?[0-9]*)");
        Matcher m = p.matcher(fileContent);
        m.find();
        return Double.parseDouble(m.group(1));
    }

    /**
     * Write the necessary Regular Expression to extract a Point object from the fileContent
     * points are given as an x and y coordinate pair surrounded by parentheses and separated by a comma
     * @return the result as a Point object
     */
    public Point getPointVar(String varName, String fileContent) {
        Point p1 = new Point(0, 0);
        // TODO: Your code goes here
        Pattern p = Pattern.compile("[\\t ]*" + varName + "[\\t ]*=[\\t ]*[\\u0028][\\t ]*([0-9]+)[\\\\t ]*[\\u002c][\\\\t ]*([0-9]+)[\\\\t ]*[\\u0029]");
        Matcher m = p.matcher(fileContent);
        m.find();
        p1.x = Integer.parseInt(m.group(1));
        p1.y = Integer.parseInt(m.group(2));
        return p1;
    } 

    /**
     * Function to extract the train lines from the fileContent by reading train line names and their 
     * respective stations.
     * @return List of TrainLine instances
     */
    public List<TrainLine> getTrainLines(String fileContent) {
        List<TrainLine> trainLines = new ArrayList<>();

        // Extract the number of train lines
        int numTrainLines = getIntVar("num_train_lines", fileContent);

        // Define regular expressions
        Pattern trainLinePattern = Pattern.compile("train_line_name\\s*=\\s*\"([^\"]+)\"");
        Pattern stationPattern = Pattern.compile("train_line_stations\\s*=\\s*(\\(\\s*\\d+\\s*,\\s*\\d+\\s*\\)(?:\\s*\\(\\s*\\d+\\s*,\\s*\\d+\\s*\\))*)");

        int currentIndex = 0;

        for (int i = 0; i < numTrainLines; i++) {
            // Find the train line name
            String trainLineName;
            try {
                trainLineName = getStringVar("train_line_name", fileContent.substring(currentIndex));
                currentIndex = fileContent.indexOf("train_line_name", currentIndex) + trainLineName.length();
            } catch (Exception e) {
                throw new IllegalStateException("Failed to find train_line_name: " + e.getMessage());
            }

            // Find the start index of train_line_stations for this train line
            int stationStartIndex = fileContent.indexOf("train_line_stations", currentIndex);
            if (stationStartIndex == -1) {
                throw new IllegalStateException("Expected train_line_stations after train_line_name");
            }
            stationStartIndex += "train_line_stations".length();
            currentIndex = stationStartIndex;

            // Find the next train line or end of the file
            int nextTrainLineIndex = fileContent.indexOf("train_line_name", currentIndex);
            if (nextTrainLineIndex == -1) {
                nextTrainLineIndex = fileContent.length();
            }

            // Extract stations substring
            String stationsSubstring = fileContent.substring(stationStartIndex, nextTrainLineIndex);

            // Extract points from the stations substring
            List<Point> trainLinePoints = getPoints(stationsSubstring);
            List<Station> trainLineStations = new ArrayList<>();
            int ii = 1;
            for (Point point : trainLinePoints) {
                trainLineStations.add(new Station(point, trainLineName + " Line Station " + ii));
                ii++;
            }

            // Add the train line to the list
            trainLines.add(new TrainLine(trainLineName, trainLineStations));

            // Update currentIndex to search for the next train line
            currentIndex = nextTrainLineIndex;
        }

        return trainLines;
    }

    // Method to extract multiple points from a string
    public List<Point> getPoints(String pointsString) {
        List<Point> points = new ArrayList<>();
        Pattern p = Pattern.compile("\\(\\s*(\\d+)\\s*,\\s*(\\d+)\\s*\\)");
        Matcher m = p.matcher(pointsString);

        while (m.find()) {
            int x = Integer.parseInt(m.group(1));
            int y = Integer.parseInt(m.group(2));
            points.add(new Point(x, y));
        }

        return points;
    }



    /**
     * Function to populate the given instance variables of this class by calling the functions above.
     */
    public void readInput(String filename) {

        // TODO: Your code goes here
        try {
            // Read the content of the file as a string
            String fileContent = new String(Files.readAllBytes(Paths.get(filename)));

            numTrainLines = getIntVar("num_train_lines", fileContent);
            startPoint = new Station(getPointVar("starting_point", fileContent), "Start Point");
            destinationPoint = new Station(getPointVar("destination_point", fileContent), "Destination");
            averageTrainSpeed = (getDoubleVar("average_train_speed", fileContent)*100/6.0);
            lines = getTrainLines(fileContent);

        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }

    }
}