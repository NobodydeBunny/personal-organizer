#pragma once
#include"FileHandle.h"
#include"Org_app.h"

namespace PersonalOrganizer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			signinPanel->Hide();
			signUpPnl->Hide();
			createDataFile();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ signupButtn;
	private: System::Windows::Forms::Button^ signinButtn;
	private: System::Windows::Forms::Button^ ExitButtn;




	private: System::Windows::Forms::Panel^ signinPanel;




	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Button^ signInButtn2;

	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::Panel^ signUpPnl;


	private: System::Windows::Forms::Panel^ panel5;
	private: System::Windows::Forms::TextBox^ textBox4;


	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::TextBox^ textBox3;


	private: System::Windows::Forms::Label^ conPasslbl;

	private: System::Windows::Forms::Label^ Passwordlbl;
	private: System::Windows::Forms::Label^ Usernamelbl;
	private: System::Windows::Forms::Button^ signupbtn2;
	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::TextBox^ textBox5;

	protected:

	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->signupButtn = (gcnew System::Windows::Forms::Button());
			this->signinButtn = (gcnew System::Windows::Forms::Button());
			this->ExitButtn = (gcnew System::Windows::Forms::Button());
			this->signinPanel = (gcnew System::Windows::Forms::Panel());
			this->signInButtn2 = (gcnew System::Windows::Forms::Button());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->signUpPnl = (gcnew System::Windows::Forms::Panel());
			this->signupbtn2 = (gcnew System::Windows::Forms::Button());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->conPasslbl = (gcnew System::Windows::Forms::Label());
			this->Passwordlbl = (gcnew System::Windows::Forms::Label());
			this->Usernamelbl = (gcnew System::Windows::Forms::Label());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->signinPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->panel3->SuspendLayout();
			this->panel2->SuspendLayout();
			this->signUpPnl->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			this->panel4->SuspendLayout();
			this->panel5->SuspendLayout();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(41, 48);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(361, 167);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			// 
			// signupButtn
			// 
			this->signupButtn->BackColor = System::Drawing::Color::Transparent;
			this->signupButtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"signupButtn.BackgroundImage")));
			this->signupButtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->signupButtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->signupButtn->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->signupButtn->FlatAppearance->BorderSize = 0;
			this->signupButtn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->signupButtn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->signupButtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->signupButtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 22.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->signupButtn->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->signupButtn->Location = System::Drawing::Point(64, 353);
			this->signupButtn->Name = L"signupButtn";
			this->signupButtn->Size = System::Drawing::Size(322, 80);
			this->signupButtn->TabIndex = 1;
			this->signupButtn->Text = L"SIGN UP";
			this->signupButtn->UseVisualStyleBackColor = false;
			this->signupButtn->Click += gcnew System::EventHandler(this, &MyForm::signupButtn_Click);
			// 
			// signinButtn
			// 
			this->signinButtn->BackColor = System::Drawing::Color::Transparent;
			this->signinButtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"signinButtn.BackgroundImage")));
			this->signinButtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->signinButtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->signinButtn->FlatAppearance->BorderSize = 0;
			this->signinButtn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->signinButtn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->signinButtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->signinButtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 22.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->signinButtn->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->signinButtn->Location = System::Drawing::Point(64, 267);
			this->signinButtn->Name = L"signinButtn";
			this->signinButtn->Size = System::Drawing::Size(322, 80);
			this->signinButtn->TabIndex = 2;
			this->signinButtn->Text = L"SIGN IN";
			this->signinButtn->UseVisualStyleBackColor = false;
			this->signinButtn->Click += gcnew System::EventHandler(this, &MyForm::signinButtn_Click);
			// 
			// ExitButtn
			// 
			this->ExitButtn->BackColor = System::Drawing::Color::Transparent;
			this->ExitButtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ExitButtn.BackgroundImage")));
			this->ExitButtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ExitButtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->ExitButtn->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->ExitButtn->FlatAppearance->BorderSize = 0;
			this->ExitButtn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->ExitButtn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->ExitButtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ExitButtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ExitButtn->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->ExitButtn->Location = System::Drawing::Point(138, 453);
			this->ExitButtn->Name = L"ExitButtn";
			this->ExitButtn->Size = System::Drawing::Size(163, 61);
			this->ExitButtn->TabIndex = 3;
			this->ExitButtn->Text = L"EXIT";
			this->ExitButtn->UseVisualStyleBackColor = false;
			this->ExitButtn->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// signinPanel
			// 
			this->signinPanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"signinPanel.BackgroundImage")));
			this->signinPanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->signinPanel->Controls->Add(this->signInButtn2);
			this->signinPanel->Controls->Add(this->pictureBox3);
			this->signinPanel->Controls->Add(this->pictureBox2);
			this->signinPanel->Controls->Add(this->panel3);
			this->signinPanel->Controls->Add(this->panel2);
			this->signinPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->signinPanel->Location = System::Drawing::Point(0, 0);
			this->signinPanel->Name = L"signinPanel";
			this->signinPanel->Size = System::Drawing::Size(450, 600);
			this->signinPanel->TabIndex = 4;
			this->signinPanel->Click += gcnew System::EventHandler(this, &MyForm::OtherClicks);
			this->signinPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint);
			// 
			// signInButtn2
			// 
			this->signInButtn2->BackColor = System::Drawing::Color::Transparent;
			this->signInButtn2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"signInButtn2.BackgroundImage")));
			this->signInButtn2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->signInButtn2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->signInButtn2->FlatAppearance->BorderSize = 0;
			this->signInButtn2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->signInButtn2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->signInButtn2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->signInButtn2->ForeColor = System::Drawing::Color::Black;
			this->signInButtn2->Location = System::Drawing::Point(127, 425);
			this->signInButtn2->Name = L"signInButtn2";
			this->signInButtn2->Size = System::Drawing::Size(191, 51);
			this->signInButtn2->TabIndex = 0;
			this->signInButtn2->Text = L"SIGN IN";
			this->signInButtn2->UseVisualStyleBackColor = false;
			this->signInButtn2->Click += gcnew System::EventHandler(this, &MyForm::signInButtn2_Click);
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.BackgroundImage")));
			this->pictureBox3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox3->Location = System::Drawing::Point(153, 468);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(134, 105);
			this->pictureBox3->TabIndex = 6;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &MyForm::pictureBox3_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(64, 77);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(322, 118);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 5;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &MyForm::OtherClicks);
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::Transparent;
			this->panel3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel3.BackgroundImage")));
			this->panel3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panel3->Controls->Add(this->textBox2);
			this->panel3->Location = System::Drawing::Point(42, 330);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(365, 70);
			this->panel3->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(169)), static_cast<System::Int32>(static_cast<System::Byte>(103)),
				static_cast<System::Int32>(static_cast<System::Byte>(103)));
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(24, 16);
			this->textBox2->MaxLength = 25;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(321, 44);
			this->textBox2->TabIndex = 0;
			this->textBox2->Text = L"Password";
			this->textBox2->UseSystemPasswordChar = true;
			this->textBox2->Click += gcnew System::EventHandler(this, &MyForm::textBox2_Click);
			this->textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBox2_KeyDown);
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::Transparent;
			this->panel2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel2.BackgroundImage")));
			this->panel2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panel2->Controls->Add(this->textBox1);
			this->panel2->Location = System::Drawing::Point(42, 238);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(365, 70);
			this->panel2->TabIndex = 1;
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(169)), static_cast<System::Int32>(static_cast<System::Byte>(103)),
				static_cast<System::Int32>(static_cast<System::Byte>(103)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(24, 16);
			this->textBox1->MaxLength = 30;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(321, 44);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"Username";
			this->textBox1->Click += gcnew System::EventHandler(this, &MyForm::textBox1_Click);
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBox1_KeyDown);
			// 
			// signUpPnl
			// 
			this->signUpPnl->BackColor = System::Drawing::Color::Transparent;
			this->signUpPnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"signUpPnl.BackgroundImage")));
			this->signUpPnl->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->signUpPnl->Controls->Add(this->signupbtn2);
			this->signUpPnl->Controls->Add(this->pictureBox4);
			this->signUpPnl->Controls->Add(this->panel4);
			this->signUpPnl->Controls->Add(this->conPasslbl);
			this->signUpPnl->Controls->Add(this->Passwordlbl);
			this->signUpPnl->Controls->Add(this->Usernamelbl);
			this->signUpPnl->Controls->Add(this->panel5);
			this->signUpPnl->Controls->Add(this->panel1);
			this->signUpPnl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->signUpPnl->Location = System::Drawing::Point(0, 0);
			this->signUpPnl->Name = L"signUpPnl";
			this->signUpPnl->Size = System::Drawing::Size(450, 600);
			this->signUpPnl->TabIndex = 7;
			this->signUpPnl->Click += gcnew System::EventHandler(this, &MyForm::signUpPnl_Click);
			// 
			// signupbtn2
			// 
			this->signupbtn2->BackColor = System::Drawing::Color::Transparent;
			this->signupbtn2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"signupbtn2.BackgroundImage")));
			this->signupbtn2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->signupbtn2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->signupbtn2->FlatAppearance->BorderSize = 0;
			this->signupbtn2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->signupbtn2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->signupbtn2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->signupbtn2->ForeColor = System::Drawing::Color::Black;
			this->signupbtn2->Location = System::Drawing::Point(127, 411);
			this->signupbtn2->Name = L"signupbtn2";
			this->signupbtn2->Size = System::Drawing::Size(191, 51);
			this->signupbtn2->TabIndex = 8;
			this->signupbtn2->Text = L"SIGN UP";
			this->signupbtn2->UseVisualStyleBackColor = false;
			this->signupbtn2->Click += gcnew System::EventHandler(this, &MyForm::signupbtn2_Click);
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.BackgroundImage")));
			this->pictureBox4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox4->Location = System::Drawing::Point(153, 454);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(134, 105);
			this->pictureBox4->TabIndex = 9;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &MyForm::pictureBox4_Click);
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::Transparent;
			this->panel4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel4.BackgroundImage")));
			this->panel4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panel4->Controls->Add(this->textBox5);
			this->panel4->Location = System::Drawing::Point(42, 327);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(365, 70);
			this->panel4->TabIndex = 4;
			// 
			// textBox5
			// 
			this->textBox5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(169)), static_cast<System::Int32>(static_cast<System::Byte>(103)),
				static_cast<System::Int32>(static_cast<System::Byte>(103)));
			this->textBox5->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox5->Location = System::Drawing::Point(24, 16);
			this->textBox5->MaxLength = 30;
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(321, 44);
			this->textBox5->TabIndex = 0;
			this->textBox5->UseSystemPasswordChar = true;
			this->textBox5->Click += gcnew System::EventHandler(this, &MyForm::textBox5_Click);
			this->textBox5->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBox5_KeyDown);
			// 
			// conPasslbl
			// 
			this->conPasslbl->ForeColor = System::Drawing::SystemColors::AppWorkspace;
			this->conPasslbl->Location = System::Drawing::Point(50, 294);
			this->conPasslbl->Name = L"conPasslbl";
			this->conPasslbl->Size = System::Drawing::Size(230, 38);
			this->conPasslbl->TabIndex = 7;
			this->conPasslbl->Text = L"Confirm Password";
			this->conPasslbl->Click += gcnew System::EventHandler(this, &MyForm::signUpPnl_Click);
			// 
			// Passwordlbl
			// 
			this->Passwordlbl->ForeColor = System::Drawing::SystemColors::AppWorkspace;
			this->Passwordlbl->Location = System::Drawing::Point(50, 181);
			this->Passwordlbl->Name = L"Passwordlbl";
			this->Passwordlbl->Size = System::Drawing::Size(194, 38);
			this->Passwordlbl->TabIndex = 6;
			this->Passwordlbl->Text = L"Enter Password";
			this->Passwordlbl->Click += gcnew System::EventHandler(this, &MyForm::signUpPnl_Click);
			// 
			// Usernamelbl
			// 
			this->Usernamelbl->ForeColor = System::Drawing::SystemColors::AppWorkspace;
			this->Usernamelbl->Location = System::Drawing::Point(50, 67);
			this->Usernamelbl->Name = L"Usernamelbl";
			this->Usernamelbl->Size = System::Drawing::Size(194, 38);
			this->Usernamelbl->TabIndex = 5;
			this->Usernamelbl->Text = L"Enter Username";
			this->Usernamelbl->Click += gcnew System::EventHandler(this, &MyForm::signUpPnl_Click);
			// 
			// panel5
			// 
			this->panel5->BackColor = System::Drawing::Color::Transparent;
			this->panel5->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel5.BackgroundImage")));
			this->panel5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panel5->Controls->Add(this->textBox4);
			this->panel5->Location = System::Drawing::Point(39, 221);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(365, 70);
			this->panel5->TabIndex = 3;
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(169)), static_cast<System::Int32>(static_cast<System::Byte>(103)),
				static_cast<System::Int32>(static_cast<System::Byte>(103)));
			this->textBox4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox4->Location = System::Drawing::Point(24, 16);
			this->textBox4->MaxLength = 30;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(321, 44);
			this->textBox4->TabIndex = 0;
			this->textBox4->UseSystemPasswordChar = true;
			this->textBox4->Click += gcnew System::EventHandler(this, &MyForm::textBox4_Click);
			this->textBox4->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBox4_KeyDown);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Transparent;
			this->panel1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel1.BackgroundImage")));
			this->panel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panel1->Controls->Add(this->textBox3);
			this->panel1->Location = System::Drawing::Point(42, 108);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(365, 70);
			this->panel1->TabIndex = 2;
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(169)), static_cast<System::Int32>(static_cast<System::Byte>(103)),
				static_cast<System::Int32>(static_cast<System::Byte>(103)));
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(24, 16);
			this->textBox3->MaxLength = 30;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(321, 44);
			this->textBox3->TabIndex = 0;
			this->textBox3->Click += gcnew System::EventHandler(this, &MyForm::textBox3_Click);
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::EnterUserNTB_TextChanged);
			this->textBox3->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBox3_KeyDown);
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(450, 600);
			this->Controls->Add(this->signUpPnl);
			this->Controls->Add(this->signinPanel);
			this->Controls->Add(this->ExitButtn);
			this->Controls->Add(this->signinButtn);
			this->Controls->Add(this->signupButtn);
			this->Controls->Add(this->pictureBox1);
			this->DoubleBuffered = true;
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Opacity = 0.9;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"CHECK";
			this->TransparencyKey = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(116)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->signinPanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->signUpPnl->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox1->Text == "Username") 
		{
			textBox1->Text = "";
		}
	}
	private: System::Void textBox2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox2->Text == "Password") 
		{
			textBox2->Text = "";
		}
	}
	private: System::Void panel1_Click(System::Object^ sender, System::EventArgs^ e) {}



