import java.util.ArrayList;
import java.util.List;
class TeamMethods {
        List<String> teamFinder (String type, String name, ArrayList<IceHockeyTeam> iceTeams, ArrayList<HandballTeam> handTeams) {
            String filmType = "None";
            int index = 0;
            List<String> typeAndIndex = new ArrayList<String>();

            if (type.equals("I")) {
                for (int i = 0; i < iceTeams.size(); i++) {
                    if (iceTeams.get(i).name.equals(name)) {
                        filmType = "Ice";
                        index = i;
                        break;
                    }
                }
            } else {
                for (int i = 0; i < handTeams.size(); i++) {
                    if (handTeams.get(i).name.equals(name)) {
                        filmType = "Hand";
                        index = i;
                        break;
                    }
                }
            }


            typeAndIndex.add(filmType);
            typeAndIndex.add(Integer.toString(index));
            return typeAndIndex;
        }
    }
