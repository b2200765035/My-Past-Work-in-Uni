import java.io.IOException;
import java.util.ArrayList;

//Collections.sort(tokens.tokens, Comparator.comparing(Token::getAmount));
public class Main {

    public static void main(String[] args) throws IOException {
        ArrayList<Stack> vendingMachine = new ArrayList<>();
        Queue tokens = new Queue();
        Queue temp = new Queue();
        int addOrder = 0;


        //Parts block
        Blocks.PartsBlock(vendingMachine, args[0]);


        //Items block
        Blocks.ItemsBlock(vendingMachine, args[1]);


        //Tokens block
        Blocks.TokensBlock(tokens, addOrder, args[2]);


        //Tasks block
        Blocks.TasksBlock(vendingMachine, tokens, temp, addOrder, args[3]);


        //Print block
        Blocks.PrintBlock(vendingMachine, tokens, args[4]);
    }
}


class Item {
    String id;
    String name;

    Item (String id, String name){
        this.id = id;
        this.name = name;
    }
}


class Token {
    String name;
    String type;
    int amount;
    int addOrder;

    Token(String name,  String type, int amount, int addOrder){
        this.name = name;
        this.type = type;
        this.amount = amount;
        this.addOrder = addOrder;
    }
    int getAmount(){
        return amount;
    }
    int getAddOrder(){return addOrder;}
}