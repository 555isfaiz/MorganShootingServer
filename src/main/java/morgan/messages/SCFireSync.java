package morgan.messages;

import morgan.structure.serialize.InputStream;
import morgan.structure.serialize.OutputStream;



public class SCFireSync extends MessageBase {
    public boolean isFire1;
    public boolean isFire2;
    public BVector3 direction;
    public int f1Ammo;
    public int f2Ammo;
    public long timeStamp;


    public SCFireSync() {
        msgId = 3002;
    }

    @Override
    public void writeOut(OutputStream out) {
        out.write(isFire1);
        out.write(isFire2);
        out.write(direction);
        out.write(f1Ammo);
        out.write(f2Ammo);
        out.write(timeStamp);

    }

    @Override
    public void readIn(InputStream in) {
        isFire1 = in.read();
        isFire2 = in.read();
        direction = in.read();
        f1Ammo = in.read();
        f2Ammo = in.read();
        timeStamp = in.read();

    }
}