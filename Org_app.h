#pragma once
#include"FileHandle.h"
using namespace System::IO;



namespace PersonalOrganizer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms::DataVisualization::Charting;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for Org_app
	/// </summary>
	public ref class Org_app : public System::Windows::Forms::Form
	{
	public:
		Org_app(String^ username)
		{//constructor init
			InitializeComponent();

			Incomepnl->Hide();
			Expensepnl->Hide();
			ReportPanel->Hide();
			AcedemicPnl->Hide();
			deadlinepnl->Hide();

			this->username = username;
			this->filename = username + "_data/" + username + "_data.txt";
			this->fileAcc = username + "_data/" + username + "_Acedemic.txt";

			createDataFileUser(username);
			SetWelcomeMessage();
			//income panle
			dateTimePicker1->Value = DateTime::Now;
			dateTimePicker1->MaxDate = DateTime::Now;
			//expense pnl
			dateTimePicker2->Value = DateTime::Now;
			dateTimePicker2->MaxDate = DateTime::Now;
			
			//deadline pnl
			dateTimePicker6->Value = DateTime::Today;
			dateTimePicker6->MinDate = DateTime::Today;

			LoadDataFromFile();
			calculateTotal();
			showLimit();
			ShowLable();
			showUsed();
			loaddataGrid3();

			if (budgetWarn()) {
				MessageBox::Show("The total budget limits exceed your total income. Please adjust your limits.",
					"Budget Limit Exceeded",
					MessageBoxButtons::OK,
					MessageBoxIcon::Warning);
			}

			//
			//TODO: Add the constructor code here
			//
		}

		String^ getdata(String^ key) {
			return FileHandler::RetrieveData(filename, key);
		}
		void loaddataGrid3() {
			for (int i = 8; i <= 18; i++) {
				DateTime time = DateTime(2024, 1, 1, i, 0, 0); // Example date to create times
				String^ timeString = time.ToString("hh:mm tt");
				dataGridView3->Rows->Add(timeString);
			}
		}
		Void LoadDataFromFile()//read and store in data grid expense and income
		{
			String^ filePath = System::IO::Path::Combine(Application::StartupPath, "DataFile", filename);
			if (System::IO::File::Exists(filePath)) {
				array<String^>^ lines = System::IO::File::ReadAllLines(filePath);

				for each (String ^ line in lines)
				{
					if (line->StartsWith("INCOME"))
					{
						array<String^>^ data = line->Split(':');

						if (data->Length == 4)
						{
							String^ type = data[0]->Trim();
							String^ source = data[1]->Trim();
							String^ dateString = data[2]->Trim();
							String^ amount = data[3]->Trim();

							DateTime date;
							if (DateTime::TryParse(dateString, date)) {
								dataGridView1->Rows->Add(source, date.ToShortDateString(), amount, date);
							}
							else {
								MessageBox::Show("Error");
							}
						}
					}
					if (line->StartsWith("EXPENSE"))
					{
						array<String^>^ data = line->Split(':');

						if (data->Length == 5)
						{
							String^ type = data[0]->Trim();
							String^ category = data[1]->Trim();
							String^ dateString = data[2]->Trim();
							String^ amount = data[3]->Trim();
							String^ description = data[4]->Trim();

							DateTime date;
							if (DateTime::TryParse(dateString, date)) {
								dataGridView2->Rows->Add(category, description, date.ToShortDateString(), amount, date);
							}
							else
								MessageBox::Show("Error");
						}
					}
				}
				dataGridView1->Sort(dataGridView1->Columns[3], System::ComponentModel::ListSortDirection::Descending);
				dataGridView2->Sort(dataGridView2->Columns[4], System::ComponentModel::ListSortDirection::Descending);
			}

		}
		void calculateTotal() {
			String^ filePath = Path::Combine(Application::StartupPath, "DataFile", filename);
			if (System::IO::File::Exists(filePath)) {
				array<String^>^ lines = File::ReadAllLines(filePath);

				double totalIncome = 0;
				double totalExpenses = 0;
				double totalSave = 0;

				double foodUsed = 0;
				double entertainmentUsed = 0;
				double travelUsed = 0;
				double clothUsed = 0;
				double eduUsed = 0;
				double uniUsed = 0;
				double otherUsed = 0;

				for each (String ^ line in lines) {
					array<String^>^ data = line->Split(':');
					if (data->Length >= 4) {
						String^ dateString = data[2]->Trim();
						DateTime date;
						if (DateTime::TryParse(dateString, date)) {
							if (date.Year == DateTime::Now.Year && date.Month == DateTime::Now.Month) {
								if (line->StartsWith("INCOME")) {
									totalIncome += Convert::ToDouble(data[3]->Trim());
								}
								else if (line->StartsWith("EXPENSE")) {
									double amount = Convert::ToDouble(data[3]->Trim());
									if (data[1]->Trim() == "Food") {
										foodUsed += amount;
									}
									else if (data[1]->Trim() == "Entertainment") {
										entertainmentUsed += amount;
									}
									else if (data[1]->Trim() == "Travelling") {
										travelUsed += amount;
									}
									else if (data[1]->Trim() == "Clothing") {
										clothUsed += amount;
									}
									else if (data[1]->Trim() == "Education Equipment") {
										eduUsed += amount;
									}
									else if (data[1]->Trim() == "University fee") {
										uniUsed += amount;
									}
									else if (data[1]->Trim() == "Other") {
										otherUsed += amount;
									}
									totalExpenses += amount;
								}
							}

						}

					}
				}
				totalSave = totalIncome - totalExpenses;

				for (int i = 0; i < lines->Length; i++) {
					if (lines[i]->StartsWith("TotalInc")) {
						lines[i] = "TotalInc : " + totalIncome;
					}
					else if (lines[i]->StartsWith("TotalExp")) {
						lines[i] = "TotalExp : " + totalExpenses;
					}
					else if (lines[i]->StartsWith("TotalSavd")) {
						lines[i] = "TotalSavd : " + totalSave;
					}
					else if (lines[i]->StartsWith("FoodUsed")) {
						lines[i] = "FoodUsed : " + foodUsed;
					}
					else if (lines[i]->StartsWith("EntertainmentUsed")) {
						lines[i] = "EntertainmentUsed : " + entertainmentUsed;
					}
					else if (lines[i]->StartsWith("TravelUsed")) {
						lines[i] = "TravelUsed : " + travelUsed;
					}
					else if (lines[i]->StartsWith("ClothUsed")) {
						lines[i] = "ClothUsed : " + clothUsed;
					}
					else if (lines[i]->StartsWith("EduUsed")) {
						lines[i] = "EduUsed : " + eduUsed;
					}
					else if (lines[i]->StartsWith("UniUsed")) {
						lines[i] = "UniUsed : " + uniUsed;
					}
					else if (lines[i]->StartsWith("OtherUsed")) {
						lines[i] = "OtherUsed : " + otherUsed;
					}
				}
				File::WriteAllLines(filePath, lines);
			}
		}
		void ShowLable() {
			TotalBudget->Text = getdata("TotalInc");
			TotalSpent->Text = getdata("TotalExp");
			TotalAvail->Text = getdata("TotalSavd");
			BudgetExp->Text = getdata("TotalSavd");
			BudgetInc->Text = getdata("TotalSavd");

			double totalIncome = Convert::ToDouble(TotalBudget->Text);
			double totalExpenses = Convert::ToDouble(TotalSpent->Text);
			double totalAvailable = Convert::ToDouble(TotalAvail->Text);


			this->chart1->Series["Usage"]->Points->Clear();

			Series^ series = this->chart1->Series["Usage"];
			DataPoint^ available = gcnew DataPoint(1, totalAvailable);
			DataPoint^ used = gcnew DataPoint(0, totalExpenses);

			available->Color = System::Drawing::Color::Firebrick;
			available->LegendText = "Available";
			available->Label = "Available: #PERCENT{P0}";
			used->Color = System::Drawing::Color::FromArgb(211, 211, 211);
			used->LegendText = "Used";
			used->Label = "Used: #PERCENT{P0}";

			series->Points->Add(used);
			series->Points->Add(available);

			series->SetCustomProperty("PieStartAngle", "270");
		}
		void SetLimitText(String^ limitValue, Label^ lable) {
			if (limitValue == "0") {
				lable->Text = " / Unlimited";
			}
			else {
				lable->Text = limitValue;
			}
		}
		void showLimit() {
			SetLimitText(getdata("FoodLimit"), FoodLimit);
			SetLimitText(getdata("EntertainmentLimit"), EntertainLimit);
			SetLimitText(getdata("TravelLimit"), TravelLimit);
			SetLimitText(getdata("ClothLimit"), ClothLimit);
			SetLimitText(getdata("EduLimit"), EduLimit);
			SetLimitText(getdata("UniLimit"), UniLimitL);
			SetLimitText(getdata("OtherLimit"), OtherLimit);

		}
		void showUsed() {
			double foodUsedValue = Convert::ToDouble(getdata("FoodUsed"));
			double entUsedValue = Convert::ToDouble(getdata("EntertainmentUsed"));
			double travUsedValue = Convert::ToDouble(getdata("TravelUsed"));
			double clothUsedValue = Convert::ToDouble(getdata("ClothUsed"));
			double eduUsedValue = Convert::ToDouble(getdata("EduUsed"));
			double uniUsedValue = Convert::ToDouble(getdata("UniUsed"));
			double otherUsedValue = Convert::ToDouble(getdata("OtherUsed"));

			double foodLimitValue = Convert::ToDouble(getdata("FoodLimit"));
			double entLimitValue = Convert::ToDouble(getdata("EntertainmentLimit"));
			double travLimitValue = Convert::ToDouble(getdata("TravelLimit"));
			double clothLimitValue = Convert::ToDouble(getdata("ClothLimit"));
			double eduLimitValue = Convert::ToDouble(getdata("EduLimit"));
			double uniLimitValue = Convert::ToDouble(getdata("UniLimit"));
			double otherLimitValue = Convert::ToDouble(getdata("OtherLimit"));

			foodUsed->Text = getdata("FoodUsed");
			EntUsed->Text = getdata("EntertainmentUsed");
			TravUsed->Text = getdata("TravelUsed");
			ClothUsed->Text = getdata("ClothUsed");
			EduUsed->Text = getdata("EduUsed");
			UniUsed->Text = getdata("UniUsed");
			Oused->Text = getdata("OtherUsed");

			foodUsed->ForeColor = foodLimitValue!=0 && foodUsedValue >= foodLimitValue ? Color::Red : Color::White;
			EntUsed->ForeColor = entLimitValue != 0 && entUsedValue >= entLimitValue ? Color::Red : Color::White;
			TravUsed->ForeColor = travLimitValue != 0 && travUsedValue >= travLimitValue ? Color::Red : Color::White;
			ClothUsed->ForeColor = clothLimitValue != 0 && clothUsedValue >= clothLimitValue ? Color::Red : Color::White;
			EduUsed->ForeColor = eduLimitValue != 0 && eduUsedValue >= eduLimitValue ? Color::Red : Color::White;
			UniUsed->ForeColor = uniLimitValue != 0 && uniUsedValue >= uniLimitValue ? Color::Red : Color::White;
			Oused->ForeColor = otherLimitValue != 0 && otherUsedValue >= otherLimitValue ? Color::Red : Color::White;
		}
		bool budgetWarn() {
			double totalIncome = Convert::ToDouble(getdata("TotalInc"));
			double foodLimit = Convert::ToDouble(getdata("FoodLimit"));
			double entLimit = Convert::ToDouble(getdata("EntertainmentLimit"));
			double travelLimit = Convert::ToDouble(getdata("TravelLimit"));
			double clothLimit = Convert::ToDouble(getdata("ClothLimit"));
			double eduLimit = Convert::ToDouble(getdata("EduLimit"));
			double uniLimit = Convert::ToDouble(getdata("UniLimit"));
			double otherLimit = Convert::ToDouble(getdata("OtherLimit"));

			double totalBudgetLimit = foodLimit + entLimit + travelLimit + clothLimit + eduLimit + uniLimit + otherLimit;
			double BudgetAvailble = totalIncome - totalBudgetLimit;

			BudgetAvail->Text = ("Budget Available : " + BudgetAvailble);

			return totalBudgetLimit > totalIncome;
		}
		void ReportChart() {
			FRL_temp1->Text = "Food          : " + getdata("FoodUsed");
			FRL_temp2->Text = "Entertainment : " + getdata("EntertainmentUsed");
			FRL_temp3->Text = "Travelling    : " + getdata("TravelUsed");
			FRL_temp4->Text = "Clothing      : " + getdata("ClothUsed");
			FRL_temp5->Text = "Education     : " + getdata("EduUsed");
			FRL_temp6->Text = "University    : " + getdata("UniUsed");
			FRL_temp7->Text = "Other         : " + getdata("OtherUsed");


			chart2->Series["Category"]->Points->Clear();

			double foodUsed = Convert::ToDouble(getdata("FoodUsed"));
			double entUsed = Convert::ToDouble(getdata("EntertainmentUsed"));
			double travelUsed = Convert::ToDouble(getdata("TravelUsed"));
			double clothUsed = Convert::ToDouble(getdata("ClothUsed"));
			double eduUsed = Convert::ToDouble(getdata("EduUsed"));
			double uniUsed = Convert::ToDouble(getdata("UniUsed"));
			double otherUsed = Convert::ToDouble(getdata("OtherUsed"));
			double totalIncome = Convert::ToDouble(getdata("TotalInc"));
			
			chart2->Series["Category"]->Points->AddXY("Food", foodUsed);
			chart2->Series["Category"]->Points->AddXY("Entertainment", entUsed);
			chart2->Series["Category"]->Points->AddXY("Travel", travelUsed);
			chart2->Series["Category"]->Points->AddXY("Clothing", clothUsed);
			chart2->Series["Category"]->Points->AddXY("Education", eduUsed);
			chart2->Series["Category"]->Points->AddXY("University", uniUsed);
			chart2->Series["Category"]->Points->AddXY("Other", otherUsed);

			chart2->Series["Category"]->Points[0]->Color = System::Drawing::Color::Red;
			chart2->Series["Category"]->Points[1]->Color = System::Drawing::Color::Green;
			chart2->Series["Category"]->Points[2]->Color = System::Drawing::Color::Yellow;
			chart2->Series["Category"]->Points[3]->Color = System::Drawing::Color::DarkBlue;
			chart2->Series["Category"]->Points[4]->Color = System::Drawing::Color::Cyan;
			chart2->Series["Category"]->Points[5]->Color = System::Drawing::Color::DarkOrange;
			chart2->Series["Category"]->Points[6]->Color = System::Drawing::Color::MediumPurple;
		}
		void showChartFood() {
			double Limit = Convert::ToDouble(getdata("FoodLimit"));
			double Used = Convert::ToDouble(getdata("FoodUsed"));
			double Remaining = Limit - Used;

			if (Limit > 0) {
				FRL_temp1->Text = "Total Budget : " + Limit;
				FRL_temp3->Text = "Total Remaining : " + Remaining;
			}
			else {
				FRL_temp1->Text = "Total Budget : Not Limited";
				FRL_temp3->Text = "Total Remaining : Budget is not limited";
			}
			FRL_temp2->Text = "Total Spend : " + Used;
			FRL_temp4->Text = "";
			FRL_temp5->Text = "";
			FRL_temp6->Text = "";
			FRL_temp7->Text = "";


			chart2->Series["Category"]->Points->Clear();

			chart2->Series["Category"]->Points->AddXY("Spent", Used);
			if (Limit>0) {
				chart2->Series["Category"]->Points->AddXY("Available", Remaining);
			}
			else {
				chart2->Series["Category"]->Points->AddXY("Available",0);//0=unlimited
			}

			chart2->Series["Category"]->Points[0]->Color = System::Drawing::Color::Red;
			chart2->Series["Category"]->Points[1]->Color = System::Drawing::Color::Green;

			chart2->Titles->Clear();
			chart2->Titles->Add("Monthly Spending of Food");
		}
		void showChartEnt() {
			double Limit = Convert::ToDouble(getdata("EntertainmentLimit"));
			double Used = Convert::ToDouble(getdata("EntertainmentUsed"));
			double Remaining = Limit - Used;

			if (Limit > 0) {
				FRL_temp1->Text = "Total Budget : " + Limit;
				FRL_temp3->Text = "Total Remaining : " + Remaining;
			}
			else {
				FRL_temp1->Text = "Total Budget : Not Limited";
				FRL_temp3->Text = "Total Remaining : Budget is not limited";
			}
			FRL_temp2->Text = "Total Spend : " + Used;
			FRL_temp4->Text = "";
			FRL_temp5->Text = "";
			FRL_temp6->Text = "";
			FRL_temp7->Text = "";

			chart2->Series["Category"]->Points->Clear();

			chart2->Series["Category"]->Points->AddXY("Spent", Used);
			if (Limit > 0) {
				chart2->Series["Category"]->Points->AddXY("Available", Remaining);
			}
			else {
				chart2->Series["Category"]->Points->AddXY("Available", 0);//0=unlimited
			}

			chart2->Series["Category"]->Points[0]->Color = System::Drawing::Color::Red;
			chart2->Series["Category"]->Points[1]->Color = System::Drawing::Color::Green;

			chart2->Titles->Clear();
			chart2->Titles->Add("Monthly Spending of Entertainment");
		}
		void showChartTrv() {
			double Limit = Convert::ToDouble(getdata("TravelLimit"));
			double Used = Convert::ToDouble(getdata("TravelUsed"));
			double Remaining = Limit - Used;

			if (Limit > 0) {
				FRL_temp1->Text = "Total Budget : " + Limit;
				FRL_temp3->Text = "Total Remaining : " + Remaining;
			}
			else {
				FRL_temp1->Text = "Total Budget : Not Limited";
				FRL_temp3->Text = "Total Remaining : Budget is not limited";
			}
			FRL_temp2->Text = "Total Spend : " + Used;
			FRL_temp4->Text = "";
			FRL_temp5->Text = "";
			FRL_temp6->Text = "";
			FRL_temp7->Text = "";

			chart2->Series["Category"]->Points->Clear();

			chart2->Series["Category"]->Points->AddXY("Spent", Used);
			if (Limit > 0) {
				chart2->Series["Category"]->Points->AddXY("Available", Remaining);
			}
			else {
				chart2->Series["Category"]->Points->AddXY("Available", 0);//0=unlimited
			}

			chart2->Series["Category"]->Points[0]->Color = System::Drawing::Color::Red;
			chart2->Series["Category"]->Points[1]->Color = System::Drawing::Color::Green;

			chart2->Titles->Clear();
			chart2->Titles->Add("Monthly Spending of Travelling");
		}
		void showChartClo() {
			double Limit = Convert::ToDouble(getdata("ClothLimit"));
			double Used = Convert::ToDouble(getdata("ClothUsed"));
			double Remaining = Limit - Used;

			if (Limit > 0) {
				FRL_temp1->Text = "Total Budget : " + Limit;
				FRL_temp3->Text = "Total Remaining : " + Remaining;
			}
			else {
				FRL_temp1->Text = "Total Budget : Not Limited";
				FRL_temp3->Text = "Total Remaining : Budget is not limited";
			}
			FRL_temp2->Text = "Total Spend : " + Used;
			FRL_temp4->Text = "";
			FRL_temp5->Text = "";
			FRL_temp6->Text = "";
			FRL_temp7->Text = "";

			chart2->Series["Category"]->Points->Clear();

			chart2->Series["Category"]->Points->AddXY("Spent", Used);
			if (Limit > 0) {
				chart2->Series["Category"]->Points->AddXY("Available", Remaining);
			}
			else {
				chart2->Series["Category"]->Points->AddXY("Available", 0);//0=unlimited
			}

			chart2->Series["Category"]->Points[0]->Color = System::Drawing::Color::Red;
			chart2->Series["Category"]->Points[1]->Color = System::Drawing::Color::Green;

			chart2->Titles->Clear();
			chart2->Titles->Add("Monthly Spending of Clothing");
		}
		void showChartEdu() {
			double Limit = Convert::ToDouble(getdata("EduLimit"));
			double Used = Convert::ToDouble(getdata("EduUsed"));
			double Remaining = Limit - Used;

			if (Limit > 0) {
				FRL_temp1->Text = "Total Budget : " + Limit;
				FRL_temp3->Text = "Total Remaining : " + Remaining;
			}
			else {
				FRL_temp1->Text = "Total Budget : Not Limited";
				FRL_temp3->Text = "Total Remaining : Budget is not limited";
			}
			FRL_temp2->Text = "Total Spend : " + Used;
			FRL_temp4->Text = "";
			FRL_temp5->Text = "";
			FRL_temp6->Text = "";
			FRL_temp7->Text = "";

			chart2->Series["Category"]->Points->Clear();

			chart2->Series["Category"]->Points->AddXY("Spent", Used);
			if (Limit > 0) {
				chart2->Series["Category"]->Points->AddXY("Available", Remaining);
			}
			else {
				chart2->Series["Category"]->Points->AddXY("Available", 0);//0=unlimited
			}

			chart2->Series["Category"]->Points[0]->Color = System::Drawing::Color::Red;
			chart2->Series["Category"]->Points[1]->Color = System::Drawing::Color::Green;

			chart2->Titles->Clear();
			chart2->Titles->Add("Monthly Spending of Educartion Equipment");
		}
		void showChartUni() {
			double Limit = Convert::ToDouble(getdata("UniLimit"));
			double Used = Convert::ToDouble(getdata("UniUsed"));
			double Remaining = Limit - Used;

			if (Limit > 0) {
				FRL_temp1->Text = "Total Budget : " + Limit;
				FRL_temp3->Text = "Total Remaining : " + Remaining;
			}
			else {
				FRL_temp1->Text = "Total Budget : Not Limited";
				FRL_temp3->Text = "Total Remaining : Budget is not limited";
			}
			FRL_temp2->Text = "Total Spend : " + Used;
			FRL_temp4->Text = "";
			FRL_temp5->Text = "";
			FRL_temp6->Text = "";
			FRL_temp7->Text = "";


			chart2->Series["Category"]->Points->Clear();

			chart2->Series["Category"]->Points->AddXY("Spent", Used);
			if (Limit > 0) {
				chart2->Series["Category"]->Points->AddXY("Available", Remaining);
			}
			else {
				chart2->Series["Category"]->Points->AddXY("Available", 0);//0=unlimited
			}

			chart2->Series["Category"]->Points[0]->Color = System::Drawing::Color::Red;
			chart2->Series["Category"]->Points[1]->Color = System::Drawing::Color::Green;

			chart2->Titles->Clear();
			chart2->Titles->Add("Monthly Spending of University fee");
		}
		void showChartOther() {
			double Limit = Convert::ToDouble(getdata("OtherLimit"));
			double Used = Convert::ToDouble(getdata("OtherUsed"));
			double Remaining = Limit - Used;

			if (Limit > 0) {
				FRL_temp1->Text = "Total Budget : " + Limit;
				FRL_temp3->Text = "Total Remaining : " + Remaining;
			}
			else {
				FRL_temp1->Text = "Total Budget : Not Limited";
				FRL_temp3->Text = "Total Remaining : Budget is not limited";
			}
			FRL_temp2->Text = "Total Spend : " + Used;
			FRL_temp4->Text = "";
			FRL_temp5->Text = "";
			FRL_temp6->Text = "";
			FRL_temp7->Text = "";


			chart2->Series["Category"]->Points->Clear();

			chart2->Series["Category"]->Points->AddXY("Spent", Used);
			if (Limit > 0) {
				chart2->Series["Category"]->Points->AddXY("Available", Remaining);
			}
			else {
				chart2->Series["Category"]->Points->AddXY("Available", 0);//0=unlimited
			}

			chart2->Series["Category"]->Points[0]->Color = System::Drawing::Color::Red;
			chart2->Series["Category"]->Points[1]->Color = System::Drawing::Color::Green;

			chart2->Titles->Clear();
			chart2->Titles->Add("Monthly Spending of Other Expenses");
		}
		Void LoadDataAcedemic()//read and store in data grid acedemic
		{
			String^ filePath = System::IO::Path::Combine(Application::StartupPath, "DataFile", fileAcc);

			if (System::IO::File::Exists(filePath)) {
				List<String^>^ lines = gcnew List<String^>(System::IO::File::ReadAllLines(filePath));
				dataGridView3->Rows->Clear();
				loaddataGrid3();

				for each (String ^ line in lines)
				{
					array<String^>^ data = line->Split('|');
					if (data->Length == 4)
					{
						String^ type = data[0]->Trim(); // lecture
						String^ day = data[1]->Trim(); // day
						int row = Int32::Parse(data[2]->Trim()); //row 
						String^ subject = data[3]->Trim();

						int columnIndex = -1;
						for (int i = 0; i < dataGridView3->ColumnCount; i++) {
							if (dataGridView3->Columns[i]->HeaderText == day) {
								columnIndex = i;
								break;
							}
						}
						if (columnIndex != -1 && row >= 0 && row < dataGridView3->RowCount) {
							dataGridView3->Rows[row]->Cells[columnIndex]->Value = subject;
						}
					}
				}

			}
		}
		Void LoadDataDeadline()//read and store in data grid expense and income
		{
			String^ filePath = System::IO::Path::Combine(Application::StartupPath, "DataFile", fileAcc);
			dataGridView4->Rows->Clear();

			if (System::IO::File::Exists(filePath)) {
				array<String^>^ lines = System::IO::File::ReadAllLines(filePath);

				for each (String ^ line in lines)
				{
					if (line->StartsWith("DEADLINE"))
					{
						array<String^>^ data = line->Split('|');

						if (data->Length == 3)
						{
							String^ type = data[0]->Trim();//deadline
							String^ description = data[1]->Trim();//
							String^ dateString = data[2]->Trim();//date

							DateTime date = DateTime::Parse(dateString);
							DateTime Now = DateTime::Now;
							String^ timeR;

							TimeSpan timeRemain = date - Now;

							if (timeRemain.TotalSeconds <= 0) {
								timeR = "Deadline Passed";
							}
							else {
								timeR = String::Format("{0} days, {1} hrs, {2} mins",
									timeRemain.Days,
									timeRemain.Hours,
									timeRemain.Minutes);
							}
							dataGridView4->Rows->Add(description, date.ToString("MM/dd/yyyy hh:mm tt"), timeR);
						}
					}
				}
				dataGridView4->Sort(dataGridView4->Columns[2], System::ComponentModel::ListSortDirection::Ascending);
			}
		}
		Void LoadDataDeadlineAlert()//read and store in data grid expense and income
		{
			String^ filePath = System::IO::Path::Combine(Application::StartupPath, "DataFile", fileAcc);
			dataGridView4->Rows->Clear();

			if (System::IO::File::Exists(filePath)) {
				array<String^>^ lines = System::IO::File::ReadAllLines(filePath);
				TimeSpan LTRemain = TimeSpan::MaxValue;// so least time remain will be max
				String^ cDesc= "";//description of LTR
				bool flag = false;

				for each (String ^ line in lines)
				{
					if (line->StartsWith("DEADLINE"))
					{
						array<String^>^ data = line->Split('|');

						if (data->Length == 3)
						{
							String^ type = data[0]->Trim();//deadline
							String^ description = data[1]->Trim();//
							String^ dateString = data[2]->Trim();//date

							DateTime date = DateTime::Parse(dateString);
							DateTime Now = DateTime::Now;
							String^ timeR;

							TimeSpan timeRemain = date - Now;
							double totalSeconds = timeRemain.TotalSeconds;
							
							if (timeRemain.TotalSeconds <= 0) {
								timeR = "Deadline Passed";
							}
							else {
								timeR = String::Format("{0} days, {1} hrs, {2} mins",
									timeRemain.Days,
									timeRemain.Hours,
									timeRemain.Minutes);

								if (timeRemain < LTRemain) {
									LTRemain = timeRemain; // Update least time remaining
									cDesc = description; // Update the closest description
									flag = true;
								}
							}
							dataGridView4->Rows->Add(description,date.ToString("MM/dd/yyyy hh:mm tt"),timeR);
						}
					}
				}
				dataGridView4->Sort(dataGridView4->Columns[2], System::ComponentModel::ListSortDirection::Ascending);
				
				if (flag) { // Ensure there is an upcoming deadline
					String^ message = String::Format("Description: {0}\nTime Remaining: {1} days, {2} hrs, {3} mins",
						cDesc,
						LTRemain.Days,
						LTRemain.Hours,
						LTRemain.Minutes);

					MessageBox::Show(message, "Upcoming Deadline ", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Org_app()
		{
			if (components)
			{
				delete components;
			}
		}
	private: String^ username;
	private: String^ filename;
	private: String^ fileAcc;
	private: System::Windows::Forms::Button^ Exit;
		   
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ Welcome;
	private: System::Windows::Forms::Panel^ BudgetCal;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ Income;
	private: System::Windows::Forms::Button^ Expenses;
	private: System::Windows::Forms::Panel^ Freport;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ TotalSpent;
	private: System::Windows::Forms::Label^ TotalAvail;
	private: System::Windows::Forms::Label^ TotalBudget;
private: System::Windows::Forms::Button^ Acedemic;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ComboBox^ Monthlimit;
	private: System::Windows::Forms::TextBox^ LimitBox;
	private: System::Windows::Forms::Button^ SetBttn;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
private: System::Windows::Forms::Label^ Oused;

private: System::Windows::Forms::Label^ UniUsed;

private: System::Windows::Forms::Label^ EduUsed;

private: System::Windows::Forms::Label^ ClothUsed;

private: System::Windows::Forms::Label^ TravUsed;

private: System::Windows::Forms::Label^ EntUsed;

private: System::Windows::Forms::Label^ foodUsed;

	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label10;
private: System::Windows::Forms::Label^ OtherLimit;

private: System::Windows::Forms::Label^ UniLimitL;

private: System::Windows::Forms::Label^ EduLimit;

private: System::Windows::Forms::Label^ ClothLimit;

private: System::Windows::Forms::Label^ TravelLimit;

private: System::Windows::Forms::Label^ EntertainLimit;

private: System::Windows::Forms::Label^ FoodLimit;

	private: System::Windows::Forms::Button^ generate;
	private: System::Windows::Forms::Panel^ Incomepnl;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ AddIncomebtn;
	private: System::Windows::Forms::Label^ label26;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Label^ label27;
	private: System::Windows::Forms::TextBox^ SoruceTextB;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker1;
	private: System::Windows::Forms::Label^ label28;
	private: System::Windows::Forms::TextBox^ AmountTextB;
	private: System::Windows::Forms::Label^ label29;

private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
private: System::Windows::Forms::Panel^ Expensepnl;
private: System::Windows::Forms::TextBox^ textBox1;
private: System::Windows::Forms::DateTimePicker^ dateTimePicker2;
private: System::Windows::Forms::Label^ label30;
private: System::Windows::Forms::Label^ label31;
private: System::Windows::Forms::Label^ label32;
private: System::Windows::Forms::DataGridView^ dataGridView2;
private: System::Windows::Forms::Button^ ExpenseAdd;
private: System::Windows::Forms::Button^ button5;
private: System::Windows::Forms::Label^ label33;
private: System::Windows::Forms::ComboBox^ CategoryExp;
private: System::Windows::Forms::TextBox^ textBox2;
private: System::Windows::Forms::Label^ label34;





private: System::Windows::Forms::Label^ BudgetExp;
private: System::Windows::Forms::Label^ BudgetInc;
private: System::Windows::Forms::Label^ label36;
private: System::Windows::Forms::Label^ label35;
private: System::Windows::Forms::Label^ label37;
private: System::Windows::Forms::Label^ BudgetAvail;

private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn4;
private: System::Windows::Forms::Panel^ ReportPanel;
private: System::Windows::Forms::Button^ FRBack;



































private: System::Windows::Forms::Label^ label24;
private: System::Windows::Forms::Label^ FR_totalExp;
private: System::Windows::Forms::Label^ FRtotalSav;
private: System::Windows::Forms::Label^ FR_TotalIncome;
private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart2;
private: System::Windows::Forms::Label^ label12;
private: System::Windows::Forms::ComboBox^ FR_combo;
private: System::Windows::Forms::Label^ FRL_temp1;

private: System::Windows::Forms::Label^ FRL_temp3;
private: System::Windows::Forms::Label^ FRL_temp2;


private: System::Windows::Forms::Label^ label13;
private: System::Windows::Forms::Label^ FRL_temp4;

private: System::Windows::Forms::Label^ FRL_temp5;

private: System::Windows::Forms::Label^ FRL_temp6;

private: System::Windows::Forms::Label^ FRL_temp7;
private: System::Windows::Forms::Label^ label14;
private: System::Windows::Forms::Panel^ AcedemicPnl;


private: System::Windows::Forms::Button^ button4;

private: System::Windows::Forms::TextBox^ textBox4;
private: System::Windows::Forms::Label^ label44;



private: System::Windows::Forms::Label^ label45;
private: System::Windows::Forms::Label^ label46;

private: System::Windows::Forms::DataGridView^ dataGridView3;





private: System::Windows::Forms::Button^ button6;











private: System::Windows::Forms::Label^ label16;







private: System::Windows::Forms::Panel^ lecturepnl;


private: System::Windows::Forms::CheckBox^ Togglebttn;

private: System::Windows::Forms::Label^ label15;
private: System::Windows::Forms::Label^ lectureScheL;
private: System::Windows::Forms::Label^ DeadLineL;
private: System::Windows::Forms::Label^ label17;







private: System::Windows::Forms::Panel^ deadlinepnl;

private: System::Windows::Forms::DataGridView^ dataGridView4;
private: System::Windows::Forms::DateTimePicker^ dateTimePicker6;







private: System::Windows::Forms::TextBox^ textBox3;
private: System::Windows::Forms::Button^ button2;



private: System::Windows::Forms::Label^ label20;


private: System::Windows::Forms::Label^ label22;
private: System::Windows::Forms::Label^ label23;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn8;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn10;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn11;
private: System::Windows::Forms::ComboBox^ ACDayCombo;








private: System::Windows::Forms::ComboBox^ ACendCombo;
private: System::Windows::Forms::ComboBox^ ACstartCombo;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column7;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn5;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn6;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn7;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column6;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn9;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column8;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column9;





























private: System::ComponentModel::IContainer^ components;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Org_app::typeid));
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle8 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle7 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle9 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle12 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle13 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle10 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle11 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle14 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle15 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle16 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle17 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint1 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(50,
				50));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint2 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(80,
				25));
			this->Exit = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->Welcome = (gcnew System::Windows::Forms::Label());
			this->BudgetCal = (gcnew System::Windows::Forms::Panel());
			this->BudgetAvail = (gcnew System::Windows::Forms::Label());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->OtherLimit = (gcnew System::Windows::Forms::Label());
			this->UniLimitL = (gcnew System::Windows::Forms::Label());
			this->EduLimit = (gcnew System::Windows::Forms::Label());
			this->ClothLimit = (gcnew System::Windows::Forms::Label());
			this->TravelLimit = (gcnew System::Windows::Forms::Label());
			this->EntertainLimit = (gcnew System::Windows::Forms::Label());
			this->Oused = (gcnew System::Windows::Forms::Label());
			this->UniUsed = (gcnew System::Windows::Forms::Label());
			this->EduUsed = (gcnew System::Windows::Forms::Label());
			this->ClothUsed = (gcnew System::Windows::Forms::Label());
			this->TravUsed = (gcnew System::Windows::Forms::Label());
			this->EntUsed = (gcnew System::Windows::Forms::Label());
			this->foodUsed = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->FoodLimit = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SetBttn = (gcnew System::Windows::Forms::Button());
			this->LimitBox = (gcnew System::Windows::Forms::TextBox());
			this->Monthlimit = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->Expenses = (gcnew System::Windows::Forms::Button());
			this->Income = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Expensepnl = (gcnew System::Windows::Forms::Panel());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->BudgetExp = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->CategoryExp = (gcnew System::Windows::Forms::ComboBox());
			this->dateTimePicker2 = (gcnew System::Windows::Forms::DateTimePicker());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ExpenseAdd = (gcnew System::Windows::Forms::Button());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->ReportPanel = (gcnew System::Windows::Forms::Panel());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->FRL_temp4 = (gcnew System::Windows::Forms::Label());
			this->FRL_temp5 = (gcnew System::Windows::Forms::Label());
			this->FRL_temp6 = (gcnew System::Windows::Forms::Label());
			this->FRL_temp7 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->FR_combo = (gcnew System::Windows::Forms::ComboBox());
			this->FRL_temp1 = (gcnew System::Windows::Forms::Label());
			this->FRL_temp3 = (gcnew System::Windows::Forms::Label());
			this->FRL_temp2 = (gcnew System::Windows::Forms::Label());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->FR_totalExp = (gcnew System::Windows::Forms::Label());
			this->FRtotalSav = (gcnew System::Windows::Forms::Label());
			this->FR_TotalIncome = (gcnew System::Windows::Forms::Label());
			this->FRBack = (gcnew System::Windows::Forms::Button());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->AcedemicPnl = (gcnew System::Windows::Forms::Panel());
			this->DeadLineL = (gcnew System::Windows::Forms::Label());
			this->Togglebttn = (gcnew System::Windows::Forms::CheckBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->lectureScheL = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->deadlinepnl = (gcnew System::Windows::Forms::Panel());
			this->dataGridView4 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn11 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dateTimePicker6 = (gcnew System::Windows::Forms::DateTimePicker());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->lecturepnl = (gcnew System::Windows::Forms::Panel());
			this->ACendCombo = (gcnew System::Windows::Forms::ComboBox());
			this->ACstartCombo = (gcnew System::Windows::Forms::ComboBox());
			this->ACDayCombo = (gcnew System::Windows::Forms::ComboBox());
			this->dataGridView3 = (gcnew System::Windows::Forms::DataGridView());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->Incomepnl = (gcnew System::Windows::Forms::Panel());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->BudgetInc = (gcnew System::Windows::Forms::Label());
			this->AmountTextB = (gcnew System::Windows::Forms::TextBox());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->SoruceTextB = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->AddIncomebtn = (gcnew System::Windows::Forms::Button());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->Freport = (gcnew System::Windows::Forms::Panel());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->generate = (gcnew System::Windows::Forms::Button());
			this->TotalSpent = (gcnew System::Windows::Forms::Label());
			this->TotalAvail = (gcnew System::Windows::Forms::Label());
			this->TotalBudget = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Acedemic = (gcnew System::Windows::Forms::Button());
			this->BudgetCal->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->Expensepnl->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->ReportPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			this->AcedemicPnl->SuspendLayout();
			this->deadlinepnl->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView4))->BeginInit();
			this->lecturepnl->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->BeginInit();
			this->Incomepnl->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->Freport->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// Exit
			// 
			this->Exit->BackColor = System::Drawing::Color::Transparent;
			this->Exit->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Exit.BackgroundImage")));
			this->Exit->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Exit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Exit->FlatAppearance->BorderSize = 0;
			this->Exit->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->Exit->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Brown;
			this->Exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Exit->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->Exit->Location = System::Drawing::Point(1155, 3);
			this->Exit->Name = L"Exit";
			this->Exit->Size = System::Drawing::Size(45, 35);
			this->Exit->TabIndex = 0;
			this->Exit->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->Exit->UseVisualStyleBackColor = false;
			this->Exit->Click += gcnew System::EventHandler(this, &Org_app::Exit_Click);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Transparent;
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->button1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Brown;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->button1->Location = System::Drawing::Point(1104, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(45, 35);
			this->button1->TabIndex = 1;
			this->button1->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Org_app::button1_Click);
			// 
			// Welcome
			// 
			this->Welcome->BackColor = System::Drawing::Color::Transparent;
			this->Welcome->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Welcome->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->Welcome->Location = System::Drawing::Point(3, -2);
			this->Welcome->Name = L"Welcome";
			this->Welcome->Size = System::Drawing::Size(628, 35);
			this->Welcome->TabIndex = 2;
			this->Welcome->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// BudgetCal
			// 
			this->BudgetCal->BackColor = System::Drawing::Color::Transparent;
			this->BudgetCal->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"BudgetCal.BackgroundImage")));
			this->BudgetCal->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->BudgetCal->Controls->Add(this->BudgetAvail);
			this->BudgetCal->Controls->Add(this->label37);
			this->BudgetCal->Controls->Add(this->tableLayoutPanel1);
			this->BudgetCal->Controls->Add(this->label4);
			this->BudgetCal->Controls->Add(this->SetBttn);
			this->BudgetCal->Controls->Add(this->LimitBox);
			this->BudgetCal->Controls->Add(this->Monthlimit);
			this->BudgetCal->Controls->Add(this->label3);
			this->BudgetCal->Controls->Add(this->Expenses);
			this->BudgetCal->Controls->Add(this->Income);
			this->BudgetCal->Controls->Add(this->label1);
			this->BudgetCal->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->BudgetCal->Location = System::Drawing::Point(12, 36);
			this->BudgetCal->Name = L"BudgetCal";
			this->BudgetCal->Size = System::Drawing::Size(609, 603);
			this->BudgetCal->TabIndex = 3;
			// 
			// BudgetAvail
			// 
			this->BudgetAvail->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->BudgetAvail->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BudgetAvail->ForeColor = System::Drawing::Color::White;
			this->BudgetAvail->Location = System::Drawing::Point(27, 174);
			this->BudgetAvail->Name = L"BudgetAvail";
			this->BudgetAvail->Size = System::Drawing::Size(389, 41);
			this->BudgetAvail->TabIndex = 10;
			this->BudgetAvail->Text = L"Budget Availble :";
			this->BudgetAvail->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label37
			// 
			this->label37->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label37->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label37->ForeColor = System::Drawing::Color::White;
			this->label37->Location = System::Drawing::Point(353, 101);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(234, 32);
			this->label37->TabIndex = 9;
			this->label37->Text = L"(Enter 0 for unlimited)";
			this->label37->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				40)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				35)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel1->Controls->Add(this->OtherLimit, 2, 6);
			this->tableLayoutPanel1->Controls->Add(this->UniLimitL, 2, 5);
			this->tableLayoutPanel1->Controls->Add(this->EduLimit, 2, 4);
			this->tableLayoutPanel1->Controls->Add(this->ClothLimit, 2, 3);
			this->tableLayoutPanel1->Controls->Add(this->TravelLimit, 2, 2);
			this->tableLayoutPanel1->Controls->Add(this->EntertainLimit, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->Oused, 1, 6);
			this->tableLayoutPanel1->Controls->Add(this->UniUsed, 1, 5);
			this->tableLayoutPanel1->Controls->Add(this->EduUsed, 1, 4);
			this->tableLayoutPanel1->Controls->Add(this->ClothUsed, 1, 3);
			this->tableLayoutPanel1->Controls->Add(this->TravUsed, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->EntUsed, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->foodUsed, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->label11, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->label9, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->label5, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->label6, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->label7, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->label8, 0, 5);
			this->tableLayoutPanel1->Controls->Add(this->label10, 0, 6);
			this->tableLayoutPanel1->Controls->Add(this->FoodLimit, 2, 0);
			this->tableLayoutPanel1->ForeColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel1->Location = System::Drawing::Point(22, 277);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 7;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(565, 283);
			this->tableLayoutPanel1->TabIndex = 8;
			// 
			// OtherLimit
			// 
			this->OtherLimit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->OtherLimit->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->OtherLimit->ForeColor = System::Drawing::Color::White;
			this->OtherLimit->Location = System::Drawing::Point(426, 240);
			this->OtherLimit->Name = L"OtherLimit";
			this->OtherLimit->Size = System::Drawing::Size(136, 40);
			this->OtherLimit->TabIndex = 30;
			this->OtherLimit->Text = L"/ Unlimited";
			this->OtherLimit->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// UniLimitL
			// 
			this->UniLimitL->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->UniLimitL->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->UniLimitL->ForeColor = System::Drawing::Color::White;
			this->UniLimitL->Location = System::Drawing::Point(426, 200);
			this->UniLimitL->Name = L"UniLimitL";
			this->UniLimitL->Size = System::Drawing::Size(136, 40);
			this->UniLimitL->TabIndex = 29;
			this->UniLimitL->Text = L"/ Unlimited";
			this->UniLimitL->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// EduLimit
			// 
			this->EduLimit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->EduLimit->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->EduLimit->ForeColor = System::Drawing::Color::White;
			this->EduLimit->Location = System::Drawing::Point(426, 160);
			this->EduLimit->Name = L"EduLimit";
			this->EduLimit->Size = System::Drawing::Size(136, 40);
			this->EduLimit->TabIndex = 28;
			this->EduLimit->Text = L"/ Unlimited";
			this->EduLimit->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// ClothLimit
			// 
			this->ClothLimit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->ClothLimit->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ClothLimit->ForeColor = System::Drawing::Color::White;
			this->ClothLimit->Location = System::Drawing::Point(426, 120);
			this->ClothLimit->Name = L"ClothLimit";
			this->ClothLimit->Size = System::Drawing::Size(136, 40);
			this->ClothLimit->TabIndex = 27;
			this->ClothLimit->Text = L"/ Unlimited";
			this->ClothLimit->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// TravelLimit
			// 
			this->TravelLimit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->TravelLimit->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TravelLimit->ForeColor = System::Drawing::Color::White;
			this->TravelLimit->Location = System::Drawing::Point(426, 80);
			this->TravelLimit->Name = L"TravelLimit";
			this->TravelLimit->Size = System::Drawing::Size(136, 40);
			this->TravelLimit->TabIndex = 26;
			this->TravelLimit->Text = L"/ Unlimited";
			this->TravelLimit->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// EntertainLimit
			// 
			this->EntertainLimit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->EntertainLimit->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->EntertainLimit->ForeColor = System::Drawing::Color::White;
			this->EntertainLimit->Location = System::Drawing::Point(426, 40);
			this->EntertainLimit->Name = L"EntertainLimit";
			this->EntertainLimit->Size = System::Drawing::Size(136, 40);
			this->EntertainLimit->TabIndex = 25;
			this->EntertainLimit->Text = L"/ Unlimited";
			this->EntertainLimit->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// Oused
			// 
			this->Oused->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->Oused->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Oused->ForeColor = System::Drawing::Color::White;
			this->Oused->Location = System::Drawing::Point(229, 240);
			this->Oused->Name = L"Oused";
			this->Oused->Size = System::Drawing::Size(191, 40);
			this->Oused->TabIndex = 23;
			this->Oused->Text = L"0";
			this->Oused->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// UniUsed
			// 
			this->UniUsed->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->UniUsed->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->UniUsed->ForeColor = System::Drawing::Color::White;
			this->UniUsed->Location = System::Drawing::Point(229, 200);
			this->UniUsed->Name = L"UniUsed";
			this->UniUsed->Size = System::Drawing::Size(191, 40);
			this->UniUsed->TabIndex = 22;
			this->UniUsed->Text = L"0";
			this->UniUsed->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// EduUsed
			// 
			this->EduUsed->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->EduUsed->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->EduUsed->ForeColor = System::Drawing::Color::White;
			this->EduUsed->Location = System::Drawing::Point(229, 160);
			this->EduUsed->Name = L"EduUsed";
			this->EduUsed->Size = System::Drawing::Size(191, 40);
			this->EduUsed->TabIndex = 21;
			this->EduUsed->Text = L"0";
			this->EduUsed->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// ClothUsed
			// 
			this->ClothUsed->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->ClothUsed->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ClothUsed->ForeColor = System::Drawing::Color::White;
			this->ClothUsed->Location = System::Drawing::Point(229, 120);
			this->ClothUsed->Name = L"ClothUsed";
			this->ClothUsed->Size = System::Drawing::Size(191, 40);
			this->ClothUsed->TabIndex = 20;
			this->ClothUsed->Text = L"0";
			this->ClothUsed->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// TravUsed
			// 
			this->TravUsed->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->TravUsed->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TravUsed->ForeColor = System::Drawing::Color::White;
			this->TravUsed->Location = System::Drawing::Point(229, 80);
			this->TravUsed->Name = L"TravUsed";
			this->TravUsed->Size = System::Drawing::Size(191, 40);
			this->TravUsed->TabIndex = 19;
			this->TravUsed->Text = L"0";
			this->TravUsed->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// EntUsed
			// 
			this->EntUsed->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->EntUsed->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->EntUsed->ForeColor = System::Drawing::Color::White;
			this->EntUsed->Location = System::Drawing::Point(229, 40);
			this->EntUsed->Name = L"EntUsed";
			this->EntUsed->Size = System::Drawing::Size(191, 40);
			this->EntUsed->TabIndex = 18;
			this->EntUsed->Text = L"0";
			this->EntUsed->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// foodUsed
			// 
			this->foodUsed->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->foodUsed->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->foodUsed->ForeColor = System::Drawing::Color::White;
			this->foodUsed->Location = System::Drawing::Point(229, 0);
			this->foodUsed->Name = L"foodUsed";
			this->foodUsed->Size = System::Drawing::Size(191, 40);
			this->foodUsed->TabIndex = 17;
			this->foodUsed->Text = L"0";
			this->foodUsed->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label11
			// 
			this->label11->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(3, 120);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(220, 40);
			this->label11->TabIndex = 16;
			this->label11->Text = L"Clothing";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label9
			// 
			this->label9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(3, 80);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(220, 40);
			this->label9->TabIndex = 12;
			this->label9->Text = L"Traveling";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label5
			// 
			this->label5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(3, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(220, 40);
			this->label5->TabIndex = 8;
			this->label5->Text = L"Food";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label6
			// 
			this->label6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label6->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(3, 40);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(220, 40);
			this->label6->TabIndex = 9;
			this->label6->Text = L"Entertainment";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label7
			// 
			this->label7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label7->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(3, 160);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(220, 40);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Education eqip.";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label8
			// 
			this->label8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(3, 200);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(220, 40);
			this->label8->TabIndex = 14;
			this->label8->Text = L"University fee";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label10
			// 
			this->label10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(3, 240);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(220, 40);
			this->label10->TabIndex = 15;
			this->label10->Text = L"Other";
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FoodLimit
			// 
			this->FoodLimit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->FoodLimit->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FoodLimit->ForeColor = System::Drawing::Color::White;
			this->FoodLimit->Location = System::Drawing::Point(426, 0);
			this->FoodLimit->Name = L"FoodLimit";
			this->FoodLimit->Size = System::Drawing::Size(136, 40);
			this->FoodLimit->TabIndex = 24;
			this->FoodLimit->Text = L"/ Unlimited";
			this->FoodLimit->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(15, 235);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(585, 341);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Usage";
			this->label4->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// SetBttn
			// 
			this->SetBttn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->SetBttn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->SetBttn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->SetBttn->ForeColor = System::Drawing::Color::White;
			this->SetBttn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SetBttn.Image")));
			this->SetBttn->Location = System::Drawing::Point(496, 177);
			this->SetBttn->Name = L"SetBttn";
			this->SetBttn->Size = System::Drawing::Size(91, 38);
			this->SetBttn->TabIndex = 6;
			this->SetBttn->Text = L"Set";
			this->SetBttn->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->SetBttn->UseVisualStyleBackColor = true;
			this->SetBttn->Click += gcnew System::EventHandler(this, &Org_app::SetBttn_Click);
			// 
			// LimitBox
			// 
			this->LimitBox->BackColor = System::Drawing::Color::White;
			this->LimitBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->LimitBox->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LimitBox->Location = System::Drawing::Point(357, 135);
			this->LimitBox->Name = L"LimitBox";
			this->LimitBox->Size = System::Drawing::Size(230, 31);
			this->LimitBox->TabIndex = 5;
			this->LimitBox->TextChanged += gcnew System::EventHandler(this, &Org_app::LimitBox_TextChanged);
			// 
			// Monthlimit
			// 
			this->Monthlimit->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->Monthlimit->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->Monthlimit->ForeColor = System::Drawing::SystemColors::WindowText;
			this->Monthlimit->FormattingEnabled = true;
			this->Monthlimit->ItemHeight = 31;
			this->Monthlimit->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"Food", L"Entertainment", L"Travelling", L"Clothing",
					L"Education Equipment", L"University fee", L"Other"
			});
			this->Monthlimit->Location = System::Drawing::Point(22, 132);
			this->Monthlimit->Name = L"Monthlimit";
			this->Monthlimit->Size = System::Drawing::Size(285, 39);
			this->Monthlimit->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(16, 84);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(585, 142);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Set Montly Limit";
			// 
			// Expenses
			// 
			this->Expenses->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->Expenses->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->Expenses->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Expenses->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->Expenses->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Expenses.Image")));
			this->Expenses->Location = System::Drawing::Point(469, 18);
			this->Expenses->Name = L"Expenses";
			this->Expenses->Size = System::Drawing::Size(118, 39);
			this->Expenses->TabIndex = 2;
			this->Expenses->Text = L"Expenses";
			this->Expenses->UseVisualStyleBackColor = true;
			this->Expenses->Click += gcnew System::EventHandler(this, &Org_app::Expenses_Click);
			// 
			// Income
			// 
			this->Income->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->Income->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->Income->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Income->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->Income->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Income.Image")));
			this->Income->Location = System::Drawing::Point(345, 18);
			this->Income->Name = L"Income";
			this->Income->Size = System::Drawing::Size(118, 39);
			this->Income->TabIndex = 1;
			this->Income->Text = L"Income";
			this->Income->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->Income->UseVisualStyleBackColor = true;
			this->Income->Click += gcnew System::EventHandler(this, &Org_app::Income_Click);
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(14, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(587, 53);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Budget Tracker";
			// 
			// Expensepnl
			// 
			this->Expensepnl->BackColor = System::Drawing::Color::Black;
			this->Expensepnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Expensepnl.BackgroundImage")));
			this->Expensepnl->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Expensepnl->Controls->Add(this->label36);
			this->Expensepnl->Controls->Add(this->textBox1);
			this->Expensepnl->Controls->Add(this->button5);
			this->Expensepnl->Controls->Add(this->BudgetExp);
			this->Expensepnl->Controls->Add(this->textBox2);
			this->Expensepnl->Controls->Add(this->label34);
			this->Expensepnl->Controls->Add(this->CategoryExp);
			this->Expensepnl->Controls->Add(this->dateTimePicker2);
			this->Expensepnl->Controls->Add(this->label30);
			this->Expensepnl->Controls->Add(this->label31);
			this->Expensepnl->Controls->Add(this->label32);
			this->Expensepnl->Controls->Add(this->dataGridView2);
			this->Expensepnl->Controls->Add(this->ExpenseAdd);
			this->Expensepnl->Controls->Add(this->label33);
			this->Expensepnl->Location = System::Drawing::Point(-2, 0);
			this->Expensepnl->Name = L"Expensepnl";
			this->Expensepnl->Size = System::Drawing::Size(1201, 641);
			this->Expensepnl->TabIndex = 13;
			// 
			// label36
			// 
			this->label36->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label36->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label36->ForeColor = System::Drawing::Color::White;
			this->label36->Location = System::Drawing::Point(826, 4);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(103, 37);
			this->label36->TabIndex = 17;
			this->label36->Text = L"Budget : ";
			this->label36->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(783, 51);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(184, 38);
			this->textBox1->TabIndex = 10;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Org_app::textBox1_TextChanged);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::Transparent;
			this->button5->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button5.BackgroundImage")));
			this->button5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button5->FlatAppearance->BorderSize = 0;
			this->button5->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->button5->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Brown;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->button5->Location = System::Drawing::Point(1143, 0);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(58, 47);
			this->button5->TabIndex = 1;
			this->button5->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &Org_app::button5_Click);
			// 
			// BudgetExp
			// 
			this->BudgetExp->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->BudgetExp->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BudgetExp->ForeColor = System::Drawing::Color::White;
			this->BudgetExp->Location = System::Drawing::Point(941, 0);
			this->BudgetExp->Name = L"BudgetExp";
			this->BudgetExp->Size = System::Drawing::Size(198, 37);
			this->BudgetExp->TabIndex = 16;
			this->BudgetExp->Text = L"Budget : ";
			this->BudgetExp->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(176, 101);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(791, 38);
			this->textBox2->TabIndex = 14;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Org_app::textBox2_TextChanged);
			// 
			// label34
			// 
			this->label34->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label34->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label34->ForeColor = System::Drawing::Color::White;
			this->label34->Location = System::Drawing::Point(36, 92);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(134, 47);
			this->label34->TabIndex = 15;
			this->label34->Text = L"Description";
			this->label34->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// CategoryExp
			// 
			this->CategoryExp->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->CategoryExp->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->CategoryExp->ForeColor = System::Drawing::SystemColors::WindowText;
			this->CategoryExp->FormattingEnabled = true;
			this->CategoryExp->ItemHeight = 31;
			this->CategoryExp->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"Food", L"Entertainment", L"Travelling", L"Clothing",
					L"Education Equipment", L"University fee", L"Other"
			});
			this->CategoryExp->Location = System::Drawing::Point(176, 50);
			this->CategoryExp->Name = L"CategoryExp";
			this->CategoryExp->Size = System::Drawing::Size(273, 39);
			this->CategoryExp->TabIndex = 13;
			// 
			// dateTimePicker2
			// 
			this->dateTimePicker2->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dateTimePicker2->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dateTimePicker2->Location = System::Drawing::Point(528, 55);
			this->dateTimePicker2->MinDate = System::DateTime(2024, 9, 1, 0, 0, 0, 0);
			this->dateTimePicker2->Name = L"dateTimePicker2";
			this->dateTimePicker2->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->dateTimePicker2->Size = System::Drawing::Size(140, 34);
			this->dateTimePicker2->TabIndex = 12;
			this->dateTimePicker2->Value = System::DateTime(2024, 10, 14, 0, 0, 0, 0);
			// 
			// label30
			// 
			this->label30->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label30->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label30->ForeColor = System::Drawing::Color::White;
			this->label30->Location = System::Drawing::Point(682, 43);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(112, 47);
			this->label30->TabIndex = 11;
			this->label30->Text = L"Amount";
			this->label30->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label31
			// 
			this->label31->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label31->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label31->ForeColor = System::Drawing::Color::White;
			this->label31->Location = System::Drawing::Point(455, 47);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(94, 47);
			this->label31->TabIndex = 9;
			this->label31->Text = L"Date";
			this->label31->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label32
			// 
			this->label32->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label32->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label32->ForeColor = System::Drawing::Color::White;
			this->label32->Location = System::Drawing::Point(36, 48);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(114, 47);
			this->label32->TabIndex = 5;
			this->label32->Text = L"Category";
			this->label32->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// dataGridView2
			// 
			this->dataGridView2->AllowUserToResizeColumns = false;
			this->dataGridView2->AllowUserToResizeRows = false;
			this->dataGridView2->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView2->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->dataGridView2->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::DarkRed;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::InactiveBorder;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::Color::DarkRed;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView2->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->dataGridViewTextBoxColumn1,
					this->Column5, this->dataGridViewTextBoxColumn2, this->dataGridViewTextBoxColumn3, this->dataGridViewTextBoxColumn4
			});
			this->dataGridView2->EnableHeadersVisualStyles = false;
			this->dataGridView2->GridColor = System::Drawing::Color::Azure;
			this->dataGridView2->Location = System::Drawing::Point(16, 149);
			this->dataGridView2->MultiSelect = false;
			this->dataGridView2->Name = L"dataGridView2";
			dataGridViewCellStyle5->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle5->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle5->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle5->SelectionBackColor = System::Drawing::Color::Firebrick;
			dataGridViewCellStyle5->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle5->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView2->RowHeadersDefaultCellStyle = dataGridViewCellStyle5;
			this->dataGridView2->RowHeadersVisible = false;
			this->dataGridView2->RowHeadersWidth = 51;
			this->dataGridView2->RowTemplate->Height = 24;
			this->dataGridView2->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView2->Size = System::Drawing::Size(1170, 465);
			this->dataGridView2->StandardTab = true;
			this->dataGridView2->TabIndex = 4;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::Color::Firebrick;
			this->dataGridViewTextBoxColumn1->DefaultCellStyle = dataGridViewCellStyle2;
			this->dataGridViewTextBoxColumn1->FillWeight = 50;
			this->dataGridViewTextBoxColumn1->HeaderText = L"Category";
			this->dataGridViewTextBoxColumn1->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->ReadOnly = true;
			this->dataGridViewTextBoxColumn1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"Description";
			this->Column5->MinimumWidth = 6;
			this->Column5->Name = L"Column5";
			this->Column5->ReadOnly = true;
			this->Column5->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::Color::Firebrick;
			this->dataGridViewTextBoxColumn2->DefaultCellStyle = dataGridViewCellStyle3;
			this->dataGridViewTextBoxColumn2->FillWeight = 50;
			this->dataGridViewTextBoxColumn2->HeaderText = L"Date";
			this->dataGridViewTextBoxColumn2->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			this->dataGridViewTextBoxColumn2->ReadOnly = true;
			this->dataGridViewTextBoxColumn2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleRight;
			dataGridViewCellStyle4->SelectionBackColor = System::Drawing::Color::Firebrick;
			this->dataGridViewTextBoxColumn3->DefaultCellStyle = dataGridViewCellStyle4;
			this->dataGridViewTextBoxColumn3->FillWeight = 50;
			this->dataGridViewTextBoxColumn3->HeaderText = L"Amount";
			this->dataGridViewTextBoxColumn3->MaxInputLength = 20;
			this->dataGridViewTextBoxColumn3->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			this->dataGridViewTextBoxColumn3->ReadOnly = true;
			this->dataGridViewTextBoxColumn3->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// dataGridViewTextBoxColumn4
			// 
			this->dataGridViewTextBoxColumn4->HeaderText = L"DateTime";
			this->dataGridViewTextBoxColumn4->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn4->Name = L"dataGridViewTextBoxColumn4";
			this->dataGridViewTextBoxColumn4->ReadOnly = true;
			this->dataGridViewTextBoxColumn4->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Programmatic;
			this->dataGridViewTextBoxColumn4->Visible = false;
			// 
			// ExpenseAdd
			// 
			this->ExpenseAdd->BackColor = System::Drawing::Color::Transparent;
			this->ExpenseAdd->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->ExpenseAdd->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->ExpenseAdd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ExpenseAdd->ForeColor = System::Drawing::Color::White;
			this->ExpenseAdd->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ExpenseAdd.Image")));
			this->ExpenseAdd->Location = System::Drawing::Point(1016, 93);
			this->ExpenseAdd->Name = L"ExpenseAdd";
			this->ExpenseAdd->Size = System::Drawing::Size(132, 42);
			this->ExpenseAdd->TabIndex = 2;
			this->ExpenseAdd->Text = L"Add";
			this->ExpenseAdd->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->ExpenseAdd->UseVisualStyleBackColor = false;
			this->ExpenseAdd->Click += gcnew System::EventHandler(this, &Org_app::ExpenseAdd_Click);
			// 
			// label33
			// 
			this->label33->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label33->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label33->ForeColor = System::Drawing::Color::White;
			this->label33->Location = System::Drawing::Point(-2, -4);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(1201, 148);
			this->label33->TabIndex = 3;
			this->label33->Text = L"Expense Tracker";
			// 
			// ReportPanel
			// 
			this->ReportPanel->BackColor = System::Drawing::Color::Black;
			this->ReportPanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ReportPanel.BackgroundImage")));
			this->ReportPanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ReportPanel->Controls->Add(this->label14);
			this->ReportPanel->Controls->Add(this->FRL_temp4);
			this->ReportPanel->Controls->Add(this->FRL_temp5);
			this->ReportPanel->Controls->Add(this->FRL_temp6);
			this->ReportPanel->Controls->Add(this->FRL_temp7);
			this->ReportPanel->Controls->Add(this->label13);
			this->ReportPanel->Controls->Add(this->FR_combo);
			this->ReportPanel->Controls->Add(this->FRL_temp1);
			this->ReportPanel->Controls->Add(this->FRL_temp3);
			this->ReportPanel->Controls->Add(this->FRL_temp2);
			this->ReportPanel->Controls->Add(this->chart2);
			this->ReportPanel->Controls->Add(this->FR_totalExp);
			this->ReportPanel->Controls->Add(this->FRtotalSav);
			this->ReportPanel->Controls->Add(this->FR_TotalIncome);
			this->ReportPanel->Controls->Add(this->FRBack);
			this->ReportPanel->Controls->Add(this->label24);
			this->ReportPanel->Controls->Add(this->label12);
			this->ReportPanel->Location = System::Drawing::Point(-2, -2);
			this->ReportPanel->Name = L"ReportPanel";
			this->ReportPanel->Size = System::Drawing::Size(1201, 699);
			this->ReportPanel->TabIndex = 19;
			// 
			// label14
			// 
			this->label14->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label14->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->ForeColor = System::Drawing::Color::White;
			this->label14->Location = System::Drawing::Point(823, 213);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(380, 39);
			this->label14->TabIndex = 18;
			this->label14->Text = L"Report";
			this->label14->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// FRL_temp4
			// 
			this->FRL_temp4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->FRL_temp4->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FRL_temp4->ForeColor = System::Drawing::Color::White;
			this->FRL_temp4->Location = System::Drawing::Point(821, 515);
			this->FRL_temp4->Name = L"FRL_temp4";
			this->FRL_temp4->Size = System::Drawing::Size(380, 39);
			this->FRL_temp4->TabIndex = 17;
			this->FRL_temp4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FRL_temp5
			// 
			this->FRL_temp5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->FRL_temp5->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FRL_temp5->ForeColor = System::Drawing::Color::White;
			this->FRL_temp5->Location = System::Drawing::Point(821, 556);
			this->FRL_temp5->Name = L"FRL_temp5";
			this->FRL_temp5->Size = System::Drawing::Size(380, 39);
			this->FRL_temp5->TabIndex = 16;
			this->FRL_temp5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FRL_temp6
			// 
			this->FRL_temp6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->FRL_temp6->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FRL_temp6->ForeColor = System::Drawing::Color::White;
			this->FRL_temp6->Location = System::Drawing::Point(821, 596);
			this->FRL_temp6->Name = L"FRL_temp6";
			this->FRL_temp6->Size = System::Drawing::Size(380, 39);
			this->FRL_temp6->TabIndex = 15;
			this->FRL_temp6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FRL_temp7
			// 
			this->FRL_temp7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->FRL_temp7->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FRL_temp7->ForeColor = System::Drawing::Color::White;
			this->FRL_temp7->Location = System::Drawing::Point(821, 636);
			this->FRL_temp7->Name = L"FRL_temp7";
			this->FRL_temp7->Size = System::Drawing::Size(380, 39);
			this->FRL_temp7->TabIndex = 14;
			this->FRL_temp7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label13
			// 
			this->label13->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label13->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->ForeColor = System::Drawing::Color::White;
			this->label13->Location = System::Drawing::Point(821, 116);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(377, 39);
			this->label13->TabIndex = 13;
			this->label13->Text = L"Show by Category";
			this->label13->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FR_combo
			// 
			this->FR_combo->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->FR_combo->FormattingEnabled = true;
			this->FR_combo->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				L"Food", L"Entertainment", L"Travelling", L"Clothing",
					L"Education Equipment", L"University Fee", L"Other", L"Show All"
			});
			this->FR_combo->Location = System::Drawing::Point(824, 163);
			this->FR_combo->Name = L"FR_combo";
			this->FR_combo->Size = System::Drawing::Size(365, 39);
			this->FR_combo->TabIndex = 12;
			this->FR_combo->SelectedIndexChanged += gcnew System::EventHandler(this, &Org_app::FR_combo_SelectedIndexChanged);
			// 
			// FRL_temp1
			// 
			this->FRL_temp1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->FRL_temp1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FRL_temp1->ForeColor = System::Drawing::Color::White;
			this->FRL_temp1->Location = System::Drawing::Point(822, 393);
			this->FRL_temp1->Name = L"FRL_temp1";
			this->FRL_temp1->Size = System::Drawing::Size(380, 39);
			this->FRL_temp1->TabIndex = 11;
			this->FRL_temp1->Text = L"Category Budget";
			this->FRL_temp1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FRL_temp3
			// 
			this->FRL_temp3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->FRL_temp3->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FRL_temp3->ForeColor = System::Drawing::Color::White;
			this->FRL_temp3->Location = System::Drawing::Point(821, 473);
			this->FRL_temp3->Name = L"FRL_temp3";
			this->FRL_temp3->Size = System::Drawing::Size(380, 39);
			this->FRL_temp3->TabIndex = 10;
			this->FRL_temp3->Text = L"Category Availble";
			this->FRL_temp3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FRL_temp2
			// 
			this->FRL_temp2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->FRL_temp2->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FRL_temp2->ForeColor = System::Drawing::Color::White;
			this->FRL_temp2->Location = System::Drawing::Point(822, 433);
			this->FRL_temp2->Name = L"FRL_temp2";
			this->FRL_temp2->Size = System::Drawing::Size(380, 39);
			this->FRL_temp2->TabIndex = 9;
			this->FRL_temp2->Text = L"Category Spent";
			this->FRL_temp2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// chart2
			// 
			this->chart2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			chartArea1->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart2->Legends->Add(legend1);
			this->chart2->Location = System::Drawing::Point(6, 68);
			this->chart2->Name = L"chart2";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Bar;
			series1->IsVisibleInLegend = false;
			series1->Legend = L"Legend1";
			series1->Name = L"Category";
			this->chart2->Series->Add(series1);
			this->chart2->Size = System::Drawing::Size(815, 607);
			this->chart2->TabIndex = 7;
			this->chart2->Text = L"chart2";
			// 
			// FR_totalExp
			// 
			this->FR_totalExp->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->FR_totalExp->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FR_totalExp->ForeColor = System::Drawing::Color::White;
			this->FR_totalExp->Location = System::Drawing::Point(821, 313);
			this->FR_totalExp->Name = L"FR_totalExp";
			this->FR_totalExp->Size = System::Drawing::Size(417, 39);
			this->FR_totalExp->TabIndex = 6;
			this->FR_totalExp->Text = L"Total Expenses";
			this->FR_totalExp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FRtotalSav
			// 
			this->FRtotalSav->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->FRtotalSav->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FRtotalSav->ForeColor = System::Drawing::Color::White;
			this->FRtotalSav->Location = System::Drawing::Point(821, 352);
			this->FRtotalSav->Name = L"FRtotalSav";
			this->FRtotalSav->Size = System::Drawing::Size(380, 39);
			this->FRtotalSav->TabIndex = 5;
			this->FRtotalSav->Text = L"Total Saved";
			this->FRtotalSav->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FR_TotalIncome
			// 
			this->FR_TotalIncome->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->FR_TotalIncome->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FR_TotalIncome->ForeColor = System::Drawing::Color::White;
			this->FR_TotalIncome->Location = System::Drawing::Point(821, 271);
			this->FR_TotalIncome->Name = L"FR_TotalIncome";
			this->FR_TotalIncome->Size = System::Drawing::Size(403, 39);
			this->FR_TotalIncome->TabIndex = 4;
			this->FR_TotalIncome->Text = L"Total Income";
			this->FR_TotalIncome->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FRBack
			// 
			this->FRBack->BackColor = System::Drawing::Color::Transparent;
			this->FRBack->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FRBack.BackgroundImage")));
			this->FRBack->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->FRBack->Cursor = System::Windows::Forms::Cursors::Hand;
			this->FRBack->FlatAppearance->BorderSize = 0;
			this->FRBack->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->FRBack->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Brown;
			this->FRBack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->FRBack->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->FRBack->Location = System::Drawing::Point(1143, 0);
			this->FRBack->Name = L"FRBack";
			this->FRBack->Size = System::Drawing::Size(58, 47);
			this->FRBack->TabIndex = 1;
			this->FRBack->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->FRBack->UseVisualStyleBackColor = false;
			this->FRBack->Click += gcnew System::EventHandler(this, &Org_app::FRBack_Click);
			// 
			// label24
			// 
			this->label24->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label24->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label24->ForeColor = System::Drawing::Color::White;
			this->label24->Location = System::Drawing::Point(0, -2);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(1201, 52);
			this->label24->TabIndex = 3;
			this->label24->Text = L"Financial Report";
			this->label24->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label12
			// 
			this->label12->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label12->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->ForeColor = System::Drawing::Color::White;
			this->label12->Location = System::Drawing::Point(822, 67);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(380, 610);
			this->label12->TabIndex = 8;
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// AcedemicPnl
			// 
			this->AcedemicPnl->BackColor = System::Drawing::Color::Black;
			this->AcedemicPnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"AcedemicPnl.BackgroundImage")));
			this->AcedemicPnl->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->AcedemicPnl->Controls->Add(this->DeadLineL);
			this->AcedemicPnl->Controls->Add(this->Togglebttn);
			this->AcedemicPnl->Controls->Add(this->button4);
			this->AcedemicPnl->Controls->Add(this->lectureScheL);
			this->AcedemicPnl->Controls->Add(this->label17);
			this->AcedemicPnl->Controls->Add(this->deadlinepnl);
			this->AcedemicPnl->Controls->Add(this->lecturepnl);
			this->AcedemicPnl->Location = System::Drawing::Point(-1, 0);
			this->AcedemicPnl->Name = L"AcedemicPnl";
			this->AcedemicPnl->Size = System::Drawing::Size(1201, 706);
			this->AcedemicPnl->TabIndex = 20;
			// 
			// DeadLineL
			// 
			this->DeadLineL->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->DeadLineL->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DeadLineL->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				static_cast<System::Int32>(static_cast<System::Byte>(190)));
			this->DeadLineL->Location = System::Drawing::Point(420, 0);
			this->DeadLineL->Name = L"DeadLineL";
			this->DeadLineL->Size = System::Drawing::Size(193, 51);
			this->DeadLineL->TabIndex = 24;
			this->DeadLineL->Text = L"Deadlines";
			// 
			// Togglebttn
			// 
			this->Togglebttn->Appearance = System::Windows::Forms::Appearance::Button;
			this->Togglebttn->BackColor = System::Drawing::Color::Green;
			this->Togglebttn->Checked = true;
			this->Togglebttn->CheckState = System::Windows::Forms::CheckState::Checked;
			this->Togglebttn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Togglebttn->FlatAppearance->BorderSize = 0;
			this->Togglebttn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->Togglebttn->Location = System::Drawing::Point(286, 5);
			this->Togglebttn->Name = L"Togglebttn";
			this->Togglebttn->Size = System::Drawing::Size(72, 36);
			this->Togglebttn->TabIndex = 23;
			this->Togglebttn->Text = L"<<<";
			this->Togglebttn->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->Togglebttn->UseVisualStyleBackColor = false;
			this->Togglebttn->CheckedChanged += gcnew System::EventHandler(this, &Org_app::Togglebttn_CheckedChanged);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::Transparent;
			this->button4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button4.BackgroundImage")));
			this->button4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button4->FlatAppearance->BorderSize = 0;
			this->button4->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->button4->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Brown;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->button4->Location = System::Drawing::Point(1143, 0);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(58, 47);
			this->button4->TabIndex = 1;
			this->button4->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &Org_app::button4_Click_1);
			// 
			// lectureScheL
			// 
			this->lectureScheL->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->lectureScheL->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lectureScheL->ForeColor = System::Drawing::Color::White;
			this->lectureScheL->Location = System::Drawing::Point(0, 0);
			this->lectureScheL->Name = L"lectureScheL";
			this->lectureScheL->Size = System::Drawing::Size(294, 51);
			this->lectureScheL->TabIndex = 3;
			this->lectureScheL->Text = L"Lecture Schedule";
			// 
			// label17
			// 
			this->label17->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label17->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				static_cast<System::Int32>(static_cast<System::Byte>(190)));
			this->label17->Location = System::Drawing::Point(1, -3);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(1201, 51);
			this->label17->TabIndex = 25;
			// 
			// deadlinepnl
			// 
			this->deadlinepnl->BackColor = System::Drawing::Color::Transparent;
			this->deadlinepnl->Controls->Add(this->dataGridView4);
			this->deadlinepnl->Controls->Add(this->dateTimePicker6);
			this->deadlinepnl->Controls->Add(this->textBox3);
			this->deadlinepnl->Controls->Add(this->button2);
			this->deadlinepnl->Controls->Add(this->label20);
			this->deadlinepnl->Controls->Add(this->label22);
			this->deadlinepnl->Controls->Add(this->label23);
			this->deadlinepnl->Location = System::Drawing::Point(-2, 47);
			this->deadlinepnl->Name = L"deadlinepnl";
			this->deadlinepnl->Size = System::Drawing::Size(1200, 656);
			this->deadlinepnl->TabIndex = 24;
			// 
			// dataGridView4
			// 
			this->dataGridView4->AllowUserToDeleteRows = false;
			this->dataGridView4->AllowUserToResizeColumns = false;
			this->dataGridView4->AllowUserToResizeRows = false;
			this->dataGridView4->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView4->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->dataGridView4->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			dataGridViewCellStyle6->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle6->BackColor = System::Drawing::Color::DarkRed;
			dataGridViewCellStyle6->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle6->ForeColor = System::Drawing::SystemColors::InactiveBorder;
			dataGridViewCellStyle6->SelectionBackColor = System::Drawing::Color::DarkRed;
			dataGridViewCellStyle6->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle6->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView4->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle6;
			this->dataGridView4->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView4->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->dataGridViewTextBoxColumn8,
					this->dataGridViewTextBoxColumn10, this->dataGridViewTextBoxColumn11
			});
			this->dataGridView4->EditMode = System::Windows::Forms::DataGridViewEditMode::EditProgrammatically;
			this->dataGridView4->EnableHeadersVisualStyles = false;
			this->dataGridView4->GridColor = System::Drawing::Color::Azure;
			this->dataGridView4->Location = System::Drawing::Point(11, 149);
			this->dataGridView4->MultiSelect = false;
			this->dataGridView4->Name = L"dataGridView4";
			this->dataGridView4->ReadOnly = true;
			dataGridViewCellStyle8->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle8->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle8->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle8->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle8->SelectionBackColor = System::Drawing::Color::Firebrick;
			dataGridViewCellStyle8->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle8->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView4->RowHeadersDefaultCellStyle = dataGridViewCellStyle8;
			this->dataGridView4->RowHeadersVisible = false;
			this->dataGridView4->RowHeadersWidth = 51;
			this->dataGridView4->RowTemplate->Height = 24;
			this->dataGridView4->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView4->Size = System::Drawing::Size(1179, 477);
			this->dataGridView4->StandardTab = true;
			this->dataGridView4->TabIndex = 4;
			// 
			// dataGridViewTextBoxColumn8
			// 
			this->dataGridViewTextBoxColumn8->FillWeight = 150;
			this->dataGridViewTextBoxColumn8->HeaderText = L"Description";
			this->dataGridViewTextBoxColumn8->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn8->Name = L"dataGridViewTextBoxColumn8";
			this->dataGridViewTextBoxColumn8->ReadOnly = true;
			this->dataGridViewTextBoxColumn8->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// dataGridViewTextBoxColumn10
			// 
			this->dataGridViewTextBoxColumn10->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle7->SelectionBackColor = System::Drawing::Color::Firebrick;
			this->dataGridViewTextBoxColumn10->DefaultCellStyle = dataGridViewCellStyle7;
			this->dataGridViewTextBoxColumn10->FillWeight = 75;
			this->dataGridViewTextBoxColumn10->HeaderText = L"Dead Line";
			this->dataGridViewTextBoxColumn10->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn10->Name = L"dataGridViewTextBoxColumn10";
			this->dataGridViewTextBoxColumn10->ReadOnly = true;
			this->dataGridViewTextBoxColumn10->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// dataGridViewTextBoxColumn11
			// 
			this->dataGridViewTextBoxColumn11->FillWeight = 75;
			this->dataGridViewTextBoxColumn11->HeaderText = L"Time Remaining";
			this->dataGridViewTextBoxColumn11->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn11->Name = L"dataGridViewTextBoxColumn11";
			this->dataGridViewTextBoxColumn11->ReadOnly = true;
			this->dataGridViewTextBoxColumn11->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// dateTimePicker6
			// 
			this->dateTimePicker6->CustomFormat = L"MM/dd/yyyy  hh:mm tt";
			this->dateTimePicker6->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dateTimePicker6->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->dateTimePicker6->Location = System::Drawing::Point(156, 12);
			this->dateTimePicker6->MinDate = System::DateTime(2024, 9, 1, 0, 0, 0, 0);
			this->dateTimePicker6->Name = L"dateTimePicker6";
			this->dateTimePicker6->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->dateTimePicker6->Size = System::Drawing::Size(366, 34);
			this->dateTimePicker6->TabIndex = 21;
			this->dateTimePicker6->Value = System::DateTime(2024, 10, 14, 0, 0, 0, 0);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(156, 60);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(844, 38);
			this->textBox3->TabIndex = 14;
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Transparent;
			this->button2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->ForeColor = System::Drawing::Color::White;
			this->button2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.Image")));
			this->button2->Location = System::Drawing::Point(1014, 60);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(132, 38);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Add";
			this->button2->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Org_app::button2_Click);
			// 
			// label20
			// 
			this->label20->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label20->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label20->ForeColor = System::Drawing::Color::White;
			this->label20->Location = System::Drawing::Point(17, 6);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(120, 47);
			this->label20->TabIndex = 9;
			this->label20->Text = L"Deadline";
			this->label20->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label22
			// 
			this->label22->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label22->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label22->ForeColor = System::Drawing::Color::White;
			this->label22->Location = System::Drawing::Point(17, 49);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(143, 47);
			this->label22->TabIndex = 15;
			this->label22->Text = L"Description";
			this->label22->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label23
			// 
			this->label23->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label23->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label23->ForeColor = System::Drawing::Color::White;
			this->label23->Location = System::Drawing::Point(-1, -1);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(1201, 133);
			this->label23->TabIndex = 22;
			// 
			// lecturepnl
			// 
			this->lecturepnl->BackColor = System::Drawing::Color::Transparent;
			this->lecturepnl->Controls->Add(this->ACendCombo);
			this->lecturepnl->Controls->Add(this->ACstartCombo);
			this->lecturepnl->Controls->Add(this->ACDayCombo);
			this->lecturepnl->Controls->Add(this->dataGridView3);
			this->lecturepnl->Controls->Add(this->textBox4);
			this->lecturepnl->Controls->Add(this->button6);
			this->lecturepnl->Controls->Add(this->label16);
			this->lecturepnl->Controls->Add(this->label46);
			this->lecturepnl->Controls->Add(this->label45);
			this->lecturepnl->Controls->Add(this->label44);
			this->lecturepnl->Controls->Add(this->label15);
			this->lecturepnl->Location = System::Drawing::Point(0, 47);
			this->lecturepnl->Name = L"lecturepnl";
			this->lecturepnl->Size = System::Drawing::Size(1200, 656);
			this->lecturepnl->TabIndex = 22;
			// 
			// ACendCombo
			// 
			this->ACendCombo->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ACendCombo->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->ACendCombo->ForeColor = System::Drawing::SystemColors::WindowText;
			this->ACendCombo->FormattingEnabled = true;
			this->ACendCombo->ItemHeight = 31;
			this->ACendCombo->Items->AddRange(gcnew cli::array< System::Object^  >(11) {
				L"08:00 AM", L"09:00 AM", L"10:00 AM", L"11:00 AM",
					L"12:00 PM", L"01:00 PM", L"02:00 PM", L"03:00 PM", L"04:00 PM", L"05:00 PM", L"06:00 PM"
			});
			this->ACendCombo->Location = System::Drawing::Point(799, 9);
			this->ACendCombo->Name = L"ACendCombo";
			this->ACendCombo->Size = System::Drawing::Size(200, 39);
			this->ACendCombo->TabIndex = 26;
			// 
			// ACstartCombo
			// 
			this->ACstartCombo->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ACstartCombo->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->ACstartCombo->ForeColor = System::Drawing::SystemColors::WindowText;
			this->ACstartCombo->FormattingEnabled = true;
			this->ACstartCombo->ItemHeight = 31;
			this->ACstartCombo->Items->AddRange(gcnew cli::array< System::Object^  >(11) {
				L"08:00 AM", L"09:00 AM", L"10:00 AM", L"11:00 AM",
					L"12:00 PM", L"01:00 PM", L"02:00 PM", L"03:00 PM", L"04:00 PM", L"05:00 PM", L"06:00 PM"
			});
			this->ACstartCombo->Location = System::Drawing::Point(464, 10);
			this->ACstartCombo->Name = L"ACstartCombo";
			this->ACstartCombo->Size = System::Drawing::Size(180, 39);
			this->ACstartCombo->TabIndex = 25;
			// 
			// ACDayCombo
			// 
			this->ACDayCombo->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ACDayCombo->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->ACDayCombo->ForeColor = System::Drawing::SystemColors::WindowText;
			this->ACDayCombo->FormattingEnabled = true;
			this->ACDayCombo->ItemHeight = 31;
			this->ACDayCombo->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"Monday", L"Tuesday", L"Wednesday", L"Thursday",
					L"Friday", L"Saturday", L"Sunday"
			});
			this->ACDayCombo->Location = System::Drawing::Point(108, 9);
			this->ACDayCombo->Name = L"ACDayCombo";
			this->ACDayCombo->Size = System::Drawing::Size(212, 39);
			this->ACDayCombo->TabIndex = 24;
			// 
			// dataGridView3
			// 
			this->dataGridView3->AllowUserToDeleteRows = false;
			this->dataGridView3->AllowUserToResizeColumns = false;
			this->dataGridView3->AllowUserToResizeRows = false;
			this->dataGridView3->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView3->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCellsExceptHeaders;
			this->dataGridView3->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			dataGridViewCellStyle9->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle9->BackColor = System::Drawing::Color::DarkRed;
			dataGridViewCellStyle9->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle9->ForeColor = System::Drawing::SystemColors::InactiveBorder;
			dataGridViewCellStyle9->SelectionBackColor = System::Drawing::Color::DarkRed;
			dataGridViewCellStyle9->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle9->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView3->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle9;
			this->dataGridView3->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView3->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(8) {
				this->Column7,
					this->dataGridViewTextBoxColumn5, this->dataGridViewTextBoxColumn6, this->dataGridViewTextBoxColumn7, this->Column6, this->dataGridViewTextBoxColumn9,
					this->Column8, this->Column9
			});
			this->dataGridView3->EnableHeadersVisualStyles = false;
			this->dataGridView3->GridColor = System::Drawing::Color::Azure;
			this->dataGridView3->Location = System::Drawing::Point(15, 166);
			this->dataGridView3->MultiSelect = false;
			this->dataGridView3->Name = L"dataGridView3";
			this->dataGridView3->ReadOnly = true;
			dataGridViewCellStyle12->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle12->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle12->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle12->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle12->SelectionBackColor = System::Drawing::Color::Firebrick;
			dataGridViewCellStyle12->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle12->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView3->RowHeadersDefaultCellStyle = dataGridViewCellStyle12;
			this->dataGridView3->RowHeadersVisible = false;
			this->dataGridView3->RowHeadersWidth = 51;
			dataGridViewCellStyle13->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView3->RowsDefaultCellStyle = dataGridViewCellStyle13;
			this->dataGridView3->RowTemplate->Height = 24;
			this->dataGridView3->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView3->Size = System::Drawing::Size(1169, 435);
			this->dataGridView3->StandardTab = true;
			this->dataGridView3->TabIndex = 4;
			// 
			// Column7
			// 
			this->Column7->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Column7->FillWeight = 75;
			this->Column7->HeaderText = L"Time";
			this->Column7->MinimumWidth = 6;
			this->Column7->Name = L"Column7";
			this->Column7->ReadOnly = true;
			this->Column7->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// dataGridViewTextBoxColumn5
			// 
			this->dataGridViewTextBoxColumn5->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle10->SelectionBackColor = System::Drawing::Color::Firebrick;
			this->dataGridViewTextBoxColumn5->DefaultCellStyle = dataGridViewCellStyle10;
			this->dataGridViewTextBoxColumn5->HeaderText = L"Monday";
			this->dataGridViewTextBoxColumn5->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn5->Name = L"dataGridViewTextBoxColumn5";
			this->dataGridViewTextBoxColumn5->ReadOnly = true;
			this->dataGridViewTextBoxColumn5->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// dataGridViewTextBoxColumn6
			// 
			this->dataGridViewTextBoxColumn6->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn6->HeaderText = L"Tuesday";
			this->dataGridViewTextBoxColumn6->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn6->Name = L"dataGridViewTextBoxColumn6";
			this->dataGridViewTextBoxColumn6->ReadOnly = true;
			this->dataGridViewTextBoxColumn6->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// dataGridViewTextBoxColumn7
			// 
			this->dataGridViewTextBoxColumn7->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle11->SelectionBackColor = System::Drawing::Color::Firebrick;
			this->dataGridViewTextBoxColumn7->DefaultCellStyle = dataGridViewCellStyle11;
			this->dataGridViewTextBoxColumn7->HeaderText = L"Wednesday";
			this->dataGridViewTextBoxColumn7->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn7->Name = L"dataGridViewTextBoxColumn7";
			this->dataGridViewTextBoxColumn7->ReadOnly = true;
			this->dataGridViewTextBoxColumn7->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// Column6
			// 
			this->Column6->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Column6->HeaderText = L"Thursday";
			this->Column6->MinimumWidth = 6;
			this->Column6->Name = L"Column6";
			this->Column6->ReadOnly = true;
			this->Column6->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// dataGridViewTextBoxColumn9
			// 
			this->dataGridViewTextBoxColumn9->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn9->HeaderText = L"Friday";
			this->dataGridViewTextBoxColumn9->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn9->Name = L"dataGridViewTextBoxColumn9";
			this->dataGridViewTextBoxColumn9->ReadOnly = true;
			this->dataGridViewTextBoxColumn9->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Programmatic;
			// 
			// Column8
			// 
			this->Column8->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Column8->HeaderText = L"Saturday";
			this->Column8->MinimumWidth = 6;
			this->Column8->Name = L"Column8";
			this->Column8->ReadOnly = true;
			// 
			// Column9
			// 
			this->Column9->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Column9->HeaderText = L"Sunday";
			this->Column9->MinimumWidth = 6;
			this->Column9->Name = L"Column9";
			this->Column9->ReadOnly = true;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(108, 60);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(891, 38);
			this->textBox4->TabIndex = 14;
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &Org_app::textBox4_TextChanged);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::Color::Transparent;
			this->button6->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button6->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->ForeColor = System::Drawing::Color::White;
			this->button6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button6.Image")));
			this->button6->Location = System::Drawing::Point(1013, 55);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(132, 42);
			this->button6->TabIndex = 2;
			this->button6->Text = L"Add";
			this->button6->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &Org_app::button6_Click);
			// 
			// label16
			// 
			this->label16->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label16->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->ForeColor = System::Drawing::Color::White;
			this->label16->Location = System::Drawing::Point(336, 5);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(122, 47);
			this->label16->TabIndex = 19;
			this->label16->Text = L"Start Time";
			this->label16->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label46
			// 
			this->label46->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label46->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label46->ForeColor = System::Drawing::Color::White;
			this->label46->Location = System::Drawing::Point(16, 3);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(94, 47);
			this->label46->TabIndex = 9;
			this->label46->Text = L"Day";
			this->label46->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label45
			// 
			this->label45->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label45->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label45->ForeColor = System::Drawing::Color::White;
			this->label45->Location = System::Drawing::Point(659, 5);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(140, 47);
			this->label45->TabIndex = 11;
			this->label45->Text = L"End Time";
			this->label45->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label44
			// 
			this->label44->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label44->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label44->ForeColor = System::Drawing::Color::White;
			this->label44->Location = System::Drawing::Point(16, 59);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(98, 47);
			this->label44->TabIndex = 15;
			this->label44->Text = L"Subject";
			this->label44->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label15
			// 
			this->label15->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label15->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->ForeColor = System::Drawing::Color::White;
			this->label15->Location = System::Drawing::Point(-1, -1);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(1201, 133);
			this->label15->TabIndex = 22;
			// 
			// Incomepnl
			// 
			this->Incomepnl->BackColor = System::Drawing::Color::Black;
			this->Incomepnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Incomepnl.BackgroundImage")));
			this->Incomepnl->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Incomepnl->Controls->Add(this->label35);
			this->Incomepnl->Controls->Add(this->button3);
			this->Incomepnl->Controls->Add(this->BudgetInc);
			this->Incomepnl->Controls->Add(this->AmountTextB);
			this->Incomepnl->Controls->Add(this->dateTimePicker1);
			this->Incomepnl->Controls->Add(this->label28);
			this->Incomepnl->Controls->Add(this->label29);
			this->Incomepnl->Controls->Add(this->SoruceTextB);
			this->Incomepnl->Controls->Add(this->label27);
			this->Incomepnl->Controls->Add(this->dataGridView1);
			this->Incomepnl->Controls->Add(this->AddIncomebtn);
			this->Incomepnl->Controls->Add(this->label26);
			this->Incomepnl->Location = System::Drawing::Point(-3, -3);
			this->Incomepnl->Name = L"Incomepnl";
			this->Incomepnl->Size = System::Drawing::Size(1201, 641);
			this->Incomepnl->TabIndex = 9;
			// 
			// label35
			// 
			this->label35->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label35->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label35->ForeColor = System::Drawing::Color::White;
			this->label35->Location = System::Drawing::Point(828, 8);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(109, 37);
			this->label35->TabIndex = 18;
			this->label35->Text = L"Budget : ";
			this->label35->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::Transparent;
			this->button3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.BackgroundImage")));
			this->button3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button3->FlatAppearance->BorderSize = 0;
			this->button3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->button3->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Brown;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->button3->Location = System::Drawing::Point(1143, 0);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(58, 47);
			this->button3->TabIndex = 1;
			this->button3->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Org_app::button3_Click);
			// 
			// BudgetInc
			// 
			this->BudgetInc->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->BudgetInc->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BudgetInc->ForeColor = System::Drawing::Color::White;
			this->BudgetInc->Location = System::Drawing::Point(943, 8);
			this->BudgetInc->Name = L"BudgetInc";
			this->BudgetInc->Size = System::Drawing::Size(194, 37);
			this->BudgetInc->TabIndex = 17;
			this->BudgetInc->Text = L"Budget : ";
			this->BudgetInc->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// AmountTextB
			// 
			this->AmountTextB->Location = System::Drawing::Point(737, 53);
			this->AmountTextB->Name = L"AmountTextB";
			this->AmountTextB->Size = System::Drawing::Size(184, 38);
			this->AmountTextB->TabIndex = 10;
			this->AmountTextB->TextChanged += gcnew System::EventHandler(this, &Org_app::AmountTextB_TextChanged);
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dateTimePicker1->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dateTimePicker1->Location = System::Drawing::Point(482, 57);
			this->dateTimePicker1->MinDate = System::DateTime(2024, 9, 1, 0, 0, 0, 0);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->dateTimePicker1->Size = System::Drawing::Size(140, 34);
			this->dateTimePicker1->TabIndex = 12;
			this->dateTimePicker1->Value = System::DateTime(2024, 10, 14, 0, 0, 0, 0);
			// 
			// label28
			// 
			this->label28->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label28->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label28->ForeColor = System::Drawing::Color::White;
			this->label28->Location = System::Drawing::Point(636, 45);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(112, 47);
			this->label28->TabIndex = 11;
			this->label28->Text = L"Amount";
			this->label28->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label29
			// 
			this->label29->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label29->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label29->ForeColor = System::Drawing::Color::White;
			this->label29->Location = System::Drawing::Point(409, 49);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(94, 47);
			this->label29->TabIndex = 9;
			this->label29->Text = L"Date";
			this->label29->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// SoruceTextB
			// 
			this->SoruceTextB->Location = System::Drawing::Point(110, 54);
			this->SoruceTextB->Name = L"SoruceTextB";
			this->SoruceTextB->Size = System::Drawing::Size(295, 38);
			this->SoruceTextB->TabIndex = 6;
			// 
			// label27
			// 
			this->label27->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label27->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label27->ForeColor = System::Drawing::Color::White;
			this->label27->Location = System::Drawing::Point(10, 49);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(94, 47);
			this->label27->TabIndex = 5;
			this->label27->Text = L"Source";
			this->label27->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToResizeColumns = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->dataGridView1->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			dataGridViewCellStyle14->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle14->BackColor = System::Drawing::Color::DarkRed;
			dataGridViewCellStyle14->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle14->ForeColor = System::Drawing::SystemColors::InactiveBorder;
			dataGridViewCellStyle14->SelectionBackColor = System::Drawing::Color::DarkRed;
			dataGridViewCellStyle14->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle14->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle14;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->Column2,
					this->Column3, this->Column4, this->Column1
			});
			this->dataGridView1->EnableHeadersVisualStyles = false;
			this->dataGridView1->GridColor = System::Drawing::Color::Azure;
			this->dataGridView1->Location = System::Drawing::Point(16, 112);
			this->dataGridView1->MultiSelect = false;
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView1->Size = System::Drawing::Size(1170, 502);
			this->dataGridView1->StandardTab = true;
			this->dataGridView1->TabIndex = 4;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Org_app::dataGridView1_CellContentClick);
			// 
			// Column2
			// 
			this->Column2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle15->SelectionBackColor = System::Drawing::Color::Firebrick;
			this->Column2->DefaultCellStyle = dataGridViewCellStyle15;
			this->Column2->FillWeight = 150;
			this->Column2->HeaderText = L"Source";
			this->Column2->MinimumWidth = 6;
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			this->Column2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// Column3
			// 
			this->Column3->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle16->SelectionBackColor = System::Drawing::Color::Firebrick;
			this->Column3->DefaultCellStyle = dataGridViewCellStyle16;
			this->Column3->HeaderText = L"Date";
			this->Column3->MinimumWidth = 6;
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			this->Column3->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// Column4
			// 
			this->Column4->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle17->SelectionBackColor = System::Drawing::Color::Firebrick;
			this->Column4->DefaultCellStyle = dataGridViewCellStyle17;
			this->Column4->HeaderText = L"Amount";
			this->Column4->MinimumWidth = 6;
			this->Column4->Name = L"Column4";
			this->Column4->ReadOnly = true;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"DateTime";
			this->Column1->MinimumWidth = 6;
			this->Column1->Name = L"Column1";
			this->Column1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Programmatic;
			this->Column1->Visible = false;
			// 
			// AddIncomebtn
			// 
			this->AddIncomebtn->BackColor = System::Drawing::Color::Transparent;
			this->AddIncomebtn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->AddIncomebtn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->AddIncomebtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->AddIncomebtn->ForeColor = System::Drawing::Color::White;
			this->AddIncomebtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"AddIncomebtn.Image")));
			this->AddIncomebtn->Location = System::Drawing::Point(1050, 57);
			this->AddIncomebtn->Name = L"AddIncomebtn";
			this->AddIncomebtn->Size = System::Drawing::Size(118, 39);
			this->AddIncomebtn->TabIndex = 2;
			this->AddIncomebtn->Text = L"Add";
			this->AddIncomebtn->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->AddIncomebtn->UseVisualStyleBackColor = false;
			this->AddIncomebtn->Click += gcnew System::EventHandler(this, &Org_app::button4_Click);
			// 
			// label26
			// 
			this->label26->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label26->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label26->ForeColor = System::Drawing::Color::White;
			this->label26->Location = System::Drawing::Point(0, -2);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(1201, 102);
			this->label26->TabIndex = 3;
			this->label26->Text = L"Income Tracker";
			this->label26->Click += gcnew System::EventHandler(this, &Org_app::label26_Click);
			// 
			// Freport
			// 
			this->Freport->BackColor = System::Drawing::Color::Transparent;
			this->Freport->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Freport.BackgroundImage")));
			this->Freport->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Freport->Controls->Add(this->chart1);
			this->Freport->Controls->Add(this->generate);
			this->Freport->Controls->Add(this->TotalSpent);
			this->Freport->Controls->Add(this->TotalAvail);
			this->Freport->Controls->Add(this->TotalBudget);
			this->Freport->Controls->Add(this->label2);
			this->Freport->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->Freport->Location = System::Drawing::Point(619, 36);
			this->Freport->Name = L"Freport";
			this->Freport->Size = System::Drawing::Size(569, 603);
			this->Freport->TabIndex = 4;
			// 
			// chart1
			// 
			this->chart1->BackColor = System::Drawing::Color::Transparent;
			chartArea2->BackColor = System::Drawing::Color::Transparent;
			chartArea2->BackSecondaryColor = System::Drawing::Color::Transparent;
			chartArea2->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea2);
			legend2->BackColor = System::Drawing::Color::Transparent;
			legend2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			legend2->ForeColor = System::Drawing::Color::White;
			legend2->IsTextAutoFit = false;
			legend2->Name = L"Legend1";
			this->chart1->Legends->Add(legend2);
			this->chart1->Location = System::Drawing::Point(23, 195);
			this->chart1->Name = L"chart1";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Doughnut;
			series2->Legend = L"Legend1";
			series2->Name = L"Usage";
			dataPoint1->BackGradientStyle = System::Windows::Forms::DataVisualization::Charting::GradientStyle::None;
			dataPoint1->Color = System::Drawing::Color::Silver;
			dataPoint1->LegendText = L"Used";
			dataPoint2->Color = System::Drawing::Color::Firebrick;
			dataPoint2->LegendText = L"Availble";
			dataPoint2->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::None;
			series2->Points->Add(dataPoint1);
			series2->Points->Add(dataPoint2);
			this->chart1->Series->Add(series2);
			this->chart1->Size = System::Drawing::Size(525, 381);
			this->chart1->TabIndex = 8;
			this->chart1->Text = L"chart1";
			// 
			// generate
			// 
			this->generate->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->generate->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->generate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->generate->ForeColor = System::Drawing::Color::White;
			this->generate->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"generate.Image")));
			this->generate->Location = System::Drawing::Point(23, 119);
			this->generate->Name = L"generate";
			this->generate->Size = System::Drawing::Size(525, 52);
			this->generate->TabIndex = 7;
			this->generate->Text = L"Generate Report";
			this->generate->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->generate->UseVisualStyleBackColor = true;
			this->generate->Click += gcnew System::EventHandler(this, &Org_app::generate_Click);
			// 
			// TotalSpent
			// 
			this->TotalSpent->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->TotalSpent->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TotalSpent->ForeColor = System::Drawing::Color::White;
			this->TotalSpent->Location = System::Drawing::Point(228, 43);
			this->TotalSpent->Name = L"TotalSpent";
			this->TotalSpent->Size = System::Drawing::Size(302, 31);
			this->TotalSpent->TabIndex = 4;
			this->TotalSpent->Text = L"0";
			this->TotalSpent->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// TotalAvail
			// 
			this->TotalAvail->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->TotalAvail->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TotalAvail->ForeColor = System::Drawing::Color::White;
			this->TotalAvail->Location = System::Drawing::Point(222, 74);
			this->TotalAvail->Name = L"TotalAvail";
			this->TotalAvail->Size = System::Drawing::Size(308, 31);
			this->TotalAvail->TabIndex = 3;
			this->TotalAvail->Text = L"0";
			this->TotalAvail->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// TotalBudget
			// 
			this->TotalBudget->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->TotalBudget->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TotalBudget->ForeColor = System::Drawing::Color::White;
			this->TotalBudget->Location = System::Drawing::Point(228, 12);
			this->TotalBudget->Name = L"TotalBudget";
			this->TotalBudget->Size = System::Drawing::Size(302, 31);
			this->TotalBudget->TabIndex = 2;
			this->TotalBudget->Text = L"0";
			this->TotalBudget->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(25, 12);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(523, 104);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Total Income     : \r\nTotal Expenses  :\r\nTotal Availble    :\r\n";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// Acedemic
			// 
			this->Acedemic->BackColor = System::Drawing::Color::Transparent;
			this->Acedemic->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->Acedemic->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Snow;
			this->Acedemic->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Acedemic->ForeColor = System::Drawing::Color::White;
			this->Acedemic->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Acedemic.Image")));
			this->Acedemic->Location = System::Drawing::Point(948, 645);
			this->Acedemic->Name = L"Acedemic";
			this->Acedemic->Size = System::Drawing::Size(240, 39);
			this->Acedemic->TabIndex = 3;
			this->Acedemic->Text = L"Acedemic Schedule";
			this->Acedemic->UseVisualStyleBackColor = false;
			this->Acedemic->Click += gcnew System::EventHandler(this, &Org_app::Acedemic_Click);
			// 
			// Org_app
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 31);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1200, 700);
			this->Controls->Add(this->AcedemicPnl);
			this->Controls->Add(this->ReportPanel);
			this->Controls->Add(this->Expensepnl);
			this->Controls->Add(this->Incomepnl);
			this->Controls->Add(this->Acedemic);
			this->Controls->Add(this->BudgetCal);
			this->Controls->Add(this->Welcome);
			this->Controls->Add(this->Freport);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->Exit);
			this->DoubleBuffered = true;
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->Name = L"Org_app";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Org_app";
			this->Load += gcnew System::EventHandler(this, &Org_app::Org_app_Load);
			this->BudgetCal->ResumeLayout(false);
			this->BudgetCal->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->Expensepnl->ResumeLayout(false);
			this->Expensepnl->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->ReportPanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			this->AcedemicPnl->ResumeLayout(false);
			this->deadlinepnl->ResumeLayout(false);
			this->deadlinepnl->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView4))->EndInit();
			this->lecturepnl->ResumeLayout(false);
			this->lecturepnl->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->EndInit();
			this->Incomepnl->ResumeLayout(false);
			this->Incomepnl->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->Freport->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: private: System::Void Org_app_Load(System::Object^ sender, System::EventArgs^ e) {
		 // Call the load function here
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Exit_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
		
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		this->WindowState = FormWindowState::Minimized;
	}
	private: void SetWelcomeMessage() {
		this->Welcome->Text = "Welcome " + username;
}

