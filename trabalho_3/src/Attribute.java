package trabalho_3.src;

public class Attribute {
    
    private String name;
    private Class<?> type;

    public Attribute(String name, Class<?> type) {
        this.name = name;
        this.type = type;
    }

    public String getName() { return this.name; }
    public Class<?> getType() { return this.type; }

    @Override
    public String toString() {
        
        StringBuffer buffer = new StringBuffer();

        buffer.append(String.format("<Attribute name=%s, type=%s>", this.name, this.type.getName()));

        return buffer.toString();
    }
}
