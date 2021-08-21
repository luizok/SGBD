package trabalho_4.src.entries;

import trabalho_4.src.Item;
import trabalho_4.src.enums.LockEnum;

public class WaitQueueEntry {
    
    private Item it;
    private LockEnum lockType;

    public WaitQueueEntry(Item it, LockEnum lockType) {
        this.it = it;
        this.lockType = lockType;
    }
}
