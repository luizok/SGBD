package trabalho_4.src;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import trabalho_4.src.enums.StateEnum;

public class TrManager {
    
    Map<Transaction, Set<Transaction>> dependencies = new HashMap<Transaction, Set<Transaction>>();
    private int transactionCount = 0;

    public void addNode(Transaction t) {
        this.dependencies.put(t, new HashSet<Transaction>());
        this.transactionCount++;
    }

    public void addEdge(Transaction from, Transaction to) {

        this.dependencies.get(from).add(to);
    }

    public void removeEdge(Transaction from, Transaction to) {

        this.dependencies.get(from).remove(to);
    }

    public void updateState(Transaction tr) {

        tr.setCurrentState(StateEnum.COMMITED);

        this.dependencies.remove(tr);
        this.dependencies.put(tr, new HashSet<Transaction>());
    }

    @Override
    public String toString() {
        
        StringBuilder builder = new StringBuilder();

        builder.append("Transaction Manager\n");

        for(Transaction t : this.dependencies.keySet()) {
            builder.append(t + " -> ");
            for(Transaction dt : this.dependencies.get(t)) {
                builder.append(dt.getId() + " | ");
            }

            builder.append("\n");
        }

        builder.append("\n");

        return builder.toString();
    }
}
