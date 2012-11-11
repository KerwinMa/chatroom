package zet.chatroom;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.text.SimpleDateFormat;
import java.util.Date;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Toast;

public class ChatRoomActivity extends Activity
{
	private EditText chatlist;			//�����¼
	private EditText userlist;			//�û��б�
	private EditText message;			//��Ϣ�����
	private Button   sendBtn;			//���Ͱ�ť
	private Button 	 clearBtn;			//��������¼��ť
	private CheckBox IsPrivate;			//�Ƿ�˽��ѡ���
	private EditText toUserText;		//˽���û��������
	private Socket s;				
	private InputStream inStream;
	private OutputStream outStream;
	private RefleshHandler recvhandler = new RefleshHandler(); 
	private RecvThread recvThread = new RecvThread();
	private String ipaddr  ;      //������IP��ַ
	private String username ;     //�û���
	//private ExecutorService executorService;//�̳߳�
	
	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.roomlayout);
		
		chatlist = (EditText)findViewById(R.id.chatlist);
		userlist = (EditText)findViewById(R.id.userlist);
		message = (EditText)findViewById(R.id.messageText);
		sendBtn = (Button)findViewById(R.id.sendBtn);
		clearBtn = (Button)findViewById(R.id.clearBtn);
		IsPrivate = (CheckBox)findViewById(R.id.IsPrivate);
		toUserText = (EditText)findViewById(R.id.toUserText);
		
		sendBtn.setOnClickListener(new sendBtnListener());
		clearBtn.setOnClickListener(new clearBtnListener());
		IsPrivate.setOnCheckedChangeListener(new IsPrivateListener());
		
		//����chatlist , userlist �� toUserTextֻ��;
		chatlist.setCursorVisible(false);
		chatlist.setFocusable(false);
		chatlist.setFocusableInTouchMode(false);
		userlist.setCursorVisible(false);
		userlist.setFocusable(false);
		userlist.setFocusableInTouchMode(false);
		toUserText.setCursorVisible(false);
		toUserText.setFocusable(false);
		toUserText.setFocusableInTouchMode(false);
		
		Intent intent = this.getIntent();
		ipaddr = intent.getStringExtra("ipaddr");
		username = intent.getStringExtra("username");
		
		//ע����Ϣ
		String loginInfo = "0\n" + username + "\n" + "0\n" + "0";
		//chatlist.append("ipaddr = " + ipaddr + " username = " + username);
		
		try 
		{
			s = new Socket(ipaddr,3204);
			//s  new Socket("10.0.2.2" , 3204);         
			outStream = s.getOutputStream();
			inStream = s.getInputStream();
			//����ע����Ϣ
			outStream.write(loginInfo.getBytes("GBK"));
			//���������߳�
			recvThread.start();
		} 
		catch (UnknownHostException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
			ChatRoomActivity.this.finish();
		} 
		catch (IOException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
		//recvhandler.post(recvRunable);
	}
	
	//�����߳�
	public class RecvThread extends Thread
	{
		@Override
		public void run() {
			// TODO Auto-generated method stub
			while(true)
			{
				try 
				{
					if (inStream.available() > 0)
					{
						//����byte
						byte[] 	recvByte = new byte[1024*2];
						int recvCount;
						if ((recvCount = inStream.read(recvByte)) < 0)
						{
							break;
						}
						//���ܵ���byteת�ɿɶ��е��ַ�������
						//Message msg = recvhandler.obtainMessage(1, 1, 1, (Object)(new String(recvByte , 0 , recvCount ,"GBK" )));
						//recvhandler.sendMessage(msg);
						String[] cmdStr = recvByteToString(recvByte , recvCount);
						//System.out.println(data);
						//System.out.println(data.length());
						//������Ϣ��recvhandler ��handler������
						//��һ������\0��β���ַ���Э����msg��ʽ����handler������������
						//�Ż��㷨
						int i = 0 ;
						for(i = 0 ; i < 10 ; i ++)
						{
							if(cmdStr[i].compareTo("") != 0)
							{
								Message msg = recvhandler.obtainMessage(1, 1, 1, (Object)cmdStr[i]);
								recvhandler.sendMessage(msg);
								//chatlist.append(cmdStr[i]);
							}
							else 
								break;
							//chatlist.append(Integer.toString(i));
						}
						//���instream��������������Э���������ֻ��ȡ����һ��
						/*if (recvCount(recvByte) > 0)
						{
							String recvStr = new String(recvByte , 0 , recvCount(recvByte) , "GBK");
							Message msg = recvhandler.obtainMessage(1, 1, 1, (Object)recvStr);
							recvhandler.sendMessage(msg);
						}*/
					}	
				} catch (Exception e) 
				{
					// TODO: handle exception
					//ChatRoomActivity.this.finish();
				}
			}
		}
	}
	
	//����ˢ�������¼handler
	public class RefleshHandler extends Handler
	{
		@Override
		public void handleMessage(Message msg)
		{
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			if(msg.what != 1)
				return ;
			String str = (String)msg.obj;
			String[] splitStr = str.split("\n" , 4);
			if (splitStr.length != 4)
			{
				//System.out.println(splitStr[0]);
				return ;
			}
			String type = splitStr[0];
			String fromuser = splitStr[1];
			String touser = splitStr[2];
			String data = splitStr[3];
			//��ǰʱ��
			SimpleDateFormat df = new SimpleDateFormat("HH:mm:ss");
			String timeStr = df.format(new Date());
			
			//�����ж���Ϣtype������
			//type == 1������Ⱥ��
			if (type.compareTo("1") == 0 )
			{
				chatlist.append(timeStr + " ");
				chatlist.append(fromuser + " ��������˵: ");
				chatlist.append(data + "\n");
			}
			//type == 2 ��ʾ˽��
			if (type.compareTo("2") == 0)
			{
				if (fromuser.compareTo(username) == 0)
				{
					chatlist.append(timeStr + " ");
					chatlist.append("���� " + touser + " ˵: ");
					chatlist.append(data + "\n");	
				}
				if (touser.compareTo(username) == 0)
				{
					chatlist.append(timeStr + " ");
					chatlist.append(fromuser + " ����˵: ");
					chatlist.append(data + "\n");				
				}
			}

			//type == 10 ��ʾע��ɹ�
			if (type.compareTo("10") == 0)
			{
				chatlist.append(timeStr + " ");
				chatlist.append("���Է���������Ϣ: ");
				chatlist.append(data + "\n");	
			}
			//type == 11 ��ʾע��ʧ�ܣ����û����ѱ�����ע��
			if (type.compareTo("11") == 0)
			{
				chatlist.append(timeStr + " ");
				chatlist.append("���Է���������Ϣ: ");
				chatlist.append(data + "\n");
			}
			//type == 12 ��ʾ�����û��б�
			if (type.compareTo("12") == 0)
			{
				userlist.getText().clear();
				userlist.append(data);
				userlist.append("����ʱ��: \n" + timeStr);
			}
			//type == 13��ʾ���û�����������
			if (type.compareTo("13") == 0)
			{
				chatlist.append(timeStr + " ");
				chatlist.append(data + "\n");
			}
			//type == 14��ʾ���͵�˽����Ϣ����
			if (type.compareTo("14") == 0)
			{
				chatlist.append(timeStr + " ");
				chatlist.append(data + "\n");
			}
			//System.out.println(type);
		}
	}
	
	//���������߳� ;���ַ���ʹ��handler�������̣߳����ȼ�̫�ߣ���ʹ����Activity��������״̬;
	//��˲������ַ���
	//����handler������Ϣ���ƣ�������յ����ݣ��ͷ���һ����Ϣ��handler��Ȼ������handler�Խ��յ��ַ���������;
	class RecvRunable implements Runnable
	{
		public void run() 
		{
			// TODO Auto-generated method stub	
			try 
			{
				if (inStream.available() > 0)
				{
				byte[] readBuff = new byte[1024*2];
				if (inStream.read(readBuff) < 0 )
					return;
				String data = new String(readBuff ,0 , recvCount(readBuff) , "GBK");
				System.out.println(data);
				System.out.println(data.length());
				chatlist.append(data);
				}	
				recvhandler.postDelayed(recvRunable, 2000);
			} 
			catch (IOException e) 
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	};
	private RecvRunable recvRunable = new RecvRunable();
	
	@Override
	protected void onStop() 
	{
		// TODO Auto-generated method stub
		super.onStop();
		try 
		{
			s.close();
		} 
		catch (IOException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Toast.makeText(ChatRoomActivity.this, "�Ѻͷ������Ͽ�����!", Toast.LENGTH_LONG).show();
		recvThread.stop();
	}
	@Override
	protected void onDestroy() 
	{
		// TODO Auto-generated method stub
		super.onDestroy();
		try 
		{
			s.close();
		} catch (IOException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		recvThread.stop();
	}
	
	//���Ͱ�ť��������д
	public class sendBtnListener implements OnClickListener
	{
		@Override
		public void onClick(View v) 
		{
			// TODO Auto-generated method stub
			if (message.getText().toString().length() == 0)
			{
				Toast.makeText(ChatRoomActivity.this, "���ܷ��Ϳ���Ϣ!", Toast.LENGTH_LONG).show();
				return ;
			}
			//�����˽��
			if(IsPrivate.isChecked())
			{
				if (toUserText.getText().length() == 0)
				{
					Toast.makeText(ChatRoomActivity.this, "��������Ҫ˽�ĵ��û���!", Toast.LENGTH_LONG).show();
					return ;
				}
				try {
					if(toUserText.getText().toString().getBytes("GBK").length > 18)
					{
						Toast.makeText(ChatRoomActivity.this, "˽�ĵ��û���̫��!", Toast.LENGTH_LONG).show();
						return ;
					}
				} catch (UnsupportedEncodingException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				String sendStr = "2\n" + username + "\n" + toUserText.getText().toString() + "\n" + message.getText().toString();

				//System.out.println(sendStr);
				try 
				{
					byte[] sendByte = sendStr.getBytes("GBK");
					outStream.write(sendByte);
					
				} 
				catch (Exception e) 
				{
					// TODO: handle exception
					ChatRoomActivity.this.finish();
				}
			}
			else 
			{
				String sendStr = "1\n" + username + "\n0\n" + message.getText().toString() ;

				try 
				{
					byte[] sendByte = sendStr.getBytes("GBK");
					outStream.write(sendByte);
	
				} 
				catch (Exception e) 
				{
					// TODO: handle exception
					ChatRoomActivity.this.finish();
				}
			}
			message.getText().clear();
		}
	}
	
	//��հ�ť������
	public class clearBtnListener implements OnClickListener
	{
		@Override
		public void onClick(View v) 
		{
			// TODO Auto-generated method stub
			chatlist.getText().clear();
		}
	}
	
	//˽��ѡ��ť������
	public class IsPrivateListener implements android.widget.CompoundButton.OnCheckedChangeListener
	{
		@Override
		public void onCheckedChanged
		(CompoundButton buttonView, boolean isChecked) 
		{
			// TODO Auto-generated method stub
			if (isChecked)
			{
				//toUserText ��д
				toUserText.setCursorVisible(true);
				toUserText.setFocusable(true);
				toUserText.setFocusableInTouchMode(true);
			}
			else
			{
				toUserText.setCursorVisible(false);
				toUserText.setFocusable(false);
				toUserText.setFocusableInTouchMode(false);
			}
		}
	}
	//�����socket inputstream�ж�ȡ���ٸ��ַ�
	public static int recvCount(byte[] in)
	{
		int i = 0;
		for (i = 0 ; i < in.length ; i ++)
		{
			if (in[i] == 0)
				return i;
		}
		return in.length;
	}
	//�Ż��㷨����instream��õ�Э�������ַ�������;
	public static String[] recvByteToString(byte[] in , int recvCount)
	{
		String[] cmdStrArr = new String[10];
		int i = recvCount;
		int k;
		int strCount = 0;
		int offset = 0;
		for (k = 0 ; k < i ; k ++)
		{
			if (in[k] == 0)
			{
				try 
				{
					cmdStrArr[strCount] = new String(in ,offset , k - offset , "GBK");
				} 
				catch (UnsupportedEncodingException e) 
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				strCount ++;
				offset = k + 1;
			}
		}
		//System.out.println(strCount);
		return cmdStrArr;
	}
	//���Լ���Cmd�ĸ���
	public static int cmdCount(String[] cmdStrArr)
	{
		String str = new String();
		int i;
		for (i = 0 ; i < cmdStrArr.length ; i ++)
		{
			if (str.compareTo(cmdStrArr[i]) == 0)
				return i;
		}
		return cmdStrArr.length;
	}
}
