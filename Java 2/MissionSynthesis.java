import java.util.*;

// Class representing the Mission Synthesis
public class MissionSynthesis {

    // Private fields
    private final List<MolecularStructure> humanStructures; // Molecular structures for humans
    private final ArrayList<MolecularStructure> diffStructures; // Anomalies in Vitales structures compared to humans

    // Constructor
    public MissionSynthesis(List<MolecularStructure> humanStructures, ArrayList<MolecularStructure> diffStructures) {
        this.humanStructures = humanStructures;
        this.diffStructures = diffStructures;
    }

    // Method to synthesize bonds for the serum
    public List<Bond> synthesizeSerum() {
        List<Bond> serum = new ArrayList<>();

        /* YOUR CODE HERE */

        //Selecting human molecules
        List<Molecule> baseHumanMolecules = new ArrayList<>();
        for (MolecularStructure structure : humanStructures) {
            Molecule lowestBondMolecule = structure.getMoleculeWithWeakestBondStrength();
            baseHumanMolecules.add(lowestBondMolecule);
        }

        //Selecting Vitales molecules
        List<Molecule> baseVitalesMolecules = new ArrayList<>();
        for (MolecularStructure structure : diffStructures) {
            Molecule lowestBondMolecule = structure.getMoleculeWithWeakestBondStrength();
            baseVitalesMolecules.add(lowestBondMolecule);
        }

        //Selecting the base molecule
        baseHumanMolecules.addAll(baseVitalesMolecules);
        Molecule baseMolecule = baseHumanMolecules.stream().min(Comparator.comparing(Molecule::getBondStrength)).orElse(null);
        baseHumanMolecules.remove(baseMolecule);

        //Making the serum
        int serumSize = baseHumanMolecules.size();
        int baseStrength = baseMolecule.getBondStrength();
        for(int i = 0; i < serumSize; i++){
            Molecule otherMolecule = baseHumanMolecules.stream().min(Comparator.comparing(Molecule::getBondStrength)).orElse(null);
            baseHumanMolecules.remove(otherMolecule);
            int otherStrength =  otherMolecule.getBondStrength();
            double weigth = (double) (baseStrength + otherStrength) /2;
            int compare = baseMolecule.compareTo(otherMolecule);
            if(compare > 0){
                Bond bond = new Bond(otherMolecule, baseMolecule, weigth);
                serum.add(bond);
            } else if (compare < 0){
                Bond bond = new Bond(baseMolecule, otherMolecule, weigth);
                serum.add(bond);
            }
        }
        return serum;
    }

    // Method to print the synthesized bonds
    public void printSynthesis(List<Bond> serum) {

        /* YOUR CODE HERE */

        List<Molecule> baseHumanMolecules = new ArrayList<>();
        for (MolecularStructure structure : humanStructures) {
            Molecule lowestBondMolecule = structure.getMoleculeWithWeakestBondStrength();
            baseHumanMolecules.add(lowestBondMolecule);
        }
        System.out.println("Typical human molecules selected for synthesis: " + baseHumanMolecules);

        //Selecting Vitales molecules
        List<Molecule> baseVitalesMolecules = new ArrayList<>();
        for (MolecularStructure structure : diffStructures) {
            Molecule lowestBondMolecule = structure.getMoleculeWithWeakestBondStrength();
            baseVitalesMolecules.add(lowestBondMolecule);
        }
        System.out.println("Vitales molecules selected for synthesis: " + baseVitalesMolecules);


        System.out.println("Synthesizing the serum...");

        double totalWeight = 0;
        for(Bond bond : serum){
            System.out.println("Forming a bond between " + bond.getTo() +" - " + bond.getFrom() + " with strength " + bond.getWeight());
            totalWeight += bond.getWeight();
        }
        System.out.println("The total serum bond strength is " + totalWeight);

    }
}
