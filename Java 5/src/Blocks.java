import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Blocks {
    public static void PartsBlock(ArrayList<Stack> vendingMachine, String partsTxt){
        File partsFile = new File(partsTxt);
        Scanner partsReader = null;
        try {
            partsReader = new Scanner(partsFile);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        while (true) {
            assert partsReader != null;
            if (!partsReader.hasNextLine()) break;
            String partsData = partsReader.nextLine();
            if (!partsData.equals("")) {
                vendingMachine.add(new Stack(partsData));
            }
        }
        partsReader.close();
    }


    public static void ItemsBlock(ArrayList<Stack> vendingMachine, String itemsTxt){
        File itemsFile = new File(itemsTxt);
        Scanner itemsReader = null;
        try {
            itemsReader = new Scanner(itemsFile);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        while (true) {
            assert itemsReader != null;
            if (!itemsReader.hasNextLine()) break;
            String[] itemsData = itemsReader.nextLine().split(" ");
            for (Stack parts : vendingMachine){
                if(itemsData[1].equals(parts.name)){
                    parts.push(itemsData[0], itemsData[1]);
                }
            }
        }
        itemsReader.close();
    }


    public static void TokensBlock(Queue tokens, int addOrder, String tokensTxt){
        File tokensFile = new File(tokensTxt);
        Scanner tokensReader = null;
        try {
            tokensReader = new Scanner(tokensFile);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        while (true){
            assert tokensReader != null;
            if (!tokensReader.hasNextLine()) break;
            String[] tokensData = tokensReader.nextLine().split(" ");
            tokens.enqueue(tokensData[0], tokensData[1], Integer.parseInt(tokensData[2]), addOrder);
            addOrder++;
        }
        tokensReader.close();
    }


    public static void TasksBlock(ArrayList<Stack> vendingMachine, Queue tokens, Queue temp, int addOrder, String tasksTxt){
        File tasksFile = new File(tasksTxt);
        Scanner tasksReader = null;
        try {
            tasksReader = new Scanner(tasksFile);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        while (true){
            assert tasksReader != null;
            if (!tasksReader.hasNextLine()) break;
            String[] tasksData = tasksReader.nextLine().split("\t");
            if (tasksData[0].equals("PUT")){
                for(String task : tasksData){
                    String[] taskParts = task.split(",");
                    for (Stack parts : vendingMachine){
                        if(taskParts[0].equals(parts.name)){
                            for (int i = 1; i < taskParts.length ;i++){
                                parts.push(taskParts[i], taskParts[0]);
                            }
                        }
                    }
                }
            }else if (tasksData[0].equals("BUY")) {
                for(String task : tasksData) {
                    String[] taskParts = task.split(",");
                    Token lastToken = null;
                    for (Stack parts : vendingMachine){
                        if(taskParts[0].equals(parts.name)){
                            for (int i = 0; i < Integer.parseInt(taskParts[1]) ;i++){
                                parts.pop();
                            }
                            int buyCount = Integer.parseInt(taskParts[1]);
                            OUTER_LOOP: while (buyCount > 0) {

                                for (int i=0; i < tokens.size(); i++){
                                    Token tempToken = tokens.dequeue();
                                    if (tempToken.type.equals(taskParts[0])){
                                        if (tempToken.amount > buyCount){
                                            tempToken.amount = tempToken.amount - buyCount;
                                            lastToken = tempToken;
                                            break OUTER_LOOP;
                                        } else if (tempToken.amount == buyCount){
                                            break OUTER_LOOP;
                                        } else if (tempToken.amount < buyCount){
                                            buyCount = buyCount - tempToken.amount;
                                        } else {
                                            temp.enqueue(tempToken.name, tempToken.type, tempToken.amount, tempToken.addOrder);
                                        }
                                    } else {
                                        temp.enqueue(tempToken.name, tempToken.type, tempToken.amount, tempToken.addOrder);
                                    }
                                }
                            }
                            int tokensSize = tokens.size();
                            for (int i=0; i < tokensSize; i++){
                                Token tempaddToken = tokens.dequeue();
                                temp.enqueue(tempaddToken.name, tempaddToken.type, tempaddToken.amount, tempaddToken.addOrder);
                            }
                            int tempSize = temp.size();
                            for (int i=0; i < tempSize; i++){
                                Token addToken = temp.dequeue();
                                tokens.enqueue(addToken.name, addToken.type, addToken.amount, addToken.addOrder);
                            }
                            if (lastToken != null){
                                tokens.enqueue(lastToken.name, lastToken.type, lastToken.amount, addOrder);
                                addOrder++;
                            }
                        }
                    }
                }
            }
        }
        tasksReader.close();
    }


    public static void PrintBlock(ArrayList<Stack> vendingMachine, Queue tokens, String outputTxt) throws IOException {
        FileWriter printWriter = new FileWriter(outputTxt);
        for (Stack stack : vendingMachine){
            printWriter.write(stack.name + ":\n");
            if(!stack.isEmpty()){
                int itemRepeat = stack.size();
                for (int i = 0; i < itemRepeat; i++){
                    Item printItem = stack.pop();
                    printWriter.write(printItem.id + "\n");
                }
            }else{
                printWriter.write(" \n");
            }
            printWriter.write("---------------\n");
        }
        printWriter.write("Token Box:\n");
        tokens.sort();
        if(!tokens.isEmpty()){
            int tokenRepeat = tokens.size();
            for (int i = 0; i < tokenRepeat; i++){
                Token printToken= tokens.dequeue();
                printWriter.write(printToken.name + " " + printToken.type + " " + printToken.amount + "\n");
            }
        }else{
            printWriter.write(" \n");
        }
        printWriter.close();}
}
