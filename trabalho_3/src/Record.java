package trabalho_3.src;

import java.io.InvalidClassException;
import java.util.HashMap;
import java.util.List;

public class Record {

    public class InvalidAttributeValueException extends Exception {};

    HashMap<String, Attribute> fields = new HashMap<String, Attribute>();
    HashMap<String, Object> values = new HashMap<String, Object>();

    public Record(Attribute... attributes) {

        for(Attribute attr : attributes) {
            this.fields.put(attr.getName(), attr);
            this.values.put(attr.getName(), null);
        }
    }

    public void fromRow(String row, List<String> fields) {

        String[] splits = row.split(",");

        for(int i=0; i < splits.length; i++)
            this.values.put(fields.get(i), splits[i]);
    }

    public void setField(String fieldName, Object value) throws
        InvalidClassException, InvalidAttributeValueException {

        try {   
            if(!this.fields.get(fieldName).getType().isInstance(value))
                throw new InvalidClassException("INVALID CASTING", "Tipo atribuído não confere com o tipo declarado");

            this.values.put(fieldName, value);

        } catch(NullPointerException e) {
            throw new InvalidAttributeValueException();
        }
    }

    public Object getFieldValue(String fieldName) {

        return this.values.get(fieldName);
    }

    public Class<?> getFieldType(String fieldName) {

        return this.fields.get(fieldName).getType();
    }

    public int compareTo(Record r, String fieldName) {
        
        Class<?> fieldType = this.getFieldType(fieldName);
        Object field1 = this.getFieldValue(fieldName);
        Object field2 = r.getFieldValue(fieldName);

        // criar um mapa para cada classe de comparadores
        return Comparator.compare(field1, field2, fieldType);
    }

    @Override
    public String toString() {
        
        StringBuffer buffer = new StringBuffer();

        buffer.append("<Record ");

        for(String fieldName : this.fields.keySet())
            buffer.append(String.format("%s=%s ", fieldName, this.values.get(fieldName)));

        buffer.append("\b>");
        return buffer.toString();
    }
}
