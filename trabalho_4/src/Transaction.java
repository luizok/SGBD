package trabalho_4.src;

import java.sql.Timestamp;

import trabalho_4.src.enums.StateEnum;

public class Transaction {
    
    private int id;
    private Timestamp ts;
    private StateEnum currentState;

    public Transaction() {
        this.id = -1;
        this.ts = new Timestamp(System.currentTimeMillis());
        this.currentState = StateEnum.ACTIVE;
    }

    public Transaction(int id) {
        this.id = id;
        this.ts = new Timestamp(System.currentTimeMillis());
        this.currentState = StateEnum.ACTIVE;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Timestamp getTs() {
        return ts;
    }

    public StateEnum getCurrentState() {
        return currentState;
    }

    public void setCurrentState(StateEnum currentState) {
        this.currentState = currentState;
    }

    @Override
    public String toString() {

        StringBuilder builder = new StringBuilder();

        builder.append(String.format("<trId=%d, time=%s, state=%s>", this.id, this.ts, this.currentState));

        return builder.toString();
    }
}
