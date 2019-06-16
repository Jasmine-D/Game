package server1;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import java.net.Socket;
import java.util.ArrayList;


public class ClientThread extends Thread {
	private ArrayList<Socket> clients = new ArrayList<Socket>();
	 
    // 添加客户
    public void addClient(Socket so) {
        clients.add(so);
   
        OutputStream os;
        try {
        	os = so.getOutputStream();
		
        	String send = "{\"cmd\":1}";
        	os.write(send.getBytes("UTF-8"));
        } catch (IOException e) {
        }
    }
    
    @Override
    public void run() {
    	while (true) {
    		try {
    			for (Socket so : clients) {
    				// 获取客户端发来的数据
    				InputStream is = so.getInputStream();
    				OutputStream os = so.getOutputStream();
    				int len = is.available() + 1;
    				if(len <= 0) {
    					continue;
    				}
    				byte[] buff = new byte[len];
    				is.read(buff);
 
    				String read = new String(buff);	
    				System.out.println("收到的数据" + read);
    			}
    			sleep(10);
    		} catch (IOException e) {
    		} catch (InterruptedException e) {
    		}
		}
	}
}
