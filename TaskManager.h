#pragma once

#include "Services/ProcessService.h"
#include "Utils/Format.h"
#include "ProcessDetailForm.h"

namespace TaskManager {

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
			service = gcnew ProcessService();
			SetupColumns();
			LoadProcess();
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
		ProcessService^ service;
	private: System::Windows::Forms::ImageList^ ImgIcons;
	private: System::Windows::Forms::ContextMenuStrip^ cmsProcess;
	private: System::Windows::Forms::ToolStripMenuItem^ showThreadsToolStripMenuItem;

	private: System::ComponentModel::IContainer^ components;
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
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lvProcesses = (gcnew System::Windows::Forms::ListView());
			this->cmsProcess = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->showThreadsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImgIcons = (gcnew System::Windows::Forms::ImageList(this->components));
			this->menuStrip1->SuspendLayout();
			this->cmsProcess->SuspendLayout();
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
			this->lvProcesses->ContextMenuStrip = this->cmsProcess;
			this->lvProcesses->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lvProcesses->FullRowSelect = true;
			this->lvProcesses->HideSelection = false;
			this->lvProcesses->Location = System::Drawing::Point(0, 24);
			this->lvProcesses->MultiSelect = false;
			this->lvProcesses->Name = L"lvProcesses";
			this->lvProcesses->Size = System::Drawing::Size(1370, 725);
			this->lvProcesses->SmallImageList = this->ImgIcons;
			this->lvProcesses->TabIndex = 2;
			this->lvProcesses->UseCompatibleStateImageBehavior = false;
			this->lvProcesses->View = System::Windows::Forms::View::Details;
			// 
			// cmsProcess
			// 
			this->cmsProcess->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->showThreadsToolStripMenuItem });
			this->cmsProcess->Name = L"cmsProcess";
			this->cmsProcess->Size = System::Drawing::Size(181, 48);
			this->cmsProcess->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::cmsProcess_Opening);
			// 
			// showThreadsToolStripMenuItem
			// 
			this->showThreadsToolStripMenuItem->Name = L"showThreadsToolStripMenuItem";
			this->showThreadsToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->showThreadsToolStripMenuItem->Text = L"Show Threads";
			this->showThreadsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::showThreadsToolStripMenuItem_Click);
			// 
			// ImgIcons
			// 
			this->ImgIcons->ColorDepth = System::Windows::Forms::ColorDepth::Depth32Bit;
			this->ImgIcons->ImageSize = System::Drawing::Size(16, 16);
			this->ImgIcons->TransparentColor = System::Drawing::Color::Transparent;
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
			this->cmsProcess->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

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

			AddCol("Name", 180, L);
			AddCol("PID", 60, L);
			AddCol("Status", 110, L);
			AddCol("Priority", 90, L);
			AddCol("User name", 90, L);
			AddCol("CPU", 45, R);
			AddCol("CPU time", 75, R);
			AddCol("Working set", 95, R);
			AddCol("Virtual size", 105, R);
			AddCol("Private bytes", 100, R);
			AddCol("Threads", 60, R);
			AddCol("SID", 200, L);
			AddCol("Path", 400, L);
		}

		String^ GetIconKey(String^ path)
		{
			if (String::IsNullOrEmpty(path))
			{
				return "default";
			}
			if (ImgIcons->Images->ContainsKey(path))
			{
				return path;
			}

			try
			{
				System::Drawing::Icon^ ic = System::Drawing::Icon::ExtractAssociatedIcon(path);
				ImgIcons->Images->Add(path, ic);
				return path;
			}
			catch (Exception^)
			{
				return "default";
			}
		}

		void LoadProcess()
		{
			lvProcesses->BeginUpdate();
			lvProcesses->Items->Clear();

			for each (ProcessInfo ^ p in service->GetProcesses())
			{
				ListViewItem^ it = gcnew ListViewItem(p->GetName());
				ImgIcons->Images->Add("default", SystemIcons::Application);
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
				it->ImageKey = GetIconKey(p->GetFullPath());
				it->Tag = p;
				lvProcesses->Items->Add(it);
			}
			lvProcesses->EndUpdate();
		}

	private:
		System::Void cmsProcess_Opening(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
		{
			Point pt = lvProcesses->PointToClient(System::Windows::Forms::Cursor::Position);
			ListViewItem^ item = lvProcesses->GetItemAt(pt.X, pt.Y);

			if (item == nullptr)
			{
				e->Cancel = true;
			}
			else
			{
				item->Selected = true;
			}
		}
		System::Void showThreadsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (lvProcesses->SelectedItems->Count == 0)
				return;

			ProcessInfo^ p = safe_cast<ProcessInfo^>(lvProcesses->SelectedItems[0]->Tag);
			ProcessDetailsForm^ details = gcnew ProcessDetailsForm(p);
			details->ShowDialog(this);
		}	
};
}
