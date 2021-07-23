package trabalho_3.src;

import java.util.ArrayList;
import java.util.List;

public class Joiner {
    
    public static Table sortMergeJoin(Table R, Table S, String leftField, String rightField)  throws Exception {

        List<Attribute> newSchema = new ArrayList<Attribute>();

        for(Attribute attr : R.getSchema())
            newSchema.add(new Attribute(R.getName() + '.' + attr.getName(), attr.getType()));

        for(Attribute attr : S.getSchema())
            newSchema.add(new Attribute(S.getName() + '.' + attr.getName(), attr.getType()));

        Table T = new Table(R.getName() + "_" + S.getName(),  newSchema);
        int r = 0, s = 0, mark = -1;

        R = R.sortBy(leftField);
        S = S.sortBy(rightField);

        while(r < R.getTotalRecords() && s < S.getTotalRecords()) {

            if(mark < 0) {
                while(Comparator.compare(R.getRecord(r).getFieldValue(leftField), S.getRecord(s).getFieldValue(rightField), R.getRecord(r).getFieldType(leftField)) == -1) {
                    r++;
                    if(r >= R.getTotalRecords()) return T;
                }

                while(Comparator.compare(R.getRecord(r).getFieldValue(leftField), S.getRecord(s).getFieldValue(rightField), R.getRecord(r).getFieldType(leftField)) == 1) {
                    s++;
                    if(s >= S.getTotalRecords()) return T;
                }

                mark = s;
            }

            if(Comparator.compare(R.getRecord(r).getFieldValue(leftField), S.getRecord(s).getFieldValue(rightField), R.getRecord(r).getFieldType(leftField)) == 0) {

                Record rec = new Record(newSchema);
                for(Attribute attr : R.getSchema())
                    rec.setField(R.getName() + '.' + attr.getName(), R.getRecord(r).getFieldValue(attr.getName()));
                for(Attribute attr : S.getSchema())
                    rec.setField(S.getName() + '.' + attr.getName(), S.getRecord(s).getFieldValue(attr.getName()));

                T.insert(rec);
                s++;
            } else {
                s = mark;
                r++;
                mark = -1;
            }
        }

        return T;
    }
}
