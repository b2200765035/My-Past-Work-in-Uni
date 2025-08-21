import java.io.*;
import java.util.*;

public class Quiz4 {
    public static void main(String[] args) throws IOException {

        // TODO: Use the first and the second command line argument (args[0] and args[1]) to read the database and the query file.
        // TODO: Your code goes here
        // TODO: Print the solution to STDOUT
        Trie trie = new Trie();

        File dbFile = new File(args[0]);
        Scanner dbSc = new Scanner(dbFile);

        int database = dbSc.nextInt();
        dbSc.nextLine();
        for(int i = 0; i < database; i++) {
            String line = dbSc.nextLine();
            String[] words = line.split("\t");
            Long weight = Long.valueOf(words[0]);
            String word = words[1].toLowerCase();
            trie.insert(word, weight);
        }

        File qFile = new File(args[1]);
        Scanner qSc = new Scanner(qFile);
        while(qSc.hasNextLine()) {
            String line = qSc.nextLine();
            String[] words = line.split("\t");
            System.out.println("Query received: \"" + words[0] + "\" with limit " + words[1] + ". Showing results:");

            if(Integer.parseInt(words[1]) == 0){
                System.out.println("No results.");
            }else{
                List<Map.Entry<String, Long>> results = trie.search(words[0], Integer.parseInt(words[1]));
                int count = Math.min(Integer.parseInt(words[1]), results.size());
                if(count == 0){
                    System.out.println("No results.");
                }else{
                    for(int i = 0; i < count; i++) {
                        System.out.println("- " + results.get(i).getValue() + " " + results.get(i).getKey());
                    }
                }

            }
        }
    }
}

class TrieNode {
    Map<Character, TrieNode> children;
    Map<String, Long> Weight;

    public TrieNode() {
        children = new HashMap<>();
        Weight = new HashMap<>();
    }
}

class Trie {
    private TrieNode root;

    public Trie() {
        root = new TrieNode();
    }

    public void insert(String word, Long weight) {
        TrieNode currentNode = root;
        for (char c : word.toCharArray()) {
            currentNode.children.putIfAbsent(c, new TrieNode());
            currentNode = currentNode.children.get(c);
            currentNode.Weight.put(word, weight);
        }
    }

    public List<Map.Entry<String, Long>> search(String prefix, int limit) {
        TrieNode currentNode = root;
        for (char c : prefix.toCharArray()) {
            if (!currentNode.children.containsKey(c)) {
                return Collections.emptyList();
            }
            currentNode = currentNode.children.get(c);
        }

        PriorityQueue<Map.Entry<String, Long>> bestSearch = new PriorityQueue<>(
                Map.Entry.comparingByValue()
        );

        for (Map.Entry<String, Long> entry : currentNode.Weight.entrySet()) {
            bestSearch.offer(entry);
            if (bestSearch.size() > limit) {
                bestSearch.poll();
            }
        }

        List<Map.Entry<String, Long>> result = new ArrayList<>();
        while (!bestSearch.isEmpty()) {
            result.add(bestSearch.poll());
        }
        Collections.reverse(result);
        return result;
    }
}
