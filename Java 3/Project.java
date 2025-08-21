import java.io.Serializable;
import java.util.*;

public class Project implements Serializable {
    static final long serialVersionUID = 33L;
    private final String name;
    private final List<Task> tasks;

    public Project(String name, List<Task> tasks) {
        this.name = name;
        this.tasks = tasks;
    }

    /**
     * @return the total duration of the project in days
     */
    public int getProjectDuration() {
        int projectDuration = 0;

        // TODO: YOUR CODE HERE
        int[] earliestStartTimes = getEarliestSchedule();

        projectDuration = tasks.get(earliestStartTimes.length-1).getDuration() + earliestStartTimes[earliestStartTimes.length-1];

        return projectDuration;
    }

    /**
     * Schedule all tasks within this project such that they will be completed as early as possible.
     *
     * @return An integer array consisting of the earliest start days for each task.
     */
    public int[] getEarliestSchedule() {

        // TODO: YOUR CODE HERE
        Map<Integer, Task> taskMap = new HashMap<>();
        for (Task task : tasks) {
            taskMap.put(task.getTaskID(), task);
        }

        int[] earliestStartTimes = new int[tasks.size()];
        Arrays.fill(earliestStartTimes, 0);

        //Kahn's Algorithm
        Map<Integer, List<Integer>> adjList = new HashMap<>();
        Map<Integer, Integer> inDegree = new HashMap<>();

        for (Task task : tasks) {
            inDegree.put(task.getTaskID(), 0);
            adjList.put(task.getTaskID(), new ArrayList<>());
        }

        for (Task task : tasks) {
            for (int dependency : task.getDependencies()) {
                adjList.get(dependency).add(task.getTaskID());
                inDegree.put(task.getTaskID(), inDegree.get(task.getTaskID()) + 1);
            }
        }

        Queue<Integer> queue = new LinkedList<>();
        for (Map.Entry<Integer, Integer> entry : inDegree.entrySet()) {
            if (entry.getValue() == 0) {
                queue.add(entry.getKey());
            }
        }

        List<Integer> topOrder = new ArrayList<>();
        while (!queue.isEmpty()) {
            int current = queue.poll();
            topOrder.add(current);

            for (int neighbor : adjList.get(current)) {
                inDegree.put(neighbor, inDegree.get(neighbor) - 1);
                if (inDegree.get(neighbor) == 0) {
                    queue.add(neighbor);
                }
            }
        }

        //Early time
        for (int taskID : topOrder) {
            Task task = taskMap.get(taskID);
            int earliestStart = 0;

            for (int dependency : task.getDependencies()) {
                Task depTask = taskMap.get(dependency);
                earliestStart = Math.max(earliestStart, earliestStartTimes[depTask.getTaskID()] + depTask.getDuration());
            }

            earliestStartTimes[taskID] = earliestStart;
        }

        return earliestStartTimes;
    }

    public static void printlnDash(int limit, char symbol) {
        for (int i = 0; i < limit; i++) System.out.print(symbol);
        System.out.println();
    }

    /**
     * Some free code here. YAAAY! 
     */
    public void printSchedule(int[] schedule) {
        int limit = 65;
        char symbol = '-';
        printlnDash(limit, symbol);
        System.out.println(String.format("Project name: %s", name));
        printlnDash(limit, symbol);

        // Print header
        System.out.println(String.format("%-10s%-45s%-7s%-5s","Task ID","Description","Start","End"));
        printlnDash(limit, symbol);
        for (int i = 0; i < schedule.length; i++) {
            Task t = tasks.get(i);
            System.out.println(String.format("%-10d%-45s%-7d%-5d", i, t.getDescription(), schedule[i], schedule[i]+t.getDuration()));
        }
        printlnDash(limit, symbol);
        System.out.println(String.format("Project will be completed in %d days.", tasks.get(schedule.length-1).getDuration() + schedule[schedule.length-1]));
        printlnDash(limit, symbol);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Project project = (Project) o;

        int equal = 0;

        for (Task otherTask : ((Project) o).tasks) {
            if (tasks.stream().anyMatch(t -> t.equals(otherTask))) {
                equal++;
            }
        }

        return name.equals(project.name) && equal == tasks.size();
    }

}
