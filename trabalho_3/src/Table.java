package trabalho_3.src;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;

public class Table {
    
    private static int nRecsPerPages = 2;
    private String name;
    private List<Attribute> schema;
    List<Page> pages = new ArrayList<Page>();

    public Table(String name, List<Attribute> schema) {
        this.name = name;
        this.schema = schema;

        pages.add(new Page(Table.nRecsPerPages));
    }

    public boolean insert(Record r) {

        boolean wasInserted = false;
        Iterator<Page> iterPages = this.pages.iterator();

        while(iterPages.hasNext())
            if(iterPages.next().add(r)) {
                wasInserted = true;
                break;
            }

        if(!wasInserted) {
            Page newPage = new Page(Table.nRecsPerPages);
            newPage.add(r);
            this.pages.add(newPage);
        }

        return true;
    }

    public String getName() { return this.name; }
    public List<Attribute> getSchema() { return this.schema; }
    public void sortBy(String fieldName) {

        List<Record> recordsChunk = new ArrayList<Record>();

        for(Page p : this.pages)
            recordsChunk.addAll(p);

        recordsChunk.sort(new Comparator<Record>(){
           public int compare(Record r1, Record r2) {
                
                return r1.compareTo(r2);
            }
        });
    }

    @Override
    public String toString() {
        
        StringBuffer buffer = new StringBuffer();

        buffer.append(String.format(
            "<Table name=%s nPages=%s nRecsPerPages=%d>",
            this.name, this.pages.size(), this.pages.get(0).getNRecords()
        ));
        
        int i = 0;
        for(Page p : this.pages) {
            buffer.append(String.format(
                "\n\t<Page idx=%d records=%d/%d>",
                i, p.size(), p.getNRecords()
            ));

            for(Record r : p) {
                buffer.append(String.format("\n\t\t%s", r));
            }
        }


        return buffer.toString();
    }
}
