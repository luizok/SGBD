package trabalho_4;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import trabalho_4.src.FileHandler;
import trabalho_4.src.LockManager;
import trabalho_4.src.TrManager;

// javac Main.java src/*.java
// cd ..
// java trabalho_4.Main

public class Main {

    public static void main(String[] args) throws Exception {

        String cmds = FileHandler.readFile("trabalho_4/example.txt");
        System.out.println(cmds);

        Pattern p = Pattern.compile("(\\w+)\\((\\w+)\\)");
        Matcher cmdsMatches = p.matcher(cmds);

        while(cmdsMatches.find()) {
            String cmd = cmdsMatches.group(1);
            String param = cmdsMatches.group(2);
            System.out.print(String.format("%s(%s) -> ", cmd, param));
        }
        System.out.print("\n");

        TrManager tManager = new TrManager();
        LockManager lManager = new LockManager();
    }
}