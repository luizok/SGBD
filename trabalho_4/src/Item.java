package trabalho_4.src;

public class Item {
    
    private String val;

    public Item(String val) {
        this.val = val;
    }

    public String getValue() {
        return val;
    }

    @Override
    public boolean equals(Object obj) {
        
        return this.val.equals(((Item) obj).getValue());
    }

    @Override
    public int hashCode() {
        
        return this.val.hashCode();
    }

    @Override
    public String toString() {

        return this.val;
    }
}
