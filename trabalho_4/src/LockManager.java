package trabalho_4.src;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import trabalho_4.src.entries.LockTableEntry;
import trabalho_4.src.entries.WaitQueueEntry;
import trabalho_4.src.enums.LockEnum;

public class LockManager {
    
    List<LockTableEntry> lockTable = new ArrayList<LockTableEntry>();
    Map<Item, List<WaitQueueEntry>> waitQueue = new HashMap<Item, List<WaitQueueEntry>>();


    private void updateWaitQueue(Transaction tr, Item d, LockEnum lockType) {

        if(this.waitQueue.get(d) == null)
            this.waitQueue.put(d, new ArrayList<WaitQueueEntry>());

        this.waitQueue.get(d).add(new WaitQueueEntry(tr, lockType));
    }

    private boolean canLock(Transaction tr, Item d, LockEnum lockType) {
            
        for(LockTableEntry lte : this.lockTable) {
            if(lte.getItem().equals(d) && (lte.getLockType() == LockEnum.EXCLUSIVE)) {
                this.updateWaitQueue(tr, d, lockType);
                return false;
            }
        }

        return true;
    }

    public void lockShared(Transaction tr, Item d) { // LS(Tr, D)

        if(this.canLock(tr, d, LockEnum.SHARED)) {
            this.lockTable.add(new LockTableEntry(d, LockEnum.SHARED, tr.getId()));
        }
    }

    public void lockExclusive(Transaction tr, Item d) { // LX(Tr, D)

        if(this.canLock(tr, d, LockEnum.EXCLUSIVE)) {
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

        builder.append("\nWaitQueue\n");
        for(Item it : this.waitQueue.keySet()) {
            builder.append("    " + it.getValue() + " = {");
            for(WaitQueueEntry wqe : this.waitQueue.get(it))
                builder.append(String.format("[%d, %s],", wqe.getTransaction().getId(), wqe.getLockType()));
            
            builder.append("\b}\n");
        }

        builder.append("\n");

        return builder.toString();
    }
}
