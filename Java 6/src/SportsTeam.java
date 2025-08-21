class SportsTeam{
    String name;
    int match = 0;
    int win = 0;
    int lose = 0;
    int draw = 0;
    int point = 0;
    int setWin = 0;
    int setLost = 0;
    int setPoint = setWin - setLost;

    public void MatchResult(int scoreWin, int scoreLost){
        match = match + 1;
        setWin = setWin + scoreWin;
        setLost = setLost + scoreLost;
        if (scoreWin > scoreLost) {
            win = win + 1;
            point = point + 3;
        } else if (scoreWin < scoreLost) {
            lose = lose + 1;
        } else {
            draw = draw + 1;
            point = point + 1;
        }
    }
    public SportsTeam (String name) {
        this.name = name;
    }

    public int getPoint() {
        return point;
    }
    public int getSetPoint() {
        return setPoint;
    }
}
