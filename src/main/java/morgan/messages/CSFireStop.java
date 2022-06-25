package morgan.messages;

import morgan.structure.serialize.InputStream;
import morgan.structure.serialize.OutputStream;



public class CSFireStop extends MessageBase {
    public boolean isFire1;
    public long timeStamp;


    public CSFireStop() {
        msgId = 3003;
    }

    @Override
    public void writeOut(OutputStream out) {
        out.write(isFire1);
        out.write(timeStamp);

    }

    @Override
    public void readIn(InputStream in) {
        isFire1 = in.read();
        timeStamp = in.read();

    }
}