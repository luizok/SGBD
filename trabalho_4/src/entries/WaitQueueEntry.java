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

    @Override
    public String toString() {

        StringBuilder builder = new StringBuilder();

        builder.append(String.format("<Item=%s, lock=%s>", this.it, this.lockType));

        return builder.toString();
    }
}