private: System::Void OtherClicks(System::Object^ sender, System::EventArgs^ e) {
	if (textBox1->Text == "")
	{
		textBox1->Text = "Username";
	}
	if (textBox2->Text == "")
	{
		textBox2->Text = "Password";
	}
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	Application::Exit();
}
private: System::Void pictureBox3_Click(System::Object^ sender, System::EventArgs^ e) {
	signinPanel->Hide();
	signUpPnl->Hide();
	textBox1->Text = "Username";
	textBox2->Text = "Password";
	textBox3->Text = "";
	textBox4->Text = "";
	textBox5->Text = "";
}
private: System::Void textBox3_Click(System::Object^ sender, System::EventArgs^ e) {
		textBox3->Text = "";
}
private: System::Void textBox5_Click(System::Object^ sender, System::EventArgs^ e) {
		textBox5->Text = "";
}
private: System::Void textBox4_Click(System::Object^ sender, System::EventArgs^ e) {
		textBox4->Text = "";
}
private: System::Void pictureBox4_Click(System::Object^ sender, System::EventArgs^ e) {
	signUpPnl->Hide();
	signinPanel->Hide();
	textBox1->Text = "Username";
	textBox2->Text = "Password";
	textBox3->Text = "";
	textBox4->Text = "";
	textBox5->Text = "";
}
private: System::Void signUpPnl_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void signinButtn_Click(System::Object^ sender, System::EventArgs^ e) {
	signinPanel->Show();
	signUpPnl->Hide();
}
private: System::Void signupButtn_Click(System::Object^ sender, System::EventArgs^ e) {
	signUpPnl->Show();
	signinPanel->Hide();
	
}
private: System::Void EnterUserNTB_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void signupbtn2_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ username = textBox3->Text;
	String^ password = textBox4->Text;
	if (username->Length < 4) {
		MessageBox::Show("Username should be at least\n4 character long!", "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else if (CheckUsername(username)) {
		MessageBox::Show("Username Already Taken", "Invalid Username",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else if (textBox4->Text != textBox5->Text)
	{
		MessageBox::Show("Password does not match", "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else if (password->Length < 4) {
		MessageBox::Show("Password Should be at least\n4 character long!", "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else {
		storeUserData(username, password);
		createDataFileUser(username);
		MessageBox::Show("Profile Successfully Created", "Success",
			MessageBoxButtons::OK, MessageBoxIcon::Information);
		signUpPnl->Hide();
		signinPanel->Show();
	}
	
}
private: System::Void signInButtn2_Click(System::Object^ sender, System::EventArgs^ e) {
	
	String^ username = textBox1->Text;
	String^ password = textBox2->Text;
	if (textBox1->Text == "Username" || textBox2->Text == "password") {
		MessageBox::Show("Enter valid username and password", "Warning",
			MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	else if (textBox1->Text == "" || textBox2->Text == "") {
		MessageBox::Show("Fields Cannot be Empty", "Warning",
			MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	else if (signIn(username, password))
	{
		String^ username = textBox1->Text;
		Org_app^ OrgApp = gcnew Org_app(username);
		OrgApp->Show();
		this->Hide();
		
	}
	else {
		MessageBox::Show("Incorrect Username or Password", "Warning",
			MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	}
	
private: System::Void textBox3_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (e->KeyValue == (int)Keys::Enter) {
		textBox4->Focus();
	}
}
private: System::Void textBox4_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (e->KeyValue == (int)Keys::Enter) {
		textBox5->Focus();
	}
}
private: System::Void textBox5_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (e->KeyValue == (int)Keys::Enter) {
		signupbtn2->PerformClick();
	}
}
private: System::Void textBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (e->KeyValue == (int)Keys::Enter) {
		textBox2->Focus();
	}
}
private: System::Void textBox2_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (e->KeyValue == (int)Keys::Enter) {
		signInButtn2->PerformClick();
	}
}
};
}
