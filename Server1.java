package server1;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server1 {
	public static void main(String[] args) {
		ServerSocket ss = null;
		ClientThread clientThread = new ClientThread();
		try {
			ss = new ServerSocket(7777);
			clientThread.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
         
        System.out.println("服务器开启啦");
 
        // 监听端口号：7777
        // 等待客户连接 accept()
        while (true) {
            // 开始接收客户端的连接
            try {
            	Socket so = ss.accept();
            	if(so == null) {
            		continue;
            	}
            	System.out.println("有新客户连接~");
            	clientThread.addClient(so);
            }catch(IOException e) {
            	e.printStackTrace();
            }
        }
    }
}

