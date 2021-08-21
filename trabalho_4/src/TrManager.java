package trabalho_4.src;

import java.util.ArrayList;
import java.util.List;

public class TrManager {
    
    List<Transaction> transactions = new ArrayList<Transaction>();
    private int transactionCount = 0;

    public void newTransaction(Transaction t) {
        t.setId(this.transactionCount);
        this.transactions.add(t);
    }
}
