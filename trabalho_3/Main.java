package trabalho_3;

import java.time.Instant;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import trabalho_3.src.*;
import trabalho_3.src.Record;

// javac Main.java src/*.java
// cd ..
// java trabalho_3.Main

public class Main {

    public static void main(String[] args) throws Exception {


        // Main.runTests();
        // Main.joinTest();
        Main.runMain();

    }

    public static void joinTest() throws Exception {
        List<Attribute> blueSchema = new ArrayList<Attribute>(List.of(
            new Attribute("sid", Integer.class),
            new Attribute("sname", String.class)
        ));
        Table blue = Table.buildFromFile("trabalho_3/src/tblBlue.txt", -1, "Blue", blueSchema);

        List<Attribute> redSchema = new ArrayList<Attribute>(List.of(
            new Attribute("sid_", Integer.class),
            new Attribute("bid", Integer.class)
        ));
        Table red = Table.buildFromFile("trabalho_3/src/tblRed.txt", -1, "Red", redSchema);

        System.out.println(blue);
        System.out.println("\n");
        System.out.println(red);
        System.out.println("\n");

        // for(int i=0; i < red.getTotalRecords(); i++) {
        //     System.out.println("REC:" + red.getRecord(i));
        // }

        Table join = Joiner.sortMergeJoin(blue, red, "sid", "sid_");


        System.out.println(join);
        System.out.println("\n");
    }

    public static void runMain() throws Exception {

        List<Attribute> funcSchema = new ArrayList<Attribute>(List.of(
            new Attribute("id", Integer.class),
            new Attribute("Nome", String.class),
            new Attribute("Sobrenome", String.class),
            new Attribute("Idade", Integer.class)
        ));
        Table funcTable = Table.buildFromFile("/home/luizok/Downloads/data_Funcionario.txt", -1, "Funcionario", funcSchema);

        List<Attribute> vendasSchema = new ArrayList<Attribute>(List.of(
            new Attribute("idVenda", Integer.class),
            new Attribute("idFunc", Integer.class),
            new Attribute("Nome", String.class),
            new Attribute("Quantidade", Integer.class)
        ));
        Table vendasTable = Table.buildFromFile("/home/luizok/Downloads/data_Venda.txt", -1, "Vendas", vendasSchema);

        System.out.println(funcTable);
        System.out.println("\n");
        System.out.println(vendasTable);

        Table joinedTable = Joiner.sortMergeJoin(funcTable, vendasTable, "id", "idFunc");
        System.out.println("--------------------------------------------");
        System.out.println(joinedTable);
        System.out.println("A tabela entrechechada tem " + joinedTable.getTotalRecords() + " elementos");
        joinedTable.toCSV("trabalho_3/joined.txt");
    }

    public static void runTests() throws Exception {

        Record r1 = new Record(List.of(
            new Attribute("nome", String.class),
            new Attribute("idade", Integer.class),
            new Attribute("dataNasc", Date.class)
        ));

        Record r2 = new Record(List.of(
            new Attribute("nome", String.class),
            new Attribute("idade", Integer.class),
            new Attribute("dataNasc", Date.class)
        ));
            
        Record r3 = new Record(List.of(
            new Attribute("nome", String.class),
            new Attribute("idade", Integer.class),
            new Attribute("dataNasc", Date.class)
        ));

        r1.setField("nome", "Luiz Felipe");
        r1.setField("idade", 23);
        r1.setField("dataNasc", Date.from(Instant.parse("1998-06-24T00:00:00.00Z")));

        r2.setField("nome", "Zé Vilásio");
        r2.setField("idade", 17);
        r2.setField("dataNasc", Date.from(Instant.parse("2004-01-23T00:00:00.00Z")));

        r3.setField("nome", "Creuza");
        r3.setField("idade", 174);
        r3.setField("dataNasc", Date.from(Instant.parse("1967-12-12T00:00:00.00Z")));

        System.out.println(r1);
        System.out.println(r2);

        Table t = new Table("Pessoas", new ArrayList<Attribute>(List.of(
            new Attribute("nome", String.class),
            new Attribute("idade", Integer.class),
            new Attribute("dataNasc", Date.class)
        )));
        
        t.insert(r1);
        t.insert(r2);
        t.insert(r3);

        Table tSorted = t.sortBy("idade");

        System.out.println(t);
        System.out.println("\n");
        System.out.println(tSorted);

        while(t.hasNext()) {
            System.out.println("R = " + t.next());
        }
    }
}