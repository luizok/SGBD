package trabalho_4.src;

import java.util.ArrayList;
import java.util.List;

import trabalho_4.src.entries.LockTableEntry;
import trabalho_4.src.entries.WaitQueueEntry;
import trabalho_4.src.enums.LockEnum;

public class LockManager {
    
    List<LockTableEntry> lockTable = new ArrayList<LockTableEntry>();
    List<WaitQueueEntry> waitQueue = new ArrayList<WaitQueueEntry>();

    private boolean canLock(Transaction tr, Item d) {

        for(WaitQueueEntry wqe : this.waitQueue)
            continue;

        return true;
    }

    public void lockShared(Transaction tr, Item d) { // LS(Tr, D)

        if(this.canLock(tr, d)) {
            this.lockTable.add(new LockTableEntry(d, LockEnum.SHARED, tr.getId()));
        }
    }

    public void lockExclusive(Transaction tr, Item d) { // LX(Tr, D)

        if(this.canLock(tr, d)) {
            this.lockTable.add(new LockTableEntry(d, LockEnum.EXCLUSIVE, tr.getId()));
        }
    }

    public void unlock(Transaction tr, Item d) { // U(Tr, D)

    }

    @Override
    public String toString() {

        StringBuilder builder = new StringBuilder();
        builder.append("Lock Table\n");
        for(LockTableEntry lte : this.lockTable)
            builder.append(lte.toString() + "\n");

        builder.append("\nWaitQueue");
        for(WaitQueueEntry wqe : this.waitQueue)
            builder.append(wqe.toString());

        builder.append("\n");

        return builder.toString();
    }
}
