import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.ArrayList;

public class ClientThread extends Thread  {
	private ArrayList<Socket> clients = new ArrayList<Socket>();

	public void addClient(Socket so) {
		clients.add(so);
		
		/* 发送登录消息 */
		OutputStream os;
		try {
			os = so.getOutputStream();
			
			/* 玩家连接上之后，就直接发送登录消息给玩家，让他登录游戏：{"cmd":1} */
			String send = "{\"cmd\":1}";
			os.write(send.getBytes("UTF-8"));
		} catch (IOException e) {
		}
	}

	@Override
	public void run() {
		while (true) {
			try {
				/* 接收客户端的数据 */
				for(Socket so : clients) {
					InputStream is = so.getInputStream();
					OutputStream os = so.getOutputStream();
					int len = is.available();
					if(len <= 0) {
						continue;
					}
					byte[] buff = new byte[len];
					is.read(buff);
					
					String read = new String(buff);	
					System.out.println("收到的数据：" + read);
					
					/* 这里得解析Json，为讲解方便，我们就写死了，认为所有消息都是cmd = 2的 */
					
					/* ---------------- 告诉客户端当前在线的玩家 --------------------- */
					StringBuffer response = new StringBuffer("{");
					response.append(getJsonValue("cmd", 2));	/* 命令码 */
					response.append("," + getJsonValue("playerNum", clients.size()));	/* 玩家总数 */
					
					int index = 0;
					response.append(",\"players\":[");	/* 玩家名字 */
					for(Socket player : clients) {
						if(index > 0) {
							response.append(",");
						}
						response.append("{" + getJsonValue("name", "player" + index) + "}");	/* 玩家名字 */
						
						index++;
					}
					response.append("]");
					response.append("}");
					
					System.out.println("response=" + response);
					
					os.write(response.toString().getBytes("UTF-8"));
					
					/* ---------------- 通知其他玩家有新玩家上线 --------------------- */
					StringBuffer notifyAllPlayer = new StringBuffer("{");
					notifyAllPlayer.append(getJsonValue("cmd", 3));	/* 命令码 */
					notifyAllPlayer.append("," + getJsonValue("newPlayerName", "player" + clients.indexOf(so)));	
					notifyAllPlayer.append("}");
					System.out.println("通知其他玩家有新玩家上线" + notifyAllPlayer);
					for(Socket player : clients) {
						if(player == so) {
							/* 新玩家自身不需要重复通知 */
							continue;
						}
						player.getOutputStream().write(notifyAllPlayer.toString().getBytes("UTF-8"));
					}
				}
				sleep(10);
			} catch (IOException e) {
			} catch (InterruptedException e) {
			}
		}
	}
	
	private String getJsonValue(String key, String value) {
		/* 看起来复杂，其实最终是这样的格式："key":"value" */
		return "\"" + key + "\":\"" + value + "\"";
	}
	private String getJsonValue(String key, int value) {
		/* 看起来复杂，其实最终是这样的格式："key":value */
		return "\"" + key + "\":" + value + "";
	}
}
