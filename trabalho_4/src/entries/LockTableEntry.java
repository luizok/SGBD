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
}
