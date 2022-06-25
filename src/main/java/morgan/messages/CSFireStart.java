package morgan.messages;

import morgan.structure.serialize.InputStream;
import morgan.structure.serialize.OutputStream;



public class CSFireStart extends MessageBase {
    public boolean isFire1;
    public BVector3 direction;
    public long timeStamp;


    public CSFireStart() {
        msgId = 3001;
    }

    @Override
    public void writeOut(OutputStream out) {
        out.write(isFire1);
        out.write(direction);
        out.write(timeStamp);

    }

    @Override
    public void readIn(InputStream in) {
        isFire1 = in.read();
        direction = in.read();
        timeStamp = in.read();

    }
}