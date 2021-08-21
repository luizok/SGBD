package trabalho_4.src;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

public class FileHandler {
    
    public static String readFile(String path) throws FileNotFoundException {
        Scanner scanner = new Scanner(new FileReader(path)).useDelimiter("\\n");

        StringBuilder builder = new StringBuilder();
        
        while (scanner.hasNext())
            builder.append(scanner.next());

        scanner.close();
        return builder.toString();
    }
}
