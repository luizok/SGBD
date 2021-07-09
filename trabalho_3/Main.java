package trabalho_3;

import java.time.Instant;
import java.util.Date;

import trabalho_3.src.*;
import trabalho_3.src.Record;

// javac Main.java src/*.java
// cd ..
// java trabalho_3.Main

public class Main {

    public static void main(String[] args) throws Exception {

        Main.runTests();
    }

    public static void runTests() throws Exception {

        Record r1 = new Record(
            new Attribute("nome", String.class),
            new Attribute("idade", Integer.class),
            new Attribute("dataNasc", Date.class)
        );

        Record r2 = new Record(
            new Attribute("nome", String.class),
            new Attribute("idade", Integer.class),
            new Attribute("dataNasc", Date.class)
        );

        r1.setField("nome", "Luiz Felipe");
        r1.setField("idade", 23);
        r1.setField("dataNasc", Date.from(Instant.parse("1998-06-24T00:00:00.00Z")));

        r2.setField("nome", "Zé Vilásio");
        r2.setField("idade", 17);
        r2.setField("dataNasc", Date.from(Instant.parse("2004-01-23T00:00:00.00Z")));

        System.out.println(r1);
        System.out.println(r2);
    }
}