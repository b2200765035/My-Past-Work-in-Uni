import java.util.ArrayList;
import java.util.Collections;

/**
 * This class accomplishes Mission POWER GRID OPTIMIZATION
 */
public class PowerGridOptimization {
    private ArrayList<Integer> amountOfEnergyDemandsArrivingPerHour;

    public PowerGridOptimization(ArrayList<Integer> amountOfEnergyDemandsArrivingPerHour){
        this.amountOfEnergyDemandsArrivingPerHour = amountOfEnergyDemandsArrivingPerHour;
    }

    public ArrayList<Integer> getAmountOfEnergyDemandsArrivingPerHour() {
        return amountOfEnergyDemandsArrivingPerHour;
    }
    /**
     *     Function to implement the given dynamic programming algorithm
     *     SOL(0) <- 0
     *     HOURS(0) <- [ ]
     *     For{j <- 1...N}
     *         SOL(j) <- max_{0<=i<j} [ (SOL(i) + min[ E(j), P(j − i) ] ]
     *         HOURS(j) <- [HOURS(i), j]
     *     EndFor
     *
     * @return OptimalPowerGridSolution
     */
    public OptimalPowerGridSolution getOptimalPowerGridSolutionDP() {
        // TODO: YOUR CODE HERE
        ArrayList<Integer> SOL = new ArrayList<>();
        SOL.add(0);
        ArrayList<ArrayList<Integer>> HOURS = new ArrayList<>();
        ArrayList<Integer> temp = new ArrayList<>();
        HOURS.add(temp);
        for(int j = 1; j < amountOfEnergyDemandsArrivingPerHour.size() + 1; j++){
            int bestCost = 0;
            int bestI = 0;
            for(int i = 0; i < j; i++){
                int cost = SOL.get(i) + Math.min(amountOfEnergyDemandsArrivingPerHour.get(j - 1), (j-i)*(j-i));
                if (cost > bestCost){
                    bestCost = cost;
                    bestI = i;
                }
            }

            SOL.add(bestCost);
            ArrayList<Integer> temp2 = new ArrayList<>(HOURS.get(bestI));
            temp2.add(j);
            HOURS.add(temp2);
        }

        Integer maxVal = Collections.max(SOL);
        int maxIdx = SOL.indexOf(maxVal);
        ArrayList<Integer> optimal = new ArrayList<>(HOURS.get(maxIdx));
        return new OptimalPowerGridSolution(maxVal, optimal);
    }
}