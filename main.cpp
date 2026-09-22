#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    TaskManager::MyForm^ form = gcnew TaskManager::MyForm();
    Application::Run(form);

    return 0;
}