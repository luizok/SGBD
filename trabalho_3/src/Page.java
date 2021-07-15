package trabalho_3.src;

import java.util.ArrayList;

public class Page extends ArrayList<Record> {
    
    private int nRecords;


    public Page(int nRecords) {
        super(nRecords);
        this.nRecords = nRecords;
    }

    public int getNRecords() { return this.nRecords; }

    @Override
    public boolean add(Record e) {
        
        if(this.size() + 1 > nRecords)
            return false;

        return super.add(e);
    }
}
