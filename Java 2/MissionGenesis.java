import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.xml.sax.SAXException;

import java.io.File;
import java.io.IOException;
import java.util.*;

// Class representing the mission of Genesis
public class MissionGenesis {

    // Private fields
    private MolecularData molecularDataHuman; // Molecular data for humans
    private MolecularData molecularDataVitales; // Molecular data for Vitales

    // Getter for human molecular data
    public MolecularData getMolecularDataHuman() {
        return molecularDataHuman;
    }

    // Getter for Vitales molecular data
    public MolecularData getMolecularDataVitales() {
        return molecularDataVitales;
    }

    // Method to read XML data from the specified filename
    // This method should populate molecularDataHuman and molecularDataVitales fields once called
    public void readXML(String filename) {

        /* YOUR CODE HERE */

        try {
            File inputFile = new File(filename);
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(inputFile);
            doc.getDocumentElement().normalize();

            // Read data for Human Molecular Data
            NodeList humanMolecularDataList = doc.getElementsByTagName("HumanMolecularData");
            processMolecularData(humanMolecularDataList, "h");

            // Read data for Vitales Molecular Data
            NodeList vitalesMolecularDataList = doc.getElementsByTagName("VitalesMolecularData");
            processMolecularData(vitalesMolecularDataList, "v");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void processMolecularData(NodeList nodeList, String human) {
        for (int i = 0; i < nodeList.getLength(); i++) {
            Element molecularDataElement = (Element) nodeList.item(i);
            NodeList moleculeNodes = molecularDataElement.getElementsByTagName("Molecule");
            List<Molecule> molecules = new ArrayList<>();
            for (int j = 0; j < moleculeNodes.getLength(); j++) {
                Element moleculeElement = (Element) moleculeNodes.item(j);
                String id = moleculeElement.getElementsByTagName("ID").item(0).getTextContent();
                int bondStrength = Integer.parseInt(moleculeElement.getElementsByTagName("BondStrength").item(0).getTextContent());
                List<String> bonds = new ArrayList<>();
                NodeList bondsNodes = moleculeElement.getElementsByTagName("Bonds").item(0).getChildNodes();
                for (int k = 0; k < bondsNodes.getLength(); k++) {
                    if (bondsNodes.item(k).getNodeType() == org.w3c.dom.Node.ELEMENT_NODE) {
                        String bondId = bondsNodes.item(k).getTextContent();
                        bonds.add(bondId);
                    }
                }
                Set<String> set = new HashSet<>(bonds);
                bonds.clear();
                bonds.addAll(set);
                Molecule molecule = new Molecule(id, bondStrength, bonds);
                molecules.add(molecule);
            }
            // Now you have a list of molecules, you can create a MolecularData object and add these molecules to
            if(human.equals("h")) {
                molecularDataHuman = new MolecularData(molecules);
            } else if (human.equals("v")) {
                molecularDataVitales = new MolecularData(molecules);
            }
        }
    }
}