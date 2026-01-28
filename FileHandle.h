#pragma once

using namespace System;

void createDataFile();
void createDataFileUser(String^ username);
void storeUserData(String^ username, String^ password);
bool CheckUsername(String^ username);
bool signIn(String^ username, String^ password);

public ref class FileHandler {
public:
    static String^ RetrieveData(String^ fileName, String^ key);
};