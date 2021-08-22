package trabalho_4.src;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

public class FileHandler {
    
    public static String readFile(String path, int line) throws FileNotFoundException {
        Scanner scanner = new Scanner(new FileReader(path)).useDelimiter("\\n");

        StringBuilder builder = new StringBuilder();
        
        int i = 0;
        while (scanner.hasNext()) {
            if(i == line) {
                builder.append(scanner.next());
                break;
            }

            scanner.next();
            i++;
        }

        scanner.close();
        return builder.toString();
    }
}
