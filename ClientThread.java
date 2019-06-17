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
		
		/* ���͵�¼��Ϣ */
		OutputStream os;
		try {
			os = so.getOutputStream();
			
			/* ���������֮�󣬾�ֱ�ӷ��͵�¼��Ϣ����ң�������¼��Ϸ��{"cmd":1} */
			String send = "{\"cmd\":1}";
			os.write(send.getBytes("UTF-8"));
		} catch (IOException e) {
		}
	}

	@Override
	public void run() {
		while (true) {
			try {
				/* ���տͻ��˵����� */
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
					System.out.println("�յ������ݣ�" + read);
					
					/* ����ý���Json��Ϊ���ⷽ�㣬���Ǿ�д���ˣ���Ϊ������Ϣ����cmd = 2�� */
					
					/* ---------------- ���߿ͻ��˵�ǰ���ߵ���� --------------------- */
					StringBuffer response = new StringBuffer("{");
					response.append(getJsonValue("cmd", 2));	/* ������ */
					response.append("," + getJsonValue("playerNum", clients.size()));	/* ������� */
					
					int index = 0;
					response.append(",\"players\":[");	/* ������� */
					for(Socket player : clients) {
						if(index > 0) {
							response.append(",");
						}
						response.append("{" + getJsonValue("name", "player" + index) + "}");	/* ������� */
						
						index++;
					}
					response.append("]");
					response.append("}");
					
					System.out.println("response=" + response);
					
					os.write(response.toString().getBytes("UTF-8"));
					
					/* ---------------- ֪ͨ������������������ --------------------- */
					StringBuffer notifyAllPlayer = new StringBuffer("{");
					notifyAllPlayer.append(getJsonValue("cmd", 3));	/* ������ */
					notifyAllPlayer.append("," + getJsonValue("newPlayerName", "player" + clients.indexOf(so)));	
					notifyAllPlayer.append("}");
					System.out.println("֪ͨ������������������" + notifyAllPlayer);
					for(Socket player : clients) {
						if(player == so) {
							/* �����������Ҫ�ظ�֪ͨ */
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
		/* ���������ӣ���ʵ�����������ĸ�ʽ��"key":"value" */
		return "\"" + key + "\":\"" + value + "\"";
	}
	private String getJsonValue(String key, int value) {
		/* ���������ӣ���ʵ�����������ĸ�ʽ��"key":value */
		return "\"" + key + "\":" + value + "";
	}
}
