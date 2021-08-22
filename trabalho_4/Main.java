package trabalho_4;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import trabalho_4.src.FileHandler;
import trabalho_4.src.Item;
import trabalho_4.src.LockManager;
import trabalho_4.src.TrManager;
import trabalho_4.src.Transaction;

// javac Main.java src/*.java
// cd ..
// java trabalho_4.Main

public class Main {

    public static void main(String[] args) throws Exception {

        String cmds = FileHandler.readFile("trabalho_4/example.txt", 1);
        System.out.println(cmds);

        Pattern p = Pattern.compile("(\\w+)\\((\\w+)\\)");
        Matcher cmdsMatches = p.matcher(cmds);

        List<String> cmdsList = new ArrayList<String>();
        List<String> paramsList = new ArrayList<String>();

        while(cmdsMatches.find()) {
            cmdsList.add(cmdsMatches.group(1));
            paramsList.add(cmdsMatches.group(2));
        }

        for(int i=0; i < cmdsList.size(); i++) {

            String cmd = cmdsList.get(i);
            String param = paramsList.get(i);

            if(cmd.equals("BT")) {
                String tabs = new String("\t").repeat(Integer.valueOf(param)-1);
                System.out.println(tabs + "START " + param);
            }
            else if(cmd.equals("C")) {
                int tId = Integer.valueOf(param);
                String tabs = new String("\t").repeat(Integer.valueOf(param)-1);
                System.out.println(tabs + "END " + param);
            }
            else if(cmd.substring(0, 1).equals("r")) {
                int tId = Integer.valueOf(cmd.substring(1));
                String tabs = new String("\t").repeat(tId-1);

                System.out.println(tabs + "R(" + param + ")");
            }
            else if(cmd.substring(0, 1).equals("w")) {
                int tId = Integer.valueOf(cmd.substring(1));
                String tabs = new String("\t").repeat(tId-1);

                System.out.println(tabs + "W(" + param + ")");
            }
        }

        TrManager tManager = new TrManager();
        LockManager lManager = new LockManager();

        for(int i=0; i < cmdsList.size(); i++) {

            String cmd = cmdsList.get(i);
            String param = paramsList.get(i);

            System.out.println(String.format("----------------------%s(%s)---------------------", cmd, param));

            if(cmd.equals("BT")) {
                lManager.newTransaction(new Transaction(Integer.valueOf(param)));
            }
            else if(cmd.equals("C")) {
                lManager.unlock(new Transaction(Integer.valueOf(param)));
            }
            else if(cmd.substring(0, 1).equals("r")) {
                int tId = Integer.valueOf(cmd.substring(1));
                lManager.lockShared(new Transaction(tId), new Item(param));
            }
            else if(cmd.substring(0, 1).equals("w")) {
                int tId = Integer.valueOf(cmd.substring(1));
                lManager.lockExclusive(new Transaction(tId), new Item(param));
            }

            System.out.print(lManager);
            System.out.println("------------------------------------------------");
        }
        // System.out.print("\n");

        // System.out.print(lManager);
    }
}
