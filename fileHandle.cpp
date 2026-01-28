#include <msclr/marshal_cppstd.h>  // For conversions between std::string and String^
#include"FileHandle.h"

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;

void createDataFile()
{
    String^ folderPath = Path::Combine(Application::StartupPath, "DataFile");

    if (!Directory::Exists(folderPath)) {
        Directory::CreateDirectory(folderPath);
    }
    System::IO::File::SetAttributes(folderPath, System::IO::FileAttributes::Hidden);
    String^ filePath = Path::Combine(folderPath, "data.txt");

    if (!File::Exists(filePath)) {
        StreamWriter^ datafile = File::CreateText(filePath);
        datafile->WriteLine("Username,password");
        datafile->WriteLine("username,password");
        datafile->Close();
    }
}

void createDataFileUser(String^ username)
{
    String^ folderPath = Path::Combine(Application::StartupPath, "DataFile",username+"_data");

    if (!Directory::Exists(folderPath)) {
        Directory::CreateDirectory(folderPath);
    }

    String^ filePath = Path::Combine(folderPath, username + "_data.txt");
    String^ fileAcc = Path::Combine(folderPath, username + "_Acedemic.txt");

    if (!File::Exists(filePath)) {
        StreamWriter^ datafile = File::CreateText(filePath);
        datafile->WriteLine("username : " + username);
        datafile->WriteLine("TotalInc : 0");
        datafile->WriteLine("TotalExp : 0");
        datafile->WriteLine("TotalSavd : 0");
        datafile->WriteLine("FoodLimit : 0");
        datafile->WriteLine("FoodUsed : 0");
        datafile->WriteLine("EntertainmentLimit : 0");
        datafile->WriteLine("EntertainmentUsed : 0");
        datafile->WriteLine("TravelLimit : 0");
        datafile->WriteLine("TravelUsed : 0");
        datafile->WriteLine("ClothLimit : 0");
        datafile->WriteLine("ClothUsed : 0");
        datafile->WriteLine("EduLimit : 0");
        datafile->WriteLine("EduUsed : 0");
        datafile->WriteLine("UniLimit : 0");
        datafile->WriteLine("UniUsed : 0");
        datafile->WriteLine("OtherLimit : 0");
        datafile->WriteLine("OtherUsed : 0");
        datafile->Close();
    }
    if (!File::Exists(fileAcc)) {
        StreamWriter^ datafile = File::CreateText(fileAcc);
        datafile->Close();
    }
}
void storeUserData(String^ username, String^ password)
{
    createDataFile();

    String^ filePath = Path::Combine(Application::StartupPath, "DataFile", "data.txt");

    StreamWriter^ datafile = gcnew StreamWriter(filePath, true);
    datafile->WriteLine(username + "," + password);
    datafile->Close();
}

bool CheckUsername(String^ username)
{
    String^ filePath = Path::Combine(Application::StartupPath, "DataFile", "data.txt");

    if (!File::Exists(filePath)) {
        return false;
    }

    StreamReader^ datafile = gcnew StreamReader(filePath);
    while (!datafile->EndOfStream) {
        String^ line = datafile->ReadLine();
        array<String^>^ userInfo = line->Split(',');

        if (userInfo->Length > 0 && userInfo[0] == username) {
            datafile->Close();
            return true;
        }
    }
    datafile->Close();
    return false;
}

bool signIn(String^ username, String^ password)
{
    String^ filePath = Path::Combine(Application::StartupPath, "DataFile", "data.txt");

    if (!File::Exists(filePath))
    {
        return false;
    }
        StreamReader^ datafile = gcnew StreamReader(filePath);
        while (!datafile->EndOfStream)
        {
            String^ line = datafile->ReadLine();
            array<String^>^ userInfo = line->Split(',');

            if (userInfo->Length == 2 && userInfo[0] == username && userInfo[1] == password)
            {
                datafile->Close();
                return true; // Valid 
            }
        }
    datafile->Close();
    return false; // Not valid
    
}
String^ FileHandler::RetrieveData(String^ fileName, String^ key) {
    String^ filePath = Path::Combine(Application::StartupPath, "DataFile",fileName);
    if (File::Exists(filePath)) {
        array<String^>^ lines = File::ReadAllLines(filePath);
        for each (String ^ line in lines) {
            if (line->StartsWith(key + " : ")) {
                return line->Substring(key->Length + 3);
            }
        }
    }
    return String::Empty;
}
