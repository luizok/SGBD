package trabalho_3.src;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class FileHandler {
    
    public static List<String> readFile(String path, int nLines) throws FileNotFoundException{
        Scanner scanner = new Scanner(new FileReader(path)).useDelimiter("\\n");
        int lines = 0;
        List<String> list = new ArrayList<String>();
        
        if(nLines < 0){
            while (scanner.hasNext()) {
                lines++;
                //scanner.next();
                list.add(scanner.next());
            }
        }
        else{
            while (scanner.hasNext() && lines < nLines) {
                lines++;
                //scanner.next();
                list.add(scanner.next());
            }
        }
        
        System.out.println("n. de linhas: " + lines);
        scanner.close();
        return list;
        
    }
}
