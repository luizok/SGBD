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
        Main.runMain();

    }

    public static void runMain() throws Exception {
        //                                          TABELA DE FUNCIONARIO
        List<String> listFunc = FileHandler.readFile("/home/luizok/Downloads/data_Funcionario.txt", 7);
        //List<Record> listRecord = new ArrayList<Record>();
        List<String> list = new ArrayList<String>();
        list.add("id");
        list.add("Nome");
        list.add("Sobrenome");
        list.add("Idade");
        
        Table funcTable = new Table("Funcionarios", new ArrayList<Attribute>(List.of(
            new Attribute("id", Integer.class),
            new Attribute("Nome", String.class),
            new Attribute("Sobrenome", String.class),
            new Attribute("Idade", Integer.class)
        )));

        for(String row : listFunc){
            Record recordFunc = new Record(
                                            new Attribute("id", Integer.class),
                                            new Attribute("Nome", String.class),
                                            new Attribute("Sobrenome", String.class),
                                            new Attribute("Idade", Integer.class)
                                );
            recordFunc.fromRow(row, list);
            funcTable.insert(recordFunc);
        }

        //                                          TABELA DE VENDA
        List<String> listVendas = FileHandler.readFile("/home/luizok/Downloads/data_Venda.txt", 7);
        //List<Record> listRecordVenda = new ArrayList<Record>();
        List<String> listSales = new ArrayList<String>();
        listSales.add("idVenda");
        listSales.add("idFunc");
        listSales.add("Nome");
        listSales.add("Quantidade");
        
        Table vendasTable = new Table("Vendas", new ArrayList<Attribute>(List.of(
            new Attribute("idVenda", Integer.class),
            new Attribute("idFunc", Integer.class),
            new Attribute("Nome", String.class),
            new Attribute("Quantidade", Integer.class)
        )));

        for(String row : listVendas){
            Record recordVenda = new Record(
                                            new Attribute("idVenda", Integer.class),
                                            new Attribute("idFunc", Integer.class),
                                            new Attribute("Nome", String.class),
                                            new Attribute("Quantidade", Integer.class)
                                );
            recordVenda.fromRow(row, listSales);
            vendasTable.insert(recordVenda);
        }

        System.out.println(funcTable);
        System.out.println("\n");
        System.out.println(vendasTable);

        System.out.println("--------------------------------------------");
        // while(vendasTable.hasNext()) {
        //     System.out.println("VENDA: " + vendasTable.next());
        // }

        Table sortedTblFunc = funcTable.sortBy("id");
        Table sortedTblVenda = vendasTable.sortBy("idFunc");

        System.out.println(sortedTblFunc);
        System.out.println("\n");
        System.out.println(sortedTblVenda);
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
            
        Record r3 = new Record(
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