#pragma once
#include <vector>
#include <string>
//#include <msclr\marshal_cppstd.h>
#include <cliext/vector>
//#include <msclr\marshal.h>


using namespace cliext;
using namespace std;
using namespace System;
using namespace System::Diagnostics;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Data::OleDb;
using namespace System::Collections::Generic;


namespace GuestHouseManagement {

	/// <summary>
	/// Summary for UserControl_User_Types
	/// </summary>
	public ref class UserControl_User_Types : public System::Windows::Forms::UserControl
	{
	public:
		UserControl_User_Types(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UserControl_User_Types()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  Btn_Add;
	protected: 
	private: System::Windows::Forms::TextBox^  Txt_User_Type;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Btn_Add = (gcnew System::Windows::Forms::Button());
			this->Txt_User_Type = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// Btn_Add
			// 
			this->Btn_Add->Location = System::Drawing::Point(313, 114);
			this->Btn_Add->Name = L"Btn_Add";
			this->Btn_Add->Size = System::Drawing::Size(75, 23);
			this->Btn_Add->TabIndex = 3;
			this->Btn_Add->Text = L"Add";
			this->Btn_Add->UseVisualStyleBackColor = true;
			this->Btn_Add->Click += gcnew System::EventHandler(this, &UserControl_User_Types::Btn_Add_Click);
			// 
			// Txt_User_Type
			// 
			this->Txt_User_Type->Location = System::Drawing::Point(118, 118);
			this->Txt_User_Type->Name = L"Txt_User_Type";
			this->Txt_User_Type->Size = System::Drawing::Size(113, 20);
			this->Txt_User_Type->TabIndex = 2;
			// 
			// UserControl_User_Types
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->Controls->Add(this->Btn_Add);
			this->Controls->Add(this->Txt_User_Type);
			this->Name = L"UserControl_User_Types";
			this->Size = System::Drawing::Size(682, 553);
			this->Load += gcnew System::EventHandler(this, &UserControl_User_Types::UserControl_User_Types_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	cliext::vector<String^> vec;
	String ^ user;
	void button_click(System::Object^  sender, System::EventArgs^  e)
	{
		for(int i=0;i<vec.size();i++)
		{

			RichTextBox ^tb = (RichTextBox^)this->Controls["TextBox" + (i)];
			String ^str = tb->Text;

			//MessageBox::Show(str);
			OleDb::OleDbConnection ^ DB_Connection = gcnew OleDb::OleDbConnection();
			DB_Connection->ConnectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=GuestHouse.accdb";
			DB_Connection->Open();
			String ^ insertString = "insert into User_Room_Price([User_Types],[Room_Types],[Price]) VALUES('" +user+ "', '" +vec[i]+ "', '" +str+ "' );";

			OleDbCommand ^ cmd = gcnew OleDbCommand(insertString, DB_Connection);

			cmd->Parameters->Add(gcnew OleDbParameter("@User_Types",Convert::ToString(user)));
			cmd->Parameters->Add(gcnew OleDbParameter("@Room_Types",Convert::ToString(vec[i])));
			cmd->Parameters->Add(gcnew OleDbParameter("@Price",Convert::ToString(str)));

			cmd->ExecuteNonQuery();
			DB_Connection->Close();



		}

		OleDb::OleDbConnection ^ DB_Connection = gcnew OleDb::OleDbConnection();
		DB_Connection->ConnectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=GuestHouse.accdb";
		DB_Connection->Open();
		String ^ insertString = "insert into User_Types([User_Type]) VALUES('" +user+ "' );";
		OleDbCommand ^ cmd = gcnew OleDbCommand(insertString, DB_Connection);
		cmd->Parameters->Add(gcnew OleDbParameter("@User_Type",Convert::ToString(user)));
		cmd->ExecuteNonQuery();
		DB_Connection->Close();

		//To Refresh User Control
		this->Controls->Clear();
		this->InitializeComponent();
	}

	private: System::Void UserControl_User_Types_Load(System::Object^  sender, System::EventArgs^  e) {
				  
			 }
	private: System::Void Btn_Add_Click(System::Object^  sender, System::EventArgs^  e) {
				
				 //for(int i=1;i<5;i++)
				 //{
					// TextBox ^tb = gcnew TextBox();
					// tb->Text = Convert::ToString(i);
					// tb->Location = System::Drawing::Point(60,70*i);
					// tb->Width = 270;
					// tb->Height = 50;
					// tb->Name = "TextBox" + i;
					// tb->Multiline = true;
					// //tb->ReadOnly = true;
					// tb->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
					// this->Controls->Add(tb);
				 //}
			

					 Btn_Add->Visible = false;
					 OleDb::OleDbConnection ^ DB_Connection = gcnew OleDb::OleDbConnection();
					 DB_Connection->ConnectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=GuestHouse.accdb";
					 DB_Connection->Open();

					 user = Txt_User_Type->Text;
					 String ^ getUserData = "Select * from User_Types where [User_Type] = '" + user + "';";

					 OleDb::OleDbCommand ^ cmd = gcnew OleDbCommand(getUserData, DB_Connection);
					 OleDbDataReader ^ user_data = cmd->ExecuteReader();

					 if(user_data->Read() == true)
					 {
						 MessageBox::Show("User Type Already Exists");
						 DB_Connection->Close();
					 }
					 else
					 {
						 DB_Connection->Close();
						 if(String::IsNullOrWhiteSpace(user))
							 MessageBox::Show("Please Enter Some User Type");
						 else
						 {
							 Txt_User_Type->Visible = false;
							 Btn_Add->Visible = false;
							 DB_Connection->Open();

							 String ^ getRoomData = "Select * from Room_Types";
							 cmd = gcnew OleDbCommand(getRoomData, DB_Connection);

							 OleDbDataReader ^ room_data = cmd->ExecuteReader();

							 int n = 0;
							 while(room_data->Read() == true)
							 {
								 String ^ tmp = room_data->GetString(1);
								 vec.push_back(tmp);
								 n=n+1;
							 }


							 for(int i=0;i<vec.size();i++)
							 {
								 Label ^lb = gcnew Label();
								 lb->Text = vec[i];
								 lb->Location = System::Drawing::Point(20,70*(i+1));
								 this->Controls->Add(lb);
							
								 TextBox ^tb = gcnew TextBox();
								 //tb->Text = Convert::ToString(i);
								 tb->Location = System::Drawing::Point(100,70*(i+1));
								 tb->Width = 70;
								 tb->Height = 10;
								 tb->Name = "TextBox" + i;
								 //tb->Multiline = true;
								 tb->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
								 this->Controls->Add(tb);
							 }

							 Button ^ btn = gcnew Button();
							 btn->Text = "Submit";
							 btn->Name = "Btn_Submit";

							 btn->ForeColor = System::Drawing::SystemColors::WindowText;
							 btn->Location = System::Drawing::Point(40,30*n+30);
							 btn->Click += gcnew System::EventHandler(this,&UserControl_User_Types::button_click);
							 this->Controls->Add(btn);

							 DB_Connection->Close();

						 }
					 }



				 

				 /*catch(Exception ^ ex)
				 {
					 MessageBox::Show(ex->Message);
				 }*/
			 }
	};
}
