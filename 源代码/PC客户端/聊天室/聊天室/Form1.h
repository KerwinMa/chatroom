#pragma once
#include "ReceiveClass.h"
#include "MessageStruct.h"
#include <string>
#include <iostream>

namespace ������ {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;


	/// <summary>
	/// Form1 ժҪ
	///
	/// ����: ������Ĵ�������ƣ�����Ҫ����
	///          ����������������� .resx �ļ��������й���Դ���������ߵ�
	///          ����Դ�ļ��������ԡ�����
	///          �������������˴���Ĺ���
	///          ���ػ���Դ��ȷ������
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �ڴ˴���ӹ��캯������
			//
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			s = gcnew Socket( AddressFamily::InterNetwork,SocketType::Stream,ProtocolType::Tcp );
		}
	private: System::Windows::Forms::Button^  connectBtn;
	private: System::Windows::Forms::Button^  disconnectBtn;
	protected: 

	protected: 

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  ipaddr;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  username;


	private: System::Windows::Forms::RichTextBox^  message;


	private: System::Windows::Forms::Button^  sendBtn;
	private: System::Windows::Forms::RichTextBox^  userlist;

	private: 
	public: 



	private:System::Net::Sockets::Socket^ s ;
	private:Thread ^receivethread;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  tousername;
	private: System::Windows::Forms::Button^  clearBtn;
	private: System::Windows::Forms::RichTextBox^  chatlist;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;

	private: 




	private:
		/// <summary>
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void)
		{
			this->connectBtn = (gcnew System::Windows::Forms::Button());
			this->disconnectBtn = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ipaddr = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->username = (gcnew System::Windows::Forms::TextBox());
			this->message = (gcnew System::Windows::Forms::RichTextBox());
			this->sendBtn = (gcnew System::Windows::Forms::Button());
			this->userlist = (gcnew System::Windows::Forms::RichTextBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tousername = (gcnew System::Windows::Forms::TextBox());
			this->clearBtn = (gcnew System::Windows::Forms::Button());
			this->chatlist = (gcnew System::Windows::Forms::RichTextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// connectBtn
			// 
			this->connectBtn->Location = System::Drawing::Point(522, 83);
			this->connectBtn->Name = L"connectBtn";
			this->connectBtn->Size = System::Drawing::Size(85, 35);
			this->connectBtn->TabIndex = 0;
			this->connectBtn->Text = L"����";
			this->connectBtn->UseVisualStyleBackColor = true;
			this->connectBtn->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// disconnectBtn
			// 
			this->disconnectBtn->Location = System::Drawing::Point(637, 83);
			this->disconnectBtn->Name = L"disconnectBtn";
			this->disconnectBtn->Size = System::Drawing::Size(85, 35);
			this->disconnectBtn->TabIndex = 1;
			this->disconnectBtn->Text = L"�Ͽ�";
			this->disconnectBtn->UseVisualStyleBackColor = true;
			this->disconnectBtn->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"����", 12));
			this->label1->Location = System::Drawing::Point(519, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(88, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"��������ַ";
			// 
			// ipaddr
			// 
			this->ipaddr->Location = System::Drawing::Point(613, 13);
			this->ipaddr->Name = L"ipaddr";
			this->ipaddr->Size = System::Drawing::Size(109, 21);
			this->ipaddr->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"����", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label2->Location = System::Drawing::Point(530, 47);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(56, 16);
			this->label2->TabIndex = 4;
			this->label2->Text = L"�û���";
			// 
			// username
			// 
			this->username->Location = System::Drawing::Point(613, 48);
			this->username->Name = L"username";
			this->username->Size = System::Drawing::Size(109, 21);
			this->username->TabIndex = 5;
			// 
			// message
			// 
			this->message->Location = System::Drawing::Point(12, 290);
			this->message->Name = L"message";
			this->message->Size = System::Drawing::Size(386, 50);
			this->message->TabIndex = 7;
			this->message->Text = L"";
			// 
			// sendBtn
			// 
			this->sendBtn->Location = System::Drawing::Point(404, 331);
			this->sendBtn->Name = L"sendBtn";
			this->sendBtn->Size = System::Drawing::Size(99, 42);
			this->sendBtn->TabIndex = 9;
			this->sendBtn->Text = L"����";
			this->sendBtn->UseVisualStyleBackColor = true;
			this->sendBtn->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// userlist
			// 
			this->userlist->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->userlist->Location = System::Drawing::Point(522, 148);
			this->userlist->Name = L"userlist";
			this->userlist->ReadOnly = true;
			this->userlist->Size = System::Drawing::Size(205, 223);
			this->userlist->TabIndex = 10;
			this->userlist->Text = L"";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(37, 355);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(48, 16);
			this->checkBox1->TabIndex = 11;
			this->checkBox1->Text = L"˽��";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(91, 355);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(101, 12);
			this->label3->TabIndex = 12;
			this->label3->Text = L"˽�Ķ�����û���";
			// 
			// tousername
			// 
			this->tousername->Location = System::Drawing::Point(196, 352);
			this->tousername->Name = L"tousername";
			this->tousername->Size = System::Drawing::Size(202, 21);
			this->tousername->TabIndex = 13;
			// 
			// clearBtn
			// 
			this->clearBtn->Location = System::Drawing::Point(404, 290);
			this->clearBtn->Name = L"clearBtn";
			this->clearBtn->Size = System::Drawing::Size(99, 35);
			this->clearBtn->TabIndex = 14;
			this->clearBtn->Text = L"��������¼";
			this->clearBtn->UseVisualStyleBackColor = true;
			this->clearBtn->Click += gcnew System::EventHandler(this, &Form1::clearBtn_Click);
			// 
			// chatlist
			// 
			this->chatlist->AutoWordSelection = true;
			this->chatlist->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->chatlist->Location = System::Drawing::Point(12, 30);
			this->chatlist->Name = L"chatlist";
			this->chatlist->ReadOnly = true;
			this->chatlist->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->chatlist->Size = System::Drawing::Size(491, 236);
			this->chatlist->TabIndex = 8;
			this->chatlist->Text = L"";
			this->chatlist->TextChanged += gcnew System::EventHandler(this, &Form1::chatlist_TextChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"����", 12));
			this->label4->Location = System::Drawing::Point(13, 11);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(72, 16);
			this->label4->TabIndex = 15;
			this->label4->Text = L"�����¼";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"����", 12));
			this->label5->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label5->Location = System::Drawing::Point(519, 129);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(72, 16);
			this->label5->TabIndex = 16;
			this->label5->Text = L"�����û�";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(10, 272);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(53, 12);
			this->label6->TabIndex = 17;
			this->label6->Text = L"��������";
			// 
			// Form1
			// 
			this->AcceptButton = this->sendBtn;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ClientSize = System::Drawing::Size(739, 380);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->clearBtn);
			this->Controls->Add(this->username);
			this->Controls->Add(this->disconnectBtn);
			this->Controls->Add(this->ipaddr);
			this->Controls->Add(this->tousername);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->connectBtn);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->userlist);
			this->Controls->Add(this->sendBtn);
			this->Controls->Add(this->chatlist);
			this->Controls->Add(this->message);
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(755, 418);
			this->MinimumSize = System::Drawing::Size(755, 418);
			this->Name = L"Form1";
			this->Text = L"������";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 s = gcnew Socket( AddressFamily::InterNetwork,SocketType::Stream,ProtocolType::Tcp );

				//���߳�ȥ���ӣ�Ϊ�˲�������ʧ��
				 /*receivethread = gcnew Thread(gcnew ThreadStart(this->connect));
				 receivethread->Start();*/
				 
				 if(String::IsNullOrEmpty(username->Text->ToString()) || String::IsNullOrEmpty(ipaddr->Text->ToString()) )
				 {
					 MessageBox::Show("��������ַ���û�������Ϊ��!");
					 return;
				 }
				 array<Byte> ^usernameByte = Encoding::GetEncoding("GBK")->GetBytes(username->Text->ToString());
				 if (usernameByte->Length > 18 )
				 {
					MessageBox::Show("�û������ܳ���18���ֽ�!");
					 return;
				 }
				 DateTime^ time = DateTime::Now;
				chatlist->AppendText(time->ToLongTimeString() + "  ");
				 chatlist->AppendText("���ڳ������ӡ���\n");
				 String ^ipadd = ipaddr->Text->ToString();
				 IPAddress ^ipAdd ;
				 if(!ipAdd ->TryParse(ipadd , ipAdd))
				 {
					 MessageBox::Show("�����IP��ַ���Ϸ����������룡");
					 chatlist->AppendText("����ʧ�ܣ�\n");
					 return ;
				 }
				//try catch ��ʽȥ����
				 try
				 {
					 s->Connect(ipAdd , 3204);
					 DateTime^ time = DateTime::Now;
					 chatlist->AppendText(time->ToLongTimeString() + "  ");
					 chatlist->AppendText("���ӳɹ�!\n");

					 //�����������û�����¼
					 String ^type = "0\n";
					 String ^usernameText = username->Text->ToString()+"\n";
					 String ^tousernameText = "0\n";
					 String ^messageText = "0";
					 String ^sendText = type + usernameText + tousernameText + messageText;
					 array<Byte> ^messageByte = Encoding::GetEncoding("GBK")->GetBytes(sendText);
					 s->Send(messageByte , messageByte->Length , static_cast<SocketFlags>(0));
					
					 //��һ���̣߳�����һֱ��ȡ����������������
					 ReceiveClass^ receiveClass = gcnew ReceiveClass(s , chatlist , connectBtn , disconnectBtn , sendBtn , username->Text->ToString() , userlist , username , ipaddr);
					 receivethread = gcnew Thread(gcnew ThreadStart(receiveClass,&ReceiveClass::DoReceive));
					 receivethread->Start();

					 sendBtn->Enabled = true;
					 disconnectBtn->Enabled = true;
					 connectBtn->Enabled = false;
					 ipaddr->ReadOnly = true;
					 username->ReadOnly = true;
					 this->AcceptButton = sendBtn;
				 }
				 catch(Exception^ e)
				 {
					 MessageBox::Show(e->Message);
					 DateTime^ time = DateTime::Now;
					 chatlist->AppendText(time->ToLongTimeString() + "  ");
					 chatlist->AppendText("����ʧ��!\n");
				 }
				 finally
				 {
	
				 }

				//��ͨ�����Ӵ���
				 /*if(String::IsNullOrEmpty(username->Text->ToString()) || String::IsNullOrEmpty(ipaddr->Text->ToString()) || username->Text->Length >19 || username->Text->Length <1 )
				 {
					 MessageBox::Show("������һ���Ϸ���IP��ַ��һ������С��19���û���!");
					 return;
				 }
				 DateTime^ time = DateTime::Now;
				chatlist->AppendText(time->ToLongTimeString() + "  ");
				 chatlist->AppendText("���ڳ������ӡ���\n");
				 String ^ipadd = ipaddr->Text->ToString();
				 IPAddress ^ipAdd ;
				 if(!ipAdd ->TryParse(ipadd , ipAdd))
				 {
					 MessageBox::Show("�����IP��ַ���Ϸ����������룡");
					 chatlist->AppendText("����ʧ�ܣ�\n");
					 return ;
				 }
				s->Connect(ipAdd , 3204);
				 if (s->Connected)
				 {
					 DateTime^ time = DateTime::Now;
					 chatlist->AppendText(time->ToLongTimeString() + "  ");
					 chatlist->AppendText("���ӳɹ�!\n");

					 //�����������û�����¼
					 String ^type = "0\n";
					 String ^usernameText = username->Text->ToString()+"\n";
					 String ^tousernameText = "0\n";
					 String ^messageText = "0";
					 String ^sendText = type + usernameText + tousernameText + messageText;
					 array<Byte> ^messageByte = Encoding::GetEncoding("GBK")->GetBytes(sendText);
					 s->Send(messageByte , messageByte->Length , static_cast<SocketFlags>(0));
					
					 //��һ���̣߳�����һֱ��ȡ����������������
					 ReceiveClass^ receiveClass = gcnew ReceiveClass(s , chatlist , connectBtn , disconnectBtn , sendBtn , username->Text->ToString() , userlist , username , ipaddr);
					 receivethread = gcnew Thread(gcnew ThreadStart(receiveClass,&ReceiveClass::DoReceive));
					 receivethread->Start();

					 sendBtn->Enabled = true;
					 disconnectBtn->Enabled = true;
					 connectBtn->Enabled = false;
					 ipaddr->ReadOnly = true;
					 username->ReadOnly = true;
				 }
				 else
				 {
					 DateTime^ time = DateTime::Now;
					 chatlist->AppendText(time->ToLongTimeString() + "  ");
					 chatlist->AppendText("����ʧ��!\n");
				 }*/
			 }

			 //�Ͽ����Ӱ�ť
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 s->Disconnect(true);
			 s = gcnew Socket( AddressFamily::InterNetwork,SocketType::Stream,ProtocolType::Tcp );
			 ipaddr->ReadOnly = false;
			 username->ReadOnly = false;
			 sendBtn->Enabled = false;
			 connectBtn->Enabled = true;
			 disconnectBtn->Enabled = false;
			 this->AcceptButton = connectBtn;
			 //DateTime^ time = DateTime::Now;
			 //chatlist->AppendText(time->ToLongTimeString() + "  ");
			 //chatlist->AppendText("�Ѿ��ͷ������Ͽ����ӣ�\n");
			 userlist->Clear();
		 }

		 //���췢�Ͱ�ť
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 if (String::IsNullOrEmpty(message->Text->ToString()))
			 {
				 return;
			 }
			 if (checkBox1->Checked)
			 {
				 String ^type = "2\n";
				 String ^usernameText = username->Text->ToString()+"\n";
				 String ^tousernameText = tousername->Text->ToString() + "\n";
				 String ^messageText = message->Text->ToString() ;
				 array<Byte> ^touserByte = Encoding::GetEncoding("GBK")->GetBytes(tousername->Text->ToString());
				 if (touserByte->Length >18)
				 {
					 MessageBox::Show("�������˽���û���������");
					 return;
				 }
				 String ^sendText = type + usernameText + tousernameText + messageText;
				 array<Byte> ^messageByte = Encoding::GetEncoding("GBK")->GetBytes(sendText);
				 s->Send(messageByte , messageByte->Length , static_cast<SocketFlags>(0));
			 }
			 else
			 {
				 String ^type = "1\n";
				 String ^usernameText = username->Text->ToString()+"\n";
				 String ^tousernameText = "0\n";
				 String ^messageText = message->Text->ToString() ;
				 String ^sendText = type + usernameText + tousernameText + messageText;
				 array<Byte> ^messageByte = Encoding::GetEncoding("GBK")->GetBytes(sendText);
				 s->Send(messageByte , messageByte->Length , static_cast<SocketFlags>(0));
			 }
			 message->Focus();
			 message->Clear();
		 }

		 //��ʼ����ʼ����ʱ
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
		 {
			 Control::CheckForIllegalCrossThreadCalls = false;						//�߳�Խ�����

			 disconnectBtn->Enabled = false;
			 sendBtn->Enabled = false;
			 tousername->Enabled = false;
			 this->AcceptButton = connectBtn;
			 s = gcnew Socket( AddressFamily::InterNetwork,SocketType::Stream,ProtocolType::Tcp );
		 }

		 //�Ƿ�˽�İ�ť
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (checkBox1->Checked)
			 {
				 tousername->Enabled = true ;
			 }
			 else
			 {
				 tousername->Enabled = false;
			 }
		 }

		 //����������¼��ť
private: System::Void clearBtn_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 chatlist->Clear();
			 chatlist->Refresh();
		 }

		 //�رճ���ʱ
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
		 {
			 if (s->Connected)
			 {
				 s->Disconnect(false);
				 receivethread->Abort();
			 }
		 }
		 //Ϊ��ʹchatlist��ʾ�Զ���������������Ϣ�����ʹ��focus���ٰ�focus����message
private: System::Void chatlist_TextChanged(System::Object^  sender, System::EventArgs^  e)
		 {
			 chatlist->SelectionStart = chatlist->TextLength;
			 chatlist->ScrollToCaret();
		 }
};

}

