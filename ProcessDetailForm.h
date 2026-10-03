#pragma once

#include "Models/ProcessInfo.h"
#include "Utils/Format.h"
#include "Thread/ThreadService.h"

namespace TaskManager {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm1
	/// </summary>
	public ref class ProcessDetailsForm : public System::Windows::Forms::Form
	{
	public:
		ProcessDetailsForm(ProcessInfo^ p)
		{
			InitializeComponent();

			pid = p->GetPID();
			threadService = gcnew ThreadService();

			lvDetails->Columns->Add("Parameter", 150);
			lvDetails->Columns->Add("Value", 600);

			lvThreads->Columns->Add("TID", 70);
			lvThreads->Columns->Add("PID", 70);
			lvThreads->Columns->Add("CPU %", 60, HorizontalAlignment::Right);
			lvThreads->Columns->Add("Relative priority", 110);
			lvThreads->Columns->Add("State", 100);
			lvThreads->Columns->Add("Base priority", 90, HorizontalAlignment::Right);
			lvThreads->Columns->Add("CPU time", 80, HorizontalAlignment::Right);
			lvThreads->Columns->Add("Group", 60, HorizontalAlignment::Right);
			lvThreads->Columns->Add("Affinity mask", 140);

			this->Text = p->GetName() + " - properties";
			AddRow("Name", p->GetName());
			AddRow("PID", p->GetPID().ToString());
			AddRow("Full path", p->GetFullPath());
			AddRow("State", Format::State(p->GetState()));
			AddRow("Priority class", p->GetPriorityClass());
			AddRow("Owner name", p->GetOwnerName());
			AddRow("SID", p->GetOwnerSid());
			AddRow("Cpu time", Format::Time(p->GetCpuTime()));
			AddRow("Threads", p->GetThreadCount().ToString());
			AddRow("Working Set", Format::Kb(p->GetWorkingSet()));
			AddRow("Virtual Size", Format::Kb(p->GetVirtualSize()));
			AddRow("Private Bytes", Format::Kb(p->GetPrivateBytes()));

			LoadThreads();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ProcessDetailsForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::SplitContainer^ splitContainer1;
	private: System::Windows::Forms::ListView^ lvDetails;
	private: System::Windows::Forms::ListView^ lvThreads;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	private: ThreadService^ threadService;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker1;
	private: int pid;

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->lvDetails = (gcnew System::Windows::Forms::ListView());
			this->lvThreads = (gcnew System::Windows::Forms::ListView());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->lvDetails);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->lvThreads);
			this->splitContainer1->Size = System::Drawing::Size(884, 611);
			this->splitContainer1->SplitterDistance = 294;
			this->splitContainer1->TabIndex = 0;
			// 
			// lvDetails
			// 
			this->lvDetails->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lvDetails->FullRowSelect = true;
			this->lvDetails->HideSelection = false;
			this->lvDetails->Location = System::Drawing::Point(0, 0);
			this->lvDetails->Name = L"lvDetails";
			this->lvDetails->Size = System::Drawing::Size(884, 294);
			this->lvDetails->TabIndex = 0;
			this->lvDetails->UseCompatibleStateImageBehavior = false;
			this->lvDetails->View = System::Windows::Forms::View::Details;
			// 
			// lvThreads
			// 
			this->lvThreads->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lvThreads->FullRowSelect = true;
			this->lvThreads->HideSelection = false;
			this->lvThreads->Location = System::Drawing::Point(0, 0);
			this->lvThreads->Name = L"lvThreads";
			this->lvThreads->Size = System::Drawing::Size(884, 313);
			this->lvThreads->TabIndex = 0;
			this->lvThreads->UseCompatibleStateImageBehavior = false;
			this->lvThreads->View = System::Windows::Forms::View::Details;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &ProcessDetailsForm::timer1_Tick);
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Location = System::Drawing::Point(15, 0);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(200, 20);
			this->dateTimePicker1->TabIndex = 1;
			// 
			// ProcessDetailsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(884, 611);
			this->Controls->Add(this->dateTimePicker1);
			this->Controls->Add(this->splitContainer1);
			this->Name = L"ProcessDetailsForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Process Propetries";
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

		void AddRow(String^ name, String^ value)
		{
			ListViewItem^ it = gcnew ListViewItem(name);
			it->SubItems->Add(value);
			lvDetails->Items->Add(it);
		}

		void LoadThreads()
		{
			lvThreads->BeginUpdate();
			lvThreads->Items->Clear();

			for each (ThreadInfo ^ t in threadService->GetThreads(pid))
			{
				ListViewItem^ it = gcnew ListViewItem(t->GetTid().ToString());
				it->SubItems->Add(t->GetOwnerPID().ToString());
				it->SubItems->Add(t->GetCpuPercent().ToString("00"));
				it->SubItems->Add(t->GetRelativePriority());
				it->SubItems->Add(Format::State(t->GetState()));
				it->SubItems->Add(t->GetBasePriority().ToString());
				it->SubItems->Add(Format::Time(t->GetCpuTime()));
				it->SubItems->Add(t->GetGroup().ToString());
				it->SubItems->Add(String::Format("0x{0:X}", t->GetAffinityMask()));
				lvThreads->Items->Add(it);
			}

			lvThreads->EndUpdate();
		}

		System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) 
		{
			LoadThreads();
		}


};
}
