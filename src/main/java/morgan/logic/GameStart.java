package morgan.logic;

import morgan.connection.ConnStarter;
import morgan.messages.ConstMessage;
import morgan.natives.NtvManager;
import morgan.structure.Node;
import morgan.structure.Worker;
import morgan.support.ConstDistrClass;
import morgan.support.Factory;
import morgan.support.NtvFunctions;

public class GameStart {
    static {
//        System.load(System.getProperty("user.dir") + "/morgan-shooting/build/libnativeshooting.dylib");
        System.load(System.getProperty("user.dir") + "/MorganShootingServer/build/libnativeshooting.so");
    }
    public static void main(String[] args){
        Node node = new Node("morgan", "tcp://127.0.0.1:3320");
        Worker gamemanager = new GameManager(node);
        node.addWorker(gamemanager);
        Worker lobby = new Lobby(node);
        node.addWorker(lobby);
        Worker global = new GlobalPlayerManager(node);
        node.addWorker(global);
		Factory.designateConstMessage(ConstMessage.class);
		Factory.designateConstDistrClass(ConstDistrClass.class);
		Factory.designateConnectionClass(Connection.class);
        ConnStarter.startUp(node);
        NtvManager.setNtvFunctions(new NtvFunctions());
        NtvManager.loadMeshes("./objs/Player.obj");
        node.startUp();
        lobby.schedule(1000, () -> {
            System.out.println("===============================");
            System.out.println("        system started         ");
            System.out.println("===============================");
        });
    }
}
