package trabalho_3.src;

import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;

public class Table implements Iterator<Record> {
    
    private static int nRecsPerPages = 16;
    private String name;
    private List<Attribute> schema;
    List<Page> pages = new ArrayList<Page>();
    private int totalRecords = 0;

    private int currPageIdx = 0;
    private int currRecordIdx = 0; 

    public static Table buildFromFile(String path, int nRows, String tblName, List<Attribute> schema) throws FileNotFoundException {

        List<String> rows = FileHandler.readFile(path, nRows);
        Table t = new Table(tblName, schema);

        List<String> fieldOrder = new ArrayList<String>();
        for(Attribute attr : schema)
            fieldOrder.add(attr.getName());

        for(String row : rows) {
            Record record = new Record(schema);
            record.fromRow(row, fieldOrder);
            t.insert(record);
        }

        return t;
    }

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

        this.totalRecords++;

        return true;
    }

    public int getTotalRecords() {

        return this.totalRecords;
    }

    public Record getRecord(int i) {

        Page p = this.pages.get(i / Table.nRecsPerPages);

        return p.get(i % p.getNRecords());
    }

    @Override
    public boolean hasNext() {

        try {
            this.pages.get(currPageIdx).get(currRecordIdx);
            return true;
        } catch(IndexOutOfBoundsException e) {
            this.currPageIdx = 0;
            this.currRecordIdx = 0;
            return false;
        }
    }

    @Override
    public Record next() {

        Record rec = this.pages.get(currPageIdx).get(currRecordIdx);

        int prevRecordIdx = this.currRecordIdx;
        this.currRecordIdx = (this.currRecordIdx + 1) % this.pages.get(this.currPageIdx).size();
        this.currPageIdx += prevRecordIdx + 1 == this.pages.get(this.currPageIdx).size() ? 1 : 0;

        return rec;
    }

    public void resetIter() {
        this.currPageIdx = 0;
        this.currRecordIdx = 0;
    }

    public String getName() { return this.name; }
    public List<Attribute> getSchema() { return this.schema; }
    public Table sortBy(String fieldName) {

        Table sortedTable = new Table(this.getName(), this.getSchema());
        List<Record> recordsChunk = new ArrayList<Record>();

        for(Page p : this.pages)
            recordsChunk.addAll(p);

        recordsChunk.sort(new Comparator<Record>(){
           public int compare(Record r1, Record r2) {
                
                return r1.compareTo(r2, fieldName);
            }
        });

        for(Record r : recordsChunk)
            sortedTable.insert(r);

        return sortedTable;
    }

    public void toCSV(String path) throws Exception {

        BufferedWriter writer = new BufferedWriter(new FileWriter(path));
        StringBuffer buffer = new StringBuffer();

        for(Page p : this.pages) {
            for(Record r : p) {
                for(Object val : r.getAllFieldValues())
                    buffer.append(val.toString() + ",");
                
                    buffer.deleteCharAt(buffer.length()-1);
                buffer.append("\r\n");
            }
        }

        writer.write(buffer.toString());

        writer.close();
    }

    @Override
    public String toString() {
        
        StringBuffer buffer = new StringBuffer();

        buffer.append(String.format(
            "<Table name=%s totalRecs=%d nPages=%s nRecsPerPages=%d>",
            this.name, this.totalRecords, this.pages.size(), this.pages.get(0).getNRecords()
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
            i++;
        }

        return buffer.toString();
    }
}
