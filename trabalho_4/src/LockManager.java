package trabalho_4.src;

import java.util.ArrayList;
import java.util.List;

import trabalho_4.src.entries.LockTableEntry;
import trabalho_4.src.entries.WaitQueueEntry;

public class LockManager {
    
    List<LockTableEntry> lockTable = new ArrayList<LockTableEntry>();
    List<WaitQueueEntry> waitQueue = new ArrayList<WaitQueueEntry>();

    public void lockShared(Transaction tr, Item d) { // LS(Tr, D)

    }

    public void lockExclusive(Transaction tr, Item d) { // LX(Tr, D)
        
    }

    public void unlock(Transaction tr, Item d) { // U(Tr, D)
        
    }
}
