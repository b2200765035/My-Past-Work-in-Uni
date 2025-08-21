import java.io.IOException;
//import java.lang.classfile.attribute.SyntheticAttribute;
import java.util.ArrayList;
import java.util.Map;
import java.util.Scanner;
import java.io.File;
/**
 * Main class
 */
// FREE CODE HERE
public class Main {
    public static void main(String[] args) throws IOException {
    	Scanner scanner;
        /* MISSION POWER GRID OPTIMIZATION BELOW **/
    	

        // TODO: Your code goes here
        // You are expected to read the file given as the first command-line argument to read 
        // the energy demands arriving per hour. Then, use this data to instantiate a 
        // PowerGridOptimization object. You need to call getOptimalPowerGridSolutionDP() method
        // of your PowerGridOptimization object to get the solution, and finally print it to STDOUT.


        File mission0 = new File(args[0]);
        scanner = new Scanner(mission0);
        ArrayList<Integer> energyDemands = new ArrayList<>();
        while (scanner.hasNext()) {
        	energyDemands.add(scanner.nextInt());
        }
        int sum = 0;
        for (int num : energyDemands) {
            sum += num;
        }
        PowerGridOptimization dynamic = new PowerGridOptimization(energyDemands);
        OptimalPowerGridSolution dynamicSol;
        dynamicSol = dynamic.getOptimalPowerGridSolutionDP();
        int satPower = dynamicSol.getmaxNumberOfSatisfiedDemands();
        int unsatPower = sum - satPower;
        ArrayList<Integer> release = dynamicSol.getHoursToDischargeBatteriesForMaxEfficiency();
        System.out.println("##MISSION POWER GRID OPTIMIZATION##");
        System.out.println("The total number of demanded gigawatts: " + sum);
        System.out.println("Maximum number of satisfied gigawatts: " + satPower);
        System.out.print("Hours at which the battery bank should be discharged: ");
        for(int i = 0; i < release.size(); i++){
            System.out.print(release.get(i));
            if(i != release.size()-1){
                System.out.print(", ");
            }
        }
        System.out.println();
        System.out.println("The number of unsatisfied gigawatts: " + unsatPower);
        System.out.println("##MISSION POWER GRID OPTIMIZATION COMPLETED##");



        /* MISSION ECO-MAINTENANCE BELOW **/
        File mission1 = new File(args[0]);
        scanner = new Scanner(mission1);
        ArrayList<Integer> energyNeeds = new ArrayList<>();
        while (scanner.hasNext()) {
            energyNeeds.add(scanner.nextInt());
        }
        int avalibleESV = energyNeeds.get(0);
        energyNeeds.remove(0);
        int ESVCapacity = energyNeeds.get(0);
        energyNeeds.remove(0);

        OptimalESVDeploymentGP greedy = new OptimalESVDeploymentGP(energyNeeds);
        int minNeeded = greedy.getMinNumESVsToDeploy(avalibleESV, ESVCapacity);

        System.out.println("##MISSION ECO-MAINTENANCE##");
        // TODO: Your code goes here
        // You are expected to read the file given as the second command-line argument to read
        // the number of available ESVs, the capacity of each available ESV, and the energy requirements 
        // of the maintenance tasks. Then, use this data to instantiate an OptimalESVDeploymentGP object.
        // You need to call getMinNumESVsToDeploy(int maxNumberOfAvailableESVs, int maxESVCapacity) method
        // of your OptimalESVDeploymentGP object to get the solution, and finally print it to STDOUT.
        if(minNeeded == -1){
            System.out.println("Warning: Mission Eco-Maintenance Failed.");
        } else {
            System.out.println("The minimum number of ESVs to deploy: " + minNeeded);
            ArrayList<ArrayList<Integer>> tasks = greedy.getMaintenanceTasksAssignedToESVs();
            for(int i = 0; i < tasks.size(); i++){
                ArrayList<Integer> task = tasks.get(i);
                System.out.print("ESV " + i+1 + " tasks: [");
                for(int j = 0; j < task.size(); j++){
                    System.out.print(task.get(j));
                    if(j != release.size()-1){
                        System.out.print(", ");
                    }
                }
                System.out.println("]");
            }
        }
        System.out.println("##MISSION ECO-MAINTENANCE COMPLETED##");
    }
}
