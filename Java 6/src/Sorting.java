import java.util.Comparator;
import java.lang.Integer;

public class Sorting implements Comparator<SportsTeam> {
    @Override
    public int compare(SportsTeam st1, SportsTeam st2) {
        int a = Integer.compare(st1.point, st2.point);
        if (a != 0) {
            return a;
        }
        return Integer.compare(st1.setPoint, st2.setPoint);
    }
}