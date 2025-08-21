import java.util.ArrayList;

public class Stack extends ArrayList {
    ArrayList<Item> items = new ArrayList<>();
    String name;

    Stack(String name){
        this.name = name;
    }

    public Item pop() {
        if (items.isEmpty()) {
            return null;
        }
        Item top = items.get(items.size() - 1);
        items.remove(items.size() - 1);
        return top;
    }

    public void push(String id, String name) {
        Item item = new Item(id, name);
        items.add(item);
    }

    public int size() {
        return items.size();
    }

    public boolean isEmpty() {
        return items.isEmpty();
    }
}
