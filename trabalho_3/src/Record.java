package trabalho_3.src;

import java.io.InvalidClassException;
import java.util.HashMap;

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

    @Override
    public String toString() {
        
        StringBuffer buffer = new StringBuffer();

        buffer.append("<Record>\n");

        for(String fieldName : this.fields.keySet())
            buffer.append(String.format("\t %s\b value=%s>\n", this.fields.get(fieldName), this.values.get(fieldName)));

        return buffer.toString();
    }
}
