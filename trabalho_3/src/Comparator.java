package trabalho_3.src;

import java.time.Instant;
import java.util.Date;

public class Comparator {
    
    public static int compare(Object o1, Object o2, Class<?> type) throws UnsupportedOperationException {

        if(type.equals(String.class))
            return ((String) o1).compareTo((String) o2);

        else if(type.equals(Date.class))
            return ((Date) o1).compareTo((Date) o2);

        else if(type.equals(Integer.class))
            return ((Integer) o1).compareTo((Integer) o2);

        throw new UnsupportedOperationException();
    }

    public static Object fromString(String str, Class<?> type) throws UnsupportedOperationException {

        if(type.equals(String.class))
            return str;

        else if(type.equals(Date.class))
            return Instant.parse(str);

        else if(type.equals(Integer.class))
            return Integer.parseInt(str);

        throw new UnsupportedOperationException();
    }
}
