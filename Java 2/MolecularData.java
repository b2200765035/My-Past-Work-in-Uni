import java.util.*;

// Class representing molecular data
public class MolecularData {

    // Private fields
    private final List<Molecule> molecules; // List of molecules

    // Constructor
    public MolecularData(List<Molecule> molecules) {
        this.molecules = molecules;;
    }

    // Getter for molecules
    public List<Molecule> getMolecules() {
        return molecules;
    }

    // Method to identify molecular structures
    // Return the list of different molecular structures identified from the input data
    public List<MolecularStructure> identifyMolecularStructures() {
        List<MolecularStructure> structures = new ArrayList<>();

        /* YOUR CODE HERE */

        Set<Molecule> visited = new HashSet<>();

        for (Molecule molecule : molecules) {
            if (!visited.contains(molecule)) {
                MolecularStructure structure = new MolecularStructure();
                dfs(molecule, visited, structure);
                structures.add(structure);
            }
        }

        return structures;
    }

    // Depth-first search to identify molecules bonded to each other
    private void dfs(Molecule molecule, Set<Molecule> visited, MolecularStructure structure) {
        visited.add(molecule);
        structure.addMolecule(molecule);

        for (Molecule neighbor : findConnectedMolecules(molecule)) {
            if (!visited.contains(neighbor)) {
                dfs(neighbor, visited, structure);
            }
        }
    }

    // Helper method to find connected molecules, including those with missing bonds
    private List<Molecule> findConnectedMolecules(Molecule molecule) {
        List<Molecule> connectedMolecules = new ArrayList<>();
        for (Molecule m : molecules) {
            if (m.getBonds().contains(molecule.getId()) || molecule.getBonds().contains(m.getId())) {
                connectedMolecules.add(m);
            }
        }
        return connectedMolecules;
    }

    // Method to print given molecular structures
    public void printMolecularStructures(List<MolecularStructure> molecularStructures, String species) {

        /* YOUR CODE HERE */

        int size = molecularStructures.size();
        System.out.println(size + " molecular structures have been discovered in " + species + ".");
        for(int i = 0; i < size; i++) {
            MolecularStructure molecularStructure = molecularStructures.get(i);
            int moleculeCount = i+1;
            System.out.println("Molecules in Molecular Structure "+ moleculeCount +": " + molecularStructure.toString());
        }
    }

    // Method to identify anomalies given a source and target molecular structure
    // Returns a list of molecular structures unique to the targetStructure only
    public static ArrayList<MolecularStructure> getVitalesAnomaly(List<MolecularStructure> sourceStructures, List<MolecularStructure> targetStructures) {
        ArrayList<MolecularStructure> anomalyList = new ArrayList<>();
        
        /* YOUR CODE HERE */
        for (MolecularStructure targetStructure : targetStructures) {
            if (!sourceStructures.contains(targetStructure)) {
                anomalyList.add(targetStructure);
            }
        }

        return anomalyList;
    }

    // Method to print Vitales anomalies
    public void printVitalesAnomaly(List<MolecularStructure> molecularStructures) {

        /* YOUR CODE HERE */
        System.out.println("Molecular structures unique to Vitales individuals:");
        for (MolecularStructure molecularStructure : molecularStructures) {
            System.out.println(molecularStructure.toString());
        }

    }
}
