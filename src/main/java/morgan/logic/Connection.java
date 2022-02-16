package morgan.logic;

import io.netty.channel.Channel;
import morgan.connection.AbstractConnection;
import morgan.messages.CSLogin;
import morgan.messages.SCLogin;
import morgan.structure.Node;
import morgan.structure.serialize.InputStream;
import morgan.support.Log;
import morgan.support.Utils;
import morgan.support.functions.Function2;

import java.util.concurrent.atomic.AtomicInteger;

public class Connection extends AbstractConnection {

    public static final int CONNECTION_STATE_WAITING = 0;
    public static final int CONNECTION_STATE_GAMING = 1;

    private int _playerId;
    private int _state;   //0: in lobby 1: in game
    private int _sessionId;    //lobbyId or gamesessionId

    private static final AtomicInteger idMalloc = new AtomicInteger();

    public Connection(Node node, Channel channel, int id) {
        super(node, channel, id);

        _started = true;
    }

    protected void handleMsg(byte[] buf) {
        byte[] msgBuf = new byte[buf.length - 4];
        System.arraycopy(buf, 4, msgBuf, 0, buf.length - 4);

        int msgId = Utils.bytesToInt(new byte[]{msgBuf[1], msgBuf[2], msgBuf[3], msgBuf[4]});

        //randomly distrbute to a lobby
        if (msgId == 1001) {
            InputStream in = new InputStream(msgBuf);
            CSLogin loginMsg = in.read();
            _playerId = idMalloc.incrementAndGet();
            if (loginMsg.isShooter && _playerId % 2 != 0) {
                //shooter's id should be even
                _playerId = idMalloc.incrementAndGet();
            }
            PlayerInfo p = new PlayerInfo(_playerId, _connId, _node.getName(), "player" + _playerId, loginMsg.isShooter);

            GlobalPlayerManager.playerLogin_(p);

            SCLogin m = new SCLogin();
            m.playerId = _playerId;
            sendMsg(m);

            return;
        }

        if (_state == CONNECTION_STATE_WAITING) {
            Lobby.handleLobbyMsg_(_playerId, msgBuf);
        } else if (_state == CONNECTION_STATE_GAMING) {
            Game.handleGameMsg_(_sessionId, _playerId, msgBuf);
        }
    }

    public void changeState(int state, int sessionId){
        _state = state;
        _sessionId = sessionId;
    }

    public static void changeState_(int workerId, int state, int sessionId) {
        CallWithStack0(workerId, state, sessionId);
    }

    protected void onConnectionClosedOverride() {
		this.schedule(100, () -> {
			if (_state == 0)
				Lobby.playerLogOut_(_playerId);
			else
				Game.removePlayer_(_sessionId, _playerId, true);
		});
		Log.connection.info("connection closed! playerId:{}, connId:{}", _playerId, _connId);
	}

    @Override
    public void registMethods() {
    	super.registMethods();
        _rpcMethodManager.registMethod("changeState", (Function2<Integer, Integer>)this::changeState, int.class, int.class);
    }
}
