package trabalho_4.src;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import trabalho_4.src.entries.LockTableEntry;
import trabalho_4.src.entries.WaitQueueEntry;
import trabalho_4.src.enums.LockEnum;

public class LockManager {
    
    List<LockTableEntry> lockTable = new ArrayList<LockTableEntry>();
    Map<Item, List<WaitQueueEntry>> waitQueues = new HashMap<Item, List<WaitQueueEntry>>();
    TrManager trManager = new TrManager();

    private void updateWaitQueue(Transaction tr, Item d, LockEnum lockType) {

        if(this.waitQueues.get(d) == null)
            this.waitQueues.put(d, new ArrayList<WaitQueueEntry>());

        this.waitQueues.get(d).add(new WaitQueueEntry(tr, lockType));
    }

    private boolean canLock(Transaction tr, Item d, LockEnum lockType) {
            
        for(LockTableEntry lte : this.lockTable)
            if(lte.getItem().equals(d) && (lockType == LockEnum.EXCLUSIVE || lte.getLockType() == LockEnum.EXCLUSIVE))
                return false;

        return true;
    }

    public void newTransaction(Transaction t) {

        this.trManager.addNode(t);
    }

    private Transaction getPrecedingTransaction(Transaction tr, Item d) {

        for(LockTableEntry lte : this.lockTable)
            if(lte.getItem().equals(d))
                return new Transaction(lte.getTrId());

        return null;
    }

    private void updateDepencyGraph(Transaction tr, Item d) {

        if((tr == null) || (d == null))
            return;

        Transaction pt = this.getPrecedingTransaction(tr, d);
        if(pt != null)
            this.trManager.addEdge(pt, tr);
    }

    public void lockShared(Transaction tr, Item d) { // LS(Tr, D)

        if(this.canLock(tr, d, LockEnum.SHARED)) {
            this.lockTable.add(new LockTableEntry(d, LockEnum.SHARED, tr.getId()));
        } else {
            this.updateDepencyGraph(tr, d);
            this.updateWaitQueue(tr, d, LockEnum.SHARED);
        }
    }

    public void lockExclusive(Transaction tr, Item d) { // LX(Tr, D)

        if(this.canLock(tr, d, LockEnum.EXCLUSIVE))
            this.lockTable.add(new LockTableEntry(d, LockEnum.EXCLUSIVE, tr.getId()));
        else {
            this.updateDepencyGraph(tr, d);
            this.updateWaitQueue(tr, d, LockEnum.EXCLUSIVE);
        }
    }

    private List<LockTableEntry> removeRelatedEntries(int transactionId) {

        List<LockTableEntry> removedElements = new ArrayList<LockTableEntry>();
        List<Integer> toBeRemoved = new ArrayList<Integer>();

        for(int i=0; i < this.lockTable.size(); i++)
            if(this.lockTable.get(i).getTrId() == transactionId) {
                removedElements.add(this.lockTable.get(i));
                toBeRemoved.add(i);
            }

        Collections.reverse(toBeRemoved);

        for(Integer idx : toBeRemoved)
            this.lockTable.remove((int) idx);

        return removedElements;
    }

    private void dequeueWaitQueue(Item it) {

        if((this.waitQueues.get(it) != null) && this.waitQueues.get(it).size() > 0)
            this.waitQueues.get(it).remove(0);

        if(this.waitQueues.get(it).size() == 0)
            this.waitQueues.remove(it);
    }

    private WaitQueueEntry getNextWaitQueueEntry(Item it) {

        // System.out.println(this.waitQueues.get(it));
        if((this.waitQueues.get(it) != null) && this.waitQueues.get(it).size() > 0)
            return this.waitQueues.get(it).get(0);

        return null;
    }

    public void unlock(Transaction tr) { // U(Tr, D)

        this.trManager.updateState(tr);

        List<LockTableEntry> removedElements = this.removeRelatedEntries(tr.getId());
        Set<Item> items = new HashSet<Item>();

        for(LockTableEntry lte : removedElements)
            items.add(lte.getItem());

        for(Item it : items) {
            WaitQueueEntry wqe = this.getNextWaitQueueEntry(it);
            if(wqe != null) {
                if(this.canLock(wqe.getTransaction(), it, wqe.getLockType())) {
                    this.lockTable.add(new LockTableEntry(
                        it,
                        wqe.getLockType(),
                        wqe.getTransaction().getId()
                    ));

                    this.dequeueWaitQueue(it);
                }
            }
        }
    }

    @Override
    public String toString() {

        StringBuilder builder = new StringBuilder();

        builder.append(this.trManager.toString());
        builder.append("Lock Table\n");
        for(LockTableEntry lte : this.lockTable)
            builder.append(lte.toString() + "\n");

        builder.append("\nWaitQueue\n");
        for(Item it : this.waitQueues.keySet()) {
            builder.append("    " + it.getValue() + " = {");
            for(WaitQueueEntry wqe : this.waitQueues.get(it))
                builder.append(String.format("[%d, %s],", wqe.getTransaction().getId(), wqe.getLockType()));
            
            builder.append("\b}\n");
        }

        builder.append("\b\n");

        return builder.toString();
    }
}
