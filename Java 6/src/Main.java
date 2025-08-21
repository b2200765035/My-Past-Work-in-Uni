import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        TeamMethods tm = new TeamMethods();
        List<String> typeAndIndex;
        ArrayList<IceHockeyTeam> iceTeams = new ArrayList<IceHockeyTeam>();
        ArrayList<HandballTeam> handTeams = new ArrayList<HandballTeam>();
        try {
            File fixtureFile = new File("fixtures.txt");
            Scanner fixtureReader = new Scanner(fixtureFile);
            while (fixtureReader.hasNextLine()) {
                String lineOfFixture = fixtureReader.nextLine();
                String[] arrOfFixture = lineOfFixture.split("\t", 0);
                String[] scores = arrOfFixture[3].split(":", 0);


                typeAndIndex = tm.teamFinder(arrOfFixture[0], arrOfFixture[1], iceTeams, handTeams);
                if(typeAndIndex.get(0).equals("None")){
                    if (arrOfFixture[0].equals("H")) {
                        handTeams.add(new HandballTeam(arrOfFixture[1]));
                    } else {
                        iceTeams.add(new IceHockeyTeam(arrOfFixture[1]));
                    }}
                    typeAndIndex = tm.teamFinder(arrOfFixture[0], arrOfFixture[1], iceTeams, handTeams);
                    if (typeAndIndex.get(0).equals("Hand")) {
                        handTeams.get(Integer.parseInt(typeAndIndex.get(1))).MatchResult(Integer.parseInt(scores[0]),
                                Integer.parseInt(scores[1]));
                    } else {
                        iceTeams.get(Integer.parseInt(typeAndIndex.get(1))).MatchResult(Integer.parseInt(scores[0]),
                                Integer.parseInt(scores[1]));
                    }



                typeAndIndex = tm.teamFinder(arrOfFixture[0], arrOfFixture[2], iceTeams, handTeams);
                if(typeAndIndex.get(0).equals("None")){
                    if (arrOfFixture[0].equals("H")) {
                        handTeams.add(new HandballTeam(arrOfFixture[2]));
                    } else {
                        iceTeams.add(new IceHockeyTeam(arrOfFixture[2]));
                    }}

                    typeAndIndex = tm.teamFinder(arrOfFixture[0], arrOfFixture[2], iceTeams, handTeams);
                    if (typeAndIndex.get(0).equals("Hand")) {
                        handTeams.get(Integer.parseInt(typeAndIndex.get(1))).MatchResult(Integer.parseInt(scores[1]),
                                Integer.parseInt(scores[0]));
                    } else {
                        iceTeams.get(Integer.parseInt(typeAndIndex.get(1))).MatchResult(Integer.parseInt(scores[1]),
                                Integer.parseInt(scores[0]));
                    }



                }
            fixtureReader.close();
            iceTeams.sort(new Sorting().reversed());
            handTeams.sort(new Sorting().reversed());

            try {
                FileWriter iceFile = new FileWriter("icehockey.txt");
                for (int i = 0; i < iceTeams.size(); i++){
                    int s = i + 1;
                    iceFile.write(s + "\t" + iceTeams.get(i).name + "\t" + iceTeams.get(i).match + "\t" +
                            iceTeams.get(i).win + "\t" + iceTeams.get(i).draw + "\t" + iceTeams.get(i).lose + "\t" +
                            iceTeams.get(i).setWin + ":" + iceTeams.get(i).setLost + "\t" + iceTeams.get(i).point + "\n");
                }
                iceFile.close();
            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();}

            try {
                FileWriter handFile = new FileWriter("handball.txt");
                for (int i = 0; i < handTeams.size(); i++){
                    int s = i + 1;
                    handFile.write(s + "\t" + handTeams.get(i).name + "\t" + handTeams.get(i).match + "\t" +
                            handTeams.get(i).win + "\t" + handTeams.get(i).draw + "\t" + handTeams.get(i).lose + "\t" +
                            handTeams.get(i).setWin + ":" + handTeams.get(i).setLost + "\t" + handTeams.get(i).point + "\n");
                }
                handFile.close();
            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();}




        } catch (FileNotFoundException e) {
                System.out.println("File containing people couldn't be read.");
                e.printStackTrace();
        }
    }
}
