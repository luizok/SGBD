package trabalho_4.src.entries;

import trabalho_4.src.Item;
import trabalho_4.src.enums.LockEnum;

public class LockTableEntry {
   
    private Item it;
    private LockEnum lockType;
    private int trId;

    public LockTableEntry(Item it, LockEnum lockType, int trId) {
        this.it = it;
        this.lockType = lockType;
        this.trId = trId;
    }

    public Item getItem() {
        return it;
    }

    public LockEnum getLockType() {
        return lockType;
    }

    public int getTrId() {
        return trId;
    }

    @Override
    public String toString() {

        StringBuilder builder = new StringBuilder();

        builder.append(String.format("<Item=%s, lock=%s, trId=%d>", this.it, this.lockType, this.trId));

        return builder.toString();
    }
}
