import java.util.ArrayList;
import java.util.Comparator;


public class Queue {
    public ArrayList<Token> tokens = new ArrayList<>();


    public Token dequeue() {
        if (tokens.isEmpty()) {
            return null;
        }
        Token token = tokens.get(0);
        tokens.remove(0);
        return token;
    }

    public void enqueue(String name, String type, int amount, int addOrder) {
        Token token = new Token(name, type, amount, addOrder);
        tokens.add(token);
        tokens.sort(Comparator.comparing(Token::getAmount).thenComparing(Token::getAddOrder, Comparator.reverseOrder()).reversed());
    }

    public  void sort(){
        tokens.sort(Comparator.comparing(Token::getAmount).thenComparing(Token::getAddOrder, Comparator.reverseOrder()));
    }

    public int size() {
        return tokens.size();
    }

    public boolean isEmpty() {
        return tokens.isEmpty();
    }
}
