#pragma once
#include "Board.h"
//#include "windows.h"

namespace Chess {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(180, 200);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(217, 88);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Начать игру против компьютера!";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Enabled = false;
			this->label1->Location = System::Drawing::Point(200, 200);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(108, 17);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Выберите цвет";
			this->label1->Visible = false;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Enabled = false;
			this->checkBox1->Location = System::Drawing::Point(200, 230);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(73, 21);
			this->checkBox1->TabIndex = 2;
			this->checkBox1->Text = L"Белые";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->Visible = false;
			this->checkBox1->Click += gcnew System::EventHandler(this, &MyForm::checkBox1_Click);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Enabled = false;
			this->checkBox2->Location = System::Drawing::Point(200, 260);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(82, 21);
			this->checkBox2->TabIndex = 3;
			this->checkBox2->Text = L"Черные";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->Visible = false;
			this->checkBox2->Click += gcnew System::EventHandler(this, &MyForm::checkBox2_Click);
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->Location = System::Drawing::Point(200, 290);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Начать игру";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Visible = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Enabled = false;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(550, 600);
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Visible = false;
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseClick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(535, 493);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"Шашки";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: Board^ desk;
	private: const int SIZE = 50;
	private: bool start;

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		this->button1->Visible = false;
		this->button1->Enabled = false;

		this->button2->Enabled = true;
		this->button2->Visible = true;
		this->checkBox1->Visible = true;
		this->checkBox2->Visible = true;
		this->label1->Visible = true;
		this->checkBox1->Enabled = true;
		this->checkBox2->Enabled = true;
		this->label1->Enabled = true;
		
	}
	private: System::Void checkBox1_Click(System::Object^  sender, System::EventArgs^  e) {
		this->checkBox2->Checked = false;
		this->checkBox1->Checked = true;
	}

	private: System::Void checkBox2_Click(System::Object^  sender, System::EventArgs^  e) {
		this->checkBox1->Checked = false;
		this->checkBox2->Checked = true;
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		this->checkBox1->Visible = false;
		this->checkBox2->Visible = false;
		this->label1->Visible = false;
		this->checkBox1->Enabled = false;
		this->checkBox2->Enabled = false;
		this->label1->Enabled = false;
		this->button2->Enabled = false;
		this->button2->Visible = false;
		this->pictureBox1->Visible = true;
		this->pictureBox1->Enabled = true;
		
		desk = gcnew Board(pictureBox1, checkBox1->Checked);
		
	}
	private: System::Void pictureBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		
		desk->Paint(e);
		//desk->CheckEnd(0);
		if (desk->getRestart())
		{
			this->button1->Visible = true;
			this->button1->Enabled = true;
			delete[] desk;
		}
	}
};
}
