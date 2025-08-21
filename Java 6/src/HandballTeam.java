public class HandballTeam extends SportsTeam{
    HandballTeam(String name){
        super(name);
    }
    public void MatchResult(int scoreWin, int scoreLost){
        match = match + 1;
        setWin = setWin + scoreWin;
        setLost = setLost + scoreLost;
        if (scoreWin > scoreLost) {
            win = win + 1;
            point = point + 2;
        } else if (scoreWin < scoreLost) {
            lose = lose + 1;
        } else {
            draw = draw + 1;
            point = point + 1;
        }
    }
}