private: System::Void Income_Click(System::Object^ sender, System::EventArgs^ e) {
	if (budgetWarn()) {
		MessageBox::Show("This button is disabled because budget limits have been exceeded. Please adjust your limits.",
			"Button Disabled",
			MessageBoxButtons::OK,
			MessageBoxIcon::Warning);
		return;
	}
	Expensepnl->Hide();
	Incomepnl->Show();
	
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	Incomepnl->Hide();
	Expensepnl->Hide();
}
private: System::Void label26_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ filePath = Path::Combine(Application::StartupPath, "DataFile", filename);
	String^ source = SoruceTextB->Text;
	String^ Amount = AmountTextB->Text;
	DateTime date = dateTimePicker1->Value;

	if(SoruceTextB->Text == "" || AmountTextB->Text == "") {
		MessageBox::Show("Fields Cannot Be Empty", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(filePath, true);
	writer->WriteLine("INCOME : "+ source + " : " + date.ToShortDateString() + " : " + Amount);
	writer->Close();

	dataGridView1->Rows->Insert(0,source, date.ToShortDateString(), Amount,date);
	dataGridView1->Sort(dataGridView1->Columns[3], System::ComponentModel::ListSortDirection::Descending);

	SoruceTextB->Clear();
	AmountTextB->Clear();
	dateTimePicker1->Value = DateTime::Today;
	calculateTotal();
	ShowLable();

}
private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
}
private: System::Void AmountTextB_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	if (System::Text::RegularExpressions::Regex::IsMatch(AmountTextB->Text, "[^0-9.]"))
	{
		MessageBox::Show("Only Numbers are accepeted.");
		AmountTextB->Text = "";
	}
}
private: System::Void Expenses_Click(System::Object^ sender, System::EventArgs^ e) {
	if (budgetWarn()) {
		MessageBox::Show("This button is disabled because budget limits have been exceeded. Please adjust your limits.",
			"Button Disabled",
			MessageBoxButtons::OK,
			MessageBoxIcon::Warning);
		return;
	}
	Incomepnl->Hide();
	Expensepnl->Show();
	
}
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	Expensepnl->Hide();
	Incomepnl->Hide();
}
private: System::Void ExpenseAdd_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ filePath = Path::Combine(Application::StartupPath, "DataFile", filename);
	String^ category = CategoryExp->Text;
	String^ Amount = textBox1->Text;
	String^ description = textBox2->Text;
	DateTime date = dateTimePicker2->Value;
	Double AvailbleT = Convert::ToDouble(TotalAvail->Text);
	Double Amnt = Convert::ToDouble(Amount);

	if (CategoryExp->Text == "" || textBox1->Text == "" || textBox2->Text == "") {
		MessageBox::Show("Fields Cannot Be Empty", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	if (AvailbleT <= Amnt){
		MessageBox::Show("Not Enough Budget Availble", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}
	System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(filePath, true);
	writer->WriteLine("EXPENSE : " + category  + " : " + date.ToShortDateString() + " : " + Amount + " : " + description);
	writer->Close();

	dataGridView2->Rows->Insert(0, category, description, date.ToShortDateString(), Amount, date);
	dataGridView2->Sort(dataGridView2->Columns[4], System::ComponentModel::ListSortDirection::Descending);
	dateTimePicker2->Value = DateTime::Today;
	textBox1->Clear();
	textBox2->Clear();
	CategoryExp->SelectedIndex = -1;
	
	calculateTotal();
	showUsed();
	ShowLable();
	
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	if (System::Text::RegularExpressions::Regex::IsMatch(textBox1->Text, "[^0-9.]"))
	{
		MessageBox::Show("Only Numbers are accepeted.");
		textBox1->Text = "";
	}
}

private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	textBox2->MaxLength = 50;
	if (textBox2->Text->Length >= 50) {
		MessageBox::Show("Description cannot exceed 50 charcters");
	}
}
private: System::Void SetBttn_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ filePath = Path::Combine(Application::StartupPath, "DataFile", filename);
	String^ Limit = LimitBox->Text;
	String^ Category = Monthlimit->Text;
	if (Limit == "" || Monthlimit->Text == "") {
		MessageBox::Show("Fields Cannot be empty");
		return;
	}
	if (System::IO::File::Exists(filePath)) {
		array<String^>^ lines = File::ReadAllLines(filePath);
		for (int i = 0; i < lines->Length; i++) {
			if (Category == "Food" && lines[i]->StartsWith("FoodLimit")) {
				lines[i] = "FoodLimit : " + Limit;
				}
				else if (Category == "Entertainment" && lines[i]->StartsWith("EntertainmentLimit")) {
					lines[i] = "EntertainmentLimit : " + Limit;
				}
				else if (Category == "Travelling" && lines[i]->StartsWith("TravelLimit")) {
					lines[i] = "TravelLimit : " + Limit;
				}
				else if (Category == "Clothing" && lines[i]->StartsWith("ClothLimit")) {
					lines[i] = "ClothLimit : " + Limit;
				}
				else if (Category == "Education Equipment" && lines[i]->StartsWith("EduLimit")) {
					lines[i] = "EduLimit : " + Limit;
				}
				else if (Category == "University fee" && lines[i]->StartsWith("UniLimit")) {
					lines[i] = "UniLimit : " + Limit;
				}
				else if (Category == "Other" && lines[i]->StartsWith("OtherLimit")) {
					lines[i] = "OtherLimit : " + Limit;
				}
			}
		File::WriteAllLines(filePath, lines);
	}
	if (budgetWarn()) {
		MessageBox::Show("The total budget limits exceed your total income. Please adjust your limits.",
			"Budget Limit Exceeded",
			MessageBoxButtons::OK,
			MessageBoxIcon::Warning);
	}
	LimitBox->Clear();
	Monthlimit->SelectedIndex = -1;
	showLimit();
	showUsed();
}
private: System::Void LimitBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	if (System::Text::RegularExpressions::Regex::IsMatch(LimitBox->Text, "[^0-9.]"))
	{
		MessageBox::Show("Only Numbers are accepeted.");
		LimitBox->Text = "";
	}
}
private: System::Void FRBack_Click(System::Object^ sender, System::EventArgs^ e) {
	ReportPanel->Hide();
}
private: System::Void generate_Click(System::Object^ sender, System::EventArgs^ e) {
	if (budgetWarn()) {
		MessageBox::Show("This button is disabled because budget limits have been exceeded. Please adjust your limits.",
		"Button Disabled",MessageBoxButtons::OK,MessageBoxIcon::Warning);
		return;
	}
	ReportPanel->Show();
	FR_TotalIncome->Text = "Total Income : " + getdata("TotalInc");
	FR_totalExp->Text = "Total Expenses : " + getdata("TotalExp");
	FRtotalSav->Text = "Total Saved : " + getdata("TotalSavd");
	FR_combo->SelectedIndex = 7;
	ReportChart();
}
private: System::Void FR_combo_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	String^ selectedCategory = FR_combo->SelectedItem->ToString();
	if (selectedCategory == "Food") {
		showChartFood();
	}
	else if (selectedCategory == "Entertainment") {
		showChartEnt();
	}
	else if (selectedCategory == "Travelling") {
		showChartTrv();
	}
	else if (selectedCategory == "Clothing") {
		showChartClo();
	}
	else if (selectedCategory == "Education Equipment") {
		showChartEdu();
	}
	else if (selectedCategory == "University Fee") {
		showChartUni();
	}
	else if (selectedCategory == "Other") {
		showChartOther();
	}
	else if (selectedCategory == "Show All") {
		ReportChart();
	}
}
private: System::Void Acedemic_Click(System::Object^ sender, System::EventArgs^ e) {
	if (budgetWarn()) {
		MessageBox::Show("This button is disabled because budget limits have been exceeded. Please adjust your limits.",
			"Button Disabled",
			MessageBoxButtons::OK,
			MessageBoxIcon::Warning);
		return;
	}
	LoadDataAcedemic();
	LoadDataDeadlineAlert();
	AcedemicPnl->Show();
}
private: System::Void button4_Click_1(System::Object^ sender, System::EventArgs^ e) {
	AcedemicPnl->Hide();
}
private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ filePath = Path::Combine(Application::StartupPath, "DataFile", fileAcc);
	String^ Subject = textBox4->Text;
	String^ day = ACDayCombo->Text;
	String^ Stime = ACstartCombo->Text;
	String^ Etime = ACendCombo->Text;

	if (ACstartCombo->Text == "" || textBox4->Text == "" || ACDayCombo->Text == "" || ACendCombo->Text == "") {
		MessageBox::Show("Fields Cannot Be Empty", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	int Column = -1;
	for (int i = 0; i < dataGridView3->ColumnCount; i++) {
		if (dataGridView3->Columns[i]->HeaderText == day) {
			Column = i;
			break;
		}
	}

	if (Column == -1) {
		MessageBox::Show("Invalid day selected.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	DateTime stime = DateTime::Parse(Stime);
	DateTime etime = DateTime::Parse(Etime);
	int startRow = stime.Hour - 8; // Assuming starting at 08:00 AM
	int endRow = etime.Hour - 8;

	if (endRow <= startRow) {
		MessageBox::Show("End time must be after start time.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	List<String^>^ lines = gcnew List<String^>();
	if (System::IO::File::Exists(filePath)) {
		lines = gcnew List<String^>(System::IO::File::ReadAllLines(filePath));
	}

	// Create a list to hold updated lines
	List<String^>^ updatedLines = gcnew List<String^>();

	// Identify which lines to keep
	for each (String ^ line in lines) {
		bool flag = false;
		for (int row = startRow; row < endRow; row++) {
			String^ key = "LECTURE | " + day + " | " + row;
			if (line->StartsWith(key)) {
				flag = true; // Mark to remove
				break;
			}
		}
		if (!flag) {
			updatedLines->Add(line); // Keep the line if it doesn't match
		}
	}

	// Add new entries for the specified time slots
	for (int row = startRow; row < endRow; row++) {
		String^ entry = "LECTURE | " + day + " | " + row + " | " + Subject;
		updatedLines->Add(entry); // Add new entry
	}

	// Write back the updated lines to the file
	System::IO::File::WriteAllLines(filePath, updatedLines);

	LoadDataAcedemic(); // Reload data into the grid
	textBox4->Clear();
	ACstartCombo->SelectedIndex = -1;
	ACDayCombo->SelectedIndex = -1;
	ACendCombo->SelectedIndex = -1;
}


private: System::Void Togglebttn_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (this->Togglebttn->Checked) {
		this->Togglebttn->Text = "<<<";
		this->Togglebttn->BackColor = System::Drawing::Color::Green;
		DeadLineL->ForeColor = System::Drawing::Color::FromArgb(190,190,190);
		lectureScheL->ForeColor = System::Drawing::Color::White;
		deadlinepnl->Hide();
		lecturepnl->Show();

		dateTimePicker6->Value = DateTime::Today;
		textBox4->Clear();
		textBox3->Clear();
		ACDayCombo->SelectedIndex = -1;
		LoadDataAcedemic();
	}
	else {
		this->Togglebttn->Text = ">>>";
		this->Togglebttn->BackColor = System::Drawing::Color::Red;
		DeadLineL->ForeColor = System::Drawing::Color::White;
		lectureScheL->ForeColor = System::Drawing::Color::FromArgb(190, 190, 190);
		lecturepnl->Hide();
		deadlinepnl->Show();

		
		dateTimePicker6->Value = DateTime::Today;
		textBox4->Clear();
		textBox3->Clear();
		ACDayCombo->SelectedIndex = -1;
	}
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ filePath = Path::Combine(Application::StartupPath, "DataFile", fileAcc);
	String^ description =textBox3->Text;
	String^ TimeRemain;

	DateTime date = dateTimePicker6->Value;
	DateTime now = DateTime::Now;

	TimeSpan timeR = date - now;
	int days = timeR.Days;
	int Hours = timeR.Hours;
	int minutes = timeR.Minutes;

	if (timeR.TotalSeconds <= 0) {
		TimeRemain = "DeadLine Passed";

	}
	else {
		TimeRemain = String::Format("{0} days, {1} hrs, {2} mins",
			timeR.Days,
			timeR.Hours,
			timeR.Minutes);
	}

	if (textBox3->Text == "") {
		MessageBox::Show("Fields Cannot Be Empty", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(filePath, true);
	writer->WriteLine("DEADLINE | " + description + " | " + date.ToString("MM/dd/yyyy hh:mm tt"));
	writer->Close();

	dataGridView4->Rows->Insert(0, description, date.ToString("MM/dd/yyyy hh:mm tt"), TimeRemain);
	dataGridView4->Sort(dataGridView4->Columns[2], System::ComponentModel::ListSortDirection::Ascending);

	dateTimePicker6->Value = DateTime::Today;
	textBox3->Clear();
	LoadDataDeadline();
}
private: System::Void textBox4_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	textBox4->MaxLength = 20;
	if (textBox4->Text->Length >= 20) {
		MessageBox::Show("Cannot exceed 20 charcters");
		textBox4->Text = textBox4->Text->Substring(0, 20);
	}
}
};
}
