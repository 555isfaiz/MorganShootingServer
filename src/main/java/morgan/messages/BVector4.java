package morgan.messages;

import morgan.structure.serialize.InputStream;
import morgan.structure.serialize.OutputStream;



public class BVector4 extends MessageBase {
    public float x;
    public float y;
    public float z;
    public float w;


    public BVector4() {
        msgId = 104;
    }

    @Override
    public void writeOut(OutputStream out) {
        out.write(x);
        out.write(y);
        out.write(z);
        out.write(w);

    }

    @Override
    public void readIn(InputStream in) {
        x = in.read();
        y = in.read();
        z = in.read();
        w = in.read();

    }
}