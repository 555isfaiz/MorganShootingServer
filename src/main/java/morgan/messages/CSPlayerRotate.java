package morgan.messages;

import morgan.structure.serialize.InputStream;
import morgan.structure.serialize.OutputStream;



public class CSPlayerRotate extends MessageBase {
    public int playerId;
    public BVector4 rotation;
    public long timeStamp;


    public CSPlayerRotate() {
        msgId = 2008;
    }

    @Override
    public void writeOut(OutputStream out) {
        out.write(playerId);
        out.write(rotation);
        out.write(timeStamp);

    }

    @Override
    public void readIn(InputStream in) {
        playerId = in.read();
        rotation = in.read();
        timeStamp = in.read();

    }
}