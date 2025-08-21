import java.io.*;
import java.util.ArrayList;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class Main {

    public static void main(String[] args) throws IOException {
        //Treemap for callience and zorde
        TreeMap<String, Token> callience = new TreeMap<>();
        TreeMap<String, Token> zorde = new TreeMap<>();


        //Reading the initials file for board width and length
        BufferedReader in = new BufferedReader(new FileReader(args[0]), 1024);
        in.readLine();
        String lin = in.readLine();
        String[] line = lin.split("x");
        int length = Integer.parseInt(line[0]);
	    Token[][] board = new Token[length][length];

	    //This is the empty token to help print it
        Token empty = new Token ("  ");

	    //Initials block
	    File initialsFile = new File(args[0]);
        Scanner initialsReader = null;
        try {
            initialsReader = new Scanner(initialsFile);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        while (true) {
            assert initialsReader != null;
            if (!initialsReader.hasNextLine()) break;
            String[] initialsList = initialsReader.nextLine().split(" ");
            switch (initialsList[0]) {
                case "DWARF": {
                    callience.put(initialsList[1], new Dwarf(initialsList[1], Integer.parseInt(initialsList[2]),
                            Integer.parseInt(initialsList[3])));
                    board[Integer.parseInt(initialsList[3])][Integer.parseInt(initialsList[2])] = callience.get(initialsList[1]);
                    break;
                }
                case "ELF": {
                    callience.put(initialsList[1], new Elf(initialsList[1], Integer.parseInt(initialsList[2]),
                            Integer.parseInt(initialsList[3])));
                    board[Integer.parseInt(initialsList[3])][Integer.parseInt(initialsList[2])] = callience.get(initialsList[1]);
                    break;
                }
                case "HUMAN": {
                    callience.put(initialsList[1], new Human(initialsList[1], Integer.parseInt(initialsList[2]),
                            Integer.parseInt(initialsList[3])));
                    board[Integer.parseInt(initialsList[3])][Integer.parseInt(initialsList[2])] = callience.get(initialsList[1]);
                    break;
                }
                case "GOBLIN": {
                    zorde.put(initialsList[1], new Goblin(initialsList[1], Integer.parseInt(initialsList[2]),
                            Integer.parseInt(initialsList[3])));
                    board[Integer.parseInt(initialsList[3])][Integer.parseInt(initialsList[2])] = zorde.get(initialsList[1]);
                    break;
                }
                case "ORK": {
                    zorde.put(initialsList[1], new Ork(initialsList[1], Integer.parseInt(initialsList[2]),
                            Integer.parseInt(initialsList[3])));
                    board[Integer.parseInt(initialsList[3])][Integer.parseInt(initialsList[2])] = zorde.get(initialsList[1]);
                    break;
                }
                case "TROLL": {
                    zorde.put(initialsList[1], new Troll(initialsList[1], Integer.parseInt(initialsList[2]),
                            Integer.parseInt(initialsList[3])));
                    board[Integer.parseInt(initialsList[3])][Integer.parseInt(initialsList[2])] = zorde.get(initialsList[1]);
                    break;
                }
            }
        }
        initialsReader.close();


        //Initializing the output file
        FileWriter outputWriter = new FileWriter(args[2]);



        //Printing the start of the game
        print(length, board, empty, callience, zorde, outputWriter);


        //Commands block
        File commandsFile = new File (args[1]);
        Scanner commandsReader;
        commandsReader = new Scanner(commandsFile);
        OUTER_LOOP: while (commandsReader.hasNextLine()){
            String data = commandsReader.nextLine();
            String[] commandsArr = data.split(" ");
            String[] moveArray = commandsArr[1].split(";");
            String[] nameArr = commandsArr[0].split("(?!^)");
            Token activeToken = null;
            int i = 0;
            int move = 1;

            //This block checks and assigns the token that we will use
            switch (nameArr[0]) {
                case "D":  case "H":  case "E": {
                    activeToken = callience.get(commandsArr[0]);
                    break;
                }
                case "G": case "O": case "T": {
                    activeToken = zorde.get(commandsArr[0]);
                    break;
                }
            }


            //This block checks if movement is same as maxMoveCount
            if (moveArray.length != activeToken.maxMove * 2){
                new MoveCountException(outputWriter);
                continue;
            }


            //This block checks if the movement is still in bounds
            int tempX = activeToken.x;
            int tempY = activeToken.y;
            while (i < moveArray.length){
                tempX += Integer.parseInt(moveArray[i]);
                tempY += Integer.parseInt(moveArray[i+1]);
                i += 2;
                if (0 > tempX || tempX >= length || 0 > tempY || tempY >= length) {
                    new MoveOutOfBoundsException(outputWriter);
                    continue OUTER_LOOP;
                }
            }


            //This block heals allies if the token has hasHeal
            if (activeToken.hasHeal){
                activeToken.Heal(board);
            }


            //We're reducing the hp if there is an overheal, we don't have to check for callience because no one in callience can heal;
            for (Map.Entry<String, Token> entry : zorde.entrySet())
                if ( entry.getValue().currentHP > entry.getValue().maxHP){
                    entry.getValue().currentHP = entry.getValue().maxHP;
                }


            //Bulk of our code: The Movement Block
            while (move <= activeToken.maxMove){
                int xMod = Integer.parseInt(moveArray[2 * move - 2]);
                int yMod = Integer.parseInt(moveArray[2 * move - 1]);
                Token wantedToken = board[activeToken.y + yMod][activeToken.x + xMod];
                if (wantedToken != null) {
                    //This block activates if there is something in our way
                    if(wantedToken.isCallience == activeToken.isCallience){
                        //This part activates if they're allies
                        print(length, board, empty, callience, zorde, outputWriter);
                        break;
                    } else {
                        //This part activates if they're enemies
                        //Dealing the first hit
                        wantedToken.currentHP -= activeToken.ap;
                        if (activeToken.currentHP > wantedToken.currentHP){
                            //ActiveToken's HP > WantedToken's HP
                            activeToken.currentHP -= wantedToken.currentHP;
                            wantedToken.currentHP = 0;
                            board[activeToken.y][activeToken.x] = null;
                            board[wantedToken.y][wantedToken.x] = null;
                            switch (wantedToken.getClass().getName()){
                                case "Dwarf": case "Elf": case "Human": callience.remove(wantedToken.name);
                                case "Goblin": case "Ork": case "Troll": zorde.remove(wantedToken.name);
                            }
                            board[wantedToken.y][wantedToken.x] = activeToken;
                            activeToken.x += xMod;
                            activeToken.y += yMod;
                            print(length, board, empty, callience, zorde, outputWriter);
                            break;
                        } else if (activeToken.currentHP < wantedToken.currentHP){
                            //ActiveToken's HP < WantedToken's HP
                            wantedToken.currentHP -= activeToken.currentHP;
                            activeToken.currentHP = 0;
                            board[activeToken.y][activeToken.x] = null;
                            switch (activeToken.getClass().getName()){
                                case "Dwarf": case "Elf": case "Human": callience.remove(activeToken.name);
                                case "Goblin": case "Ork": case "Troll": zorde.remove(activeToken.name);
                            }
                            print(length, board, empty, callience, zorde, outputWriter);
                            break;
                        } else {
                            //ActiveToken's HP = WantedToken's HP
                            activeToken.currentHP = 0;
                            wantedToken.currentHP = 0;
                            board[activeToken.y][activeToken.x] = null;
                            switch (activeToken.getClass().getName()){
                                case "Dwarf": case "Elf": case "Human": callience.remove(activeToken.name);
                                case "Goblin": case "Ork": case "Troll": zorde.remove(activeToken.name);
                            }
                            board[wantedToken.y][wantedToken.x] = null;
                            switch (wantedToken.getClass().getName()){
                                case "Dwarf": case "Elf": case "Human": callience.remove(wantedToken.name);
                                case "Goblin": case "Ork": case "Troll": zorde.remove(wantedToken.name);
                            }
                            print(length, board, empty, callience, zorde, outputWriter);
                            break;
                        }
                    }
                } else {
                    //This part is for movement
                    // Moving our token
                    board[activeToken.y][activeToken.x] = null;
                    activeToken.x += xMod;
                    activeToken.y += yMod;
                    board[activeToken.y][activeToken.x] = activeToken;


                    //This block activates if we're at the end of our movement
                    if (move == activeToken.maxMove){
                        if(activeToken.hasRangedAttack){
                            activeToken.RangedAttack(board);
                            print(length, board, empty, callience, zorde, outputWriter);
                            break;
                        } else {
                            activeToken.Attack(board);
                            print(length, board, empty, callience, zorde, outputWriter);
                            break;
                        }
                    } else {
                        if(activeToken.hasMoveAttack){
                            activeToken.Attack(board);
                        }
                    }
                }
                //Cleaning up the dead bodies

                move++;
            }
        }
        outputWriter.close();
        commandsReader.close();
    }

    //This method prints out the board.
    public static void print(int width, Token[][] board, Token empty, TreeMap<String, Token> callience, TreeMap<String, Token> zorde, FileWriter outputWriter) throws IOException {
        TreeMap<String, Token> everyone = new TreeMap<>();
        ArrayList<String> deadBodies = new ArrayList<>();


        //This part cleans the dead bodies
        for (Map.Entry<String, Token> entry : callience.entrySet()){
            if (entry.getValue().currentHP <= 0){
                board[entry.getValue().y][entry.getValue().x] = null;
                deadBodies.add(entry.getKey());
            }
        }
        for (String dead : deadBodies){
            callience.remove(dead);
        }
        deadBodies.clear();
        for (Map.Entry<String, Token> entry : zorde.entrySet()){
            if (entry.getValue().currentHP <= 0){
                board[entry.getValue().y][entry.getValue().x] = null;
                deadBodies.add(entry.getKey());
            }
        }
        for (String dead : deadBodies){
            zorde.remove(dead);
        }
        deadBodies.clear();


        //This part prints the board
        for (int i=0; i<width + 1; i++){
            outputWriter.write("**");
        }
        for(Token[] row : board){
            outputWriter.write("\n*");
            for(Token token : row){
                if (token == null){
                    token = empty;
                }
                outputWriter.write(token.name);
            }
            outputWriter.write("*");
        }
        outputWriter.write("\n");
        for (int i=0; i< width + 1; i++){
            outputWriter.write("**");
        }
        outputWriter.write("\n\n");


        //This part prints the hp's
        everyone.putAll(callience);
        everyone.putAll(zorde);
        for (Map.Entry<String, Token> entry : everyone.entrySet()){
            outputWriter.write(entry.getKey() + "\t" + entry.getValue().currentHP + "\t(" + entry.getValue().maxHP + ")\n");
        }
        outputWriter.write("\n");


        //This part prints if anyone won
        if (callience.isEmpty()){
            outputWriter.write("Game Finished\nZorde Wins");
        }
        if (zorde.isEmpty()){
            outputWriter.write("Game Finished\nCallience Wins");
        }
    }
}


class Token {
    String name;
    int x;
    int y;
    int ap;
    int maxHP;
    int maxMove;
    int healPoint;
    int rangedAP;
    int currentHP;
    boolean isCallience;
    boolean hasHeal;
    boolean hasMoveAttack;
    boolean hasRangedAttack;

    Token(String name){
        this.name = name;
    }


    void Attack(Token[][] board){
        int rowStart  = Math.max( y - 1, 0   );
        int rowFinish = Math.min( y + 1, board.length - 1 );
        int colStart  = Math.max( x - 1, 0   );
        int colFinish = Math.min( x + 1, board.length - 1 );

        for ( int curRow = rowStart; curRow <= rowFinish; curRow++ ) {
            for ( int curCol = colStart; curCol <= colFinish; curCol++ ) {
                if (board[curRow][curCol] != null){
                    if ( isCallience != board[curRow][curCol].isCallience ) {
                        board[curRow][curCol].currentHP -= board[y][x].ap;
                    }
                }
            }
        }
    }


    void Heal(Token[][] board){
        int rowStart  = Math.max( y - 1, 0   );
        int rowFinish = Math.min( y + 1, board.length - 1 );
        int colStart  = Math.max( x - 1, 0   );
        int colFinish = Math.min( x + 1, board.length - 1 );

        for ( int curRow = rowStart; curRow <= rowFinish; curRow++ ) {
            for ( int curCol = colStart; curCol <= colFinish; curCol++ ) {
                if (board[curRow][curCol] != null){
                    if ( isCallience == board[curRow][curCol].isCallience ) {
                        board[curRow][curCol].currentHP += board[y][x].healPoint;
                    }
                }
            }
        }
    }


    void RangedAttack(Token[][] board){
        int rowStart  = Math.max( y - 2, 0   );
        int rowFinish = Math.min( y + 2, board.length - 1 );
        int colStart  = Math.max( x - 2, 0   );
        int colFinish = Math.min( x + 2, board.length - 1 );

        for ( int curRow = rowStart; curRow <= rowFinish; curRow++ ) {
            for ( int curCol = colStart; curCol <= colFinish; curCol++ ) {
                if (board[curRow][curCol] != null){
                    if ( isCallience != board[curRow][curCol].isCallience ) {
                        board[curRow][curCol].currentHP -= board[y][x].rangedAP;
                    }
                }
            }
        }
    }
}


class Ork extends Token {
    Ork (String name, int x, int y){
        super(name);
        this.x = x;
        this.y = y;
        this.ap = Constants.orkAP;
        this.maxHP = Constants.orkMaxHp;
        this.currentHP = Constants.orkMaxHp;
        this.maxMove = Constants.orkMaxMove;
        this.healPoint = Constants.orkHealPoints;
        this.isCallience = false;
        this.hasHeal = true;
        this.hasMoveAttack = false;
        this.hasRangedAttack = false;
    }
}


class Troll extends Token {
    Troll (String name, int x, int y){
        super(name);
        this.x = x;
        this.y = y;
        this.ap = Constants.trollAP;
        this.maxHP = Constants.trollMaxHp;
        this.currentHP = Constants.trollMaxHp;
        this.maxMove = Constants.trollMaxMove;
        this.isCallience = false;
        this.hasHeal = false;
        this.hasMoveAttack = false;
        this.hasRangedAttack = false;
    }
}


class Goblin extends Token {
    Goblin (String name, int x, int y){
        super(name);
        this.x = x;
        this.y = y;
        this.ap = Constants.goblinAP;
        this.maxHP = Constants.goblinMaxHp;
        this.currentHP = Constants.goblinMaxHp;
        this.maxMove = Constants.goblinMaxMove;
        this.isCallience = false;
        this.hasHeal = false;
        this.hasMoveAttack = true;
        this.hasRangedAttack = false;
    }
}


class Human extends Token {
    Human (String name, int x, int y){
        super(name);
        this.x = x;
        this.y = y;
        this.ap = Constants.humanAP;
        this.maxHP = Constants.humanMaxHp;
        this.currentHP = Constants.humanMaxHp;
        this.maxMove = Constants.humanMaxMove;
        this.isCallience = true;
        this.hasHeal = false;
        this.hasMoveAttack = false;
        this.hasRangedAttack = false;
    }
}


class Elf extends Token {
    Elf (String name, int x, int y){
        super(name);
        this.x = x;
        this.y = y;
        this.ap = Constants.elfAP;
        this.maxHP = Constants.elfMaxHp;
        this.currentHP = Constants.elfMaxHp;
        this.maxMove = Constants.elfMaxMove;
        this.rangedAP = Constants.elfRangedAP;
        this.isCallience = true;
        this.hasHeal = false;
        this.hasMoveAttack = true;
        this.hasRangedAttack = true;
    }
}


class Dwarf extends Token {
    Dwarf (String name, int x, int y){
        super(name);
        this.x = x;
        this.y = y;
        this.ap = Constants.dwarfAP;
        this.maxHP = Constants.dwarfMaxHp;
        this.currentHP = Constants.dwarfMaxHp;
        this.maxMove = Constants.dwarfMaxMove;
        this.isCallience = true;
        this.hasHeal = false;
        this.hasMoveAttack = true;
        this.hasRangedAttack = false;

    }
}


class MoveCountException extends Exception {
    MoveCountException(FileWriter outputWriter) throws IOException {
        outputWriter.write("Error : Move sequence contains wrong number of move steps. Input line ignored.\n\n");
    }
}


class MoveOutOfBoundsException extends Exception {
    MoveOutOfBoundsException(FileWriter outputWriter) throws IOException {
        outputWriter.write("Error : Game board boundaries are exceeded. Input line ignored.\n\n");
    }
}