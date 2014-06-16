#pragma once
#include "Graf.h"
#include "PriorityQueueBase.h"

namespace Graf_Way {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
		static Graphics  ^gr;
		static BufferedGraphicsContext ^st = BufferedGraphicsManager::Current;
		static BufferedGraphics ^buff;
		Pen^ pen;
		Graf^ graf1;
		Vertex^ SelectV;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button4;
			 int NowMouseDown;
	public:
		Form1(void)
		{
			InitializeComponent();
			gr = this->CreateGraphics();
			System::Drawing::Rectangle rect(0,0,1000,500);
			buff = st->Allocate(gr, rect);
			pen = gcnew Pen(Color::Green);
			buff->Graphics->Clear(Color::WhiteSmoke);
			graf1 = gcnew Graf(25);
			SelectV = nullptr;
			NowMouseDown = 0;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(654, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(120, 28);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Очистить";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(731, 47);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(41, 20);
			this->textBox3->TabIndex = 7;
			this->textBox3->Text = L"10";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(651, 49);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(62, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Веc ребра:";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(654, 68);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(120, 64);
			this->button3->TabIndex = 9;
			this->button3->Text = L"Найти ост. подграф (d-Кучи)";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(654, 138);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(120, 64);
			this->button2->TabIndex = 10;
			this->button2->Text = L"Найти ост. подграф (бин. деревья)";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(654, 208);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(120, 64);
			this->button4->TabIndex = 11;
			this->button4->Text = L"Найти ост. подграф (хеш-таблицы)";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(786, 426);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Spanning subgraph";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Shown += gcnew System::EventHandler(this, &Form1::Form1_Shown);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseClick);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseUp);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	void RepaintGraph()
	{
		buff->Graphics->Clear(Color::WhiteSmoke);
		graf1->Draw(buff);
		buff->Render();
	}

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e)  {	 
			 }
	private: System::Void Form1_Shown(System::Object^  sender, System::EventArgs^  e) {
				 graf1->Add(100, 100);
				 RepaintGraph();
			 }
	private: System::Void Form1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if( e->Button == System::Windows::Forms::MouseButtons::Left )
				 {
					if( graf1->GetVertex(e->X, e->Y) == nullptr ) // если вершина не найдена то можно ее сюда тыкнуть
						graf1->Add(e->X, e->Y);
				 }
				 if( e->Button == System::Windows::Forms::MouseButtons::Right )
				 {

				 }
				 RepaintGraph();
			 }
	private: System::Void Form1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 
				 if( e->Button == System::Windows::Forms::MouseButtons::Left )
					 NowMouseDown = 1;

				 if( e->Button == System::Windows::Forms::MouseButtons::Right )
					 NowMouseDown = 2;

				 SelectV = graf1->GetVertex(e->X, e->Y);
			 }
	private: System::Void Form1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 buff->Graphics->Clear(Color::WhiteSmoke);
				 if(NowMouseDown)
				 {
					 if(NowMouseDown == 1)
					 {
						 if(SelectV != nullptr)
						 {
							 SelectV->x = e->X;
							 SelectV->y = e->Y;
						 }
					 }
					 if(NowMouseDown == 2)
					 {
						 if(SelectV != nullptr)
						 {
							buff->Graphics->DrawLine(pen, SelectV->x, SelectV->y, e->X, e->Y);
						 }
					 }
					 graf1->Draw(buff);
					 buff->Render();
				 }
			 }
	private: System::Void Form1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if(NowMouseDown)
				 {
					 if(NowMouseDown == 1)
					 {
						 if(SelectV != nullptr)
						 {
							 SelectV->x = e->X;
							 SelectV->y = e->Y;
						 }
					 }
					 if(NowMouseDown == 2)
					 {
						 if(SelectV != nullptr)
						 {
							 Vertex^ temp = graf1->GetVertex(e->X, e->Y);
							 if(temp != nullptr && SelectV->Number != temp->Number) // если мы отпускаем ребро в вершине (и отличной от начальной)
								 graf1->AddEdge(SelectV->Number, temp->Number, Convert::ToInt32(textBox3->Text) );
						 }
					 }
					 RepaintGraph();
				 }
				 NowMouseDown = 0;
			 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

			 graf1->Clear();
			 RepaintGraph();
		 }

private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 PriorityQueueBase^ q = gcnew QueueHeap();
			 graf1->findOstSubgraf(q);
			 RepaintGraph();
		 }

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 PriorityQueueBase^ q = gcnew QueueTree();
			 graf1->findOstSubgraf(q);
			 RepaintGraph();
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 PriorityQueueBase^ q = gcnew HashTable();
			 graf1->findOstSubgraf(q);
			 RepaintGraph();
		 }
};
}

