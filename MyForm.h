#pragma once

namespace TaskManager {

	#include "Services/ProcessService.h"
	#include "Utils/Format.h"

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
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ viewToolStripMenuItem;
	private: System::Windows::Forms::ListView^ lvProcesses;




	protected:

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
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lvProcesses = (gcnew System::Windows::Forms::ListView());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->optionsToolStripMenuItem, this->viewToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1370, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(61, 20);
			this->optionsToolStripMenuItem->Text = L"Options";
			// 
			// viewToolStripMenuItem
			// 
			this->viewToolStripMenuItem->Name = L"viewToolStripMenuItem";
			this->viewToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->viewToolStripMenuItem->Text = L"View";
			// 
			// lvProcesses
			// 
			this->lvProcesses->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lvProcesses->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lvProcesses->FullRowSelect = true;
			this->lvProcesses->HideSelection = false;
			this->lvProcesses->Location = System::Drawing::Point(0, 24);
			this->lvProcesses->MultiSelect = false;
			this->lvProcesses->Name = L"lvProcesses";
			this->lvProcesses->Size = System::Drawing::Size(1370, 725);
			this->lvProcesses->TabIndex = 2;
			this->lvProcesses->UseCompatibleStateImageBehavior = false;
			this->lvProcesses->View = System::Windows::Forms::View::Details;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1370, 749);
			this->Controls->Add(this->lvProcesses);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Task Manager";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		void AddCol(String^ text, int width, HorizontalAlignment align)
		{
			ColumnHeader^ c = gcnew ColumnHeader();
			c->Text = text;
			c->Width = width;
			c->TextAlign = align;
			lvProcesses->Columns->Add(c);
		}

		void SetupColumns()
		{
			HorizontalAlignment L = HorizontalAlignment::Left;
			HorizontalAlignment R = HorizontalAlignment::Right;

			AddCol("Name", 145, L);
			AddCol("PID", 55, L);
			AddCol("Status", 70, L);
			AddCol("Base priority", 65, L);
			AddCol("Session ID", 65, L);
			AddCol("User name", 85, L);
			AddCol("CPU", 40, L);
			AddCol("CPU time", 70, L);
			AddCol("Working set delta", 115, R);
			AddCol("Working set", 85, R);
			AddCol("Peak working set", 110, R);
			AddCol("Commit size", 85, R);
			AddCol("Page faults", 85, R);
			AddCol("Handles", 75, R);
			AddCol("Threads", 60, R);
			AddCol("User objects", 60, R);
		}

		void LoadProcess()
		{
			ProcessService^ ProcessList = gcnew ProcessService();
			lvProcesses->BeginUpdate();
			lvProcesses->Items->Clear();

			for each (ProcessInfo ^ p in ProcessList->GetProcesses())
			{
				ListViewItem^ it = gcnew ListViewItem(p->GetName());
				it->SubItems->Add(p->GetPID().ToString());
				it->SubItems->Add(Format::State(p->GetState()));
				it->SubItems->Add(p->GetPriorityClass());
				it->SubItems->Add(p->GetOwnerName());
				it->SubItems->Add(p->GetCpuPercent().ToString("00"));
				it->SubItems->Add(Format::Time(p->GetCpuTime()));
				it->SubItems->Add(Format::Kb(p->GetWorkingSet()));
				it->SubItems->Add(Format::Kb(p->GetVirtualSize()));
				it->SubItems->Add(Format::Kb(p->GetPrivateBytes()));
				it->SubItems->Add(p->GetThreadCount().ToString());
				it->SubItems->Add(p->GetOwnerSid());
				it->SubItems->Add(p->GetFullPath());
				lvProcesses->Items->Add(it);
			}
			lvProcesses->EndUpdate();
		}
	};
}
