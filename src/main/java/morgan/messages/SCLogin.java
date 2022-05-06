package morgan.messages;

import morgan.structure.serialize.InputStream;
import morgan.structure.serialize.OutputStream;



public class SCLogin extends MessageBase {
    public int playerId;
    public long serverTimeZone;


    public SCLogin() {
        msgId = 1004;
    }

    @Override
    public void writeOut(OutputStream out) {
        out.write(playerId);
        out.write(serverTimeZone);

    }

    @Override
    public void readIn(InputStream in) {
        playerId = in.read();
        serverTimeZone = in.read();

    }
}