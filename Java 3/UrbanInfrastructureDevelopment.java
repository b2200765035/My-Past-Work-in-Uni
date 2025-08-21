import java.io.File;
import java.io.Serializable;
import java.util.*;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.*;

public class UrbanInfrastructureDevelopment implements Serializable {
    static final long serialVersionUID = 88L;

    /**
     * Given a list of Project objects, prints the schedule of each of them.
     * Uses getEarliestSchedule() and printSchedule() methods of the current project to print its schedule.
     * @param projectList a list of Project objects
     */
    public void printSchedule(List<Project> projectList) {
        // TODO: YOUR CODE HERE
        for(Project project : projectList) {
            project.printSchedule(project.getEarliestSchedule());
            }
    }

    /**
     * TODO: Parse the input XML file and return a list of Project objects
     *
     * @param filename the input XML file
     * @return a list of Project objects
     */
    public List<Project> readXML(String filename) {
        List<Project> projectList = new ArrayList<>();
        // TODO: YOUR CODE HERE
        try {
            // Set up the XML document parser
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.parse(new File(filename));
            document.getDocumentElement().normalize();

            // Get all Project nodes
            NodeList projects1 = document.getElementsByTagName("Project");

            for (int i = 0; i < projects1.getLength(); i++) {
                Node projectNode = projects1.item(i);
                if (projectNode.getNodeType() == Node.ELEMENT_NODE) {
                    Element projectElement = (Element) projectNode;

                    // Extract project name
                    String projectName = projectElement.getElementsByTagName("Name").item(0).getTextContent();
                    List<Task> tasks = new ArrayList<>();


                    // Get all Task nodes within this project
                    NodeList taskList = projectElement.getElementsByTagName("Task");

                    for (int j = 0; j < taskList.getLength(); j++) {
                        Node taskNode = taskList.item(j);
                        if (taskNode.getNodeType() == Node.ELEMENT_NODE) {
                            Element taskElement = (Element) taskNode;

                            // Extract task details
                            int taskID = Integer.parseInt(taskElement.getElementsByTagName("TaskID").item(0).getTextContent());
                            String description = taskElement.getElementsByTagName("Description").item(0).getTextContent();
                            int duration = Integer.parseInt(taskElement.getElementsByTagName("Duration").item(0).getTextContent());

                            // Extract dependencies
                            List<Integer> dependencies = new ArrayList<>();
                            NodeList dependencyList = taskElement.getElementsByTagName("DependsOnTaskID");
                            for (int k = 0; k < dependencyList.getLength(); k++) {
                                dependencies.add(Integer.parseInt(dependencyList.item(k).getTextContent()));
                            }

                            // Create and add the task to the project
                            Task task = new Task(taskID, description, duration, dependencies);
                            tasks.add(task);
                        }
                    }

                    // Add the project to the list
                    Project project = new Project(projectName, tasks);
                    projectList.add(project);
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

        return projectList;
    }
}
