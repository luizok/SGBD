package trabalho_4.src.entries;

import trabalho_4.src.Transaction;
import trabalho_4.src.enums.LockEnum;

public class WaitQueueEntry {
    
    private Transaction transaction;
    private LockEnum lockType;

    public WaitQueueEntry(Transaction t, LockEnum lockType) {
        this.transaction = t;
        this.lockType = lockType;
    }

    public LockEnum getLockType() {
        return lockType;
    }

    public Transaction getTransaction() {
        return transaction;
    }

    @Override
    public String toString() {

        StringBuilder builder = new StringBuilder();

        builder.append(String.format("<trId=%d, lock=%s>", this.transaction.getId(), this.lockType));

        return builder.toString();
    }
}
