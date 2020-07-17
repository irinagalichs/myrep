/*
Задана структурированная переменная со списком полей – запись хранимой
таблицы. Поля, представляющие собой строки неограниченной размерности (на-
пример, адрес), хранятся в виде указателей на динамические массивы. Структура
данных должна быть полностью динамической и увеличивать свою размерность при
заполнении. Обязательные операции – ввод, постраничный просмотр, сортировка по
любому полю, сохранение и чтение из текстового файла. Основная таблица может
использовать справочные данные, которые выбирает из соответствующих массивов
указателей на строки, помещая в основную таблицу номер строки. Справочные таб-
лицы неизменяемого вида задаются в виде статического массива указателей на
строковые константы, изменяемые справочные таблицы загружаются из того же
файла, что и основная таблица, в динамические массивы указателей и могут допол-
няться. Поля с повторяющимися значениями должны быть реализованы в виде ди-
намических массивов значений или списков.

5. Справочник склада. Товар, Изменяемый (постоянный) справочник катего-
рий товара. Количество, дата поступления, цена и процент торговой надбавки. Сор-
тировка по всем параметрам. Составление фактуры: выбор нескольких товара, коли-
чества (с уменьшением его на складе), подсчет общей суммы и торговой надбавки.
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"

#include <string>
#include <iostream>
using namespace std;
#include <sstream>
#include <fstream>
#include <cstring>
#include <wchar.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

                
char CATEGORY[9][15];  				   // массив для хранения справочной таблицы 
                                       // неизменяемого вида 
                                       
char **Category = new char*[100];      // массив для хранения справочной таблицы 
      	                               // изменяемого вида

List<WarehouseReference> directory;    // односвязный список для хранения 
                                       // основной таблицы
                                       
List<WarehouseReference> invoice;      // односвязный список для хранения 
                                       // фактуры



float price = 0;                         // подсчет цены в фактуре 
float bonusPercentage = 0;               // подсчет процента в фактуре
int count1;	                           // размер изменяемой справочной таблицы


enum  sorting {prod = 1, qt, cat, date, pr, bon};

// функция для вывода таблицы 
void SGOutput(List<WarehouseReference> &dir);
// функция для сравнения 2х дат 
bool cmp(char* dt1, char* dt2);
// сортировка 
void Sorting (sorting a); 

void __fastcall TForm1::FormActivate(TObject *Sender)     // справочная таблица 
{                                                         // неизменяемого вида
	strcpy(CATEGORY[0], "Мебель\0");
    strcpy(CATEGORY[1], "Посуда\0");
    strcpy(CATEGORY[2], "Техника\0");
    strcpy(CATEGORY[3], "Стройматериалы\0");
    strcpy(CATEGORY[4], "Освещение\0");
    strcpy(CATEGORY[5], "Косметика\0");
    strcpy(CATEGORY[6], "Продукты\0");
    strcpy(CATEGORY[7], "Химия\0");
    strcpy(CATEGORY[8], "Досуг\0");

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button9Click(TObject *Sender)
{   // загрузка справочника склада в таблицу 
    StringGrid1 -> RowCount = 1;
    directory.clear();
	int i = 0;
    char a;
    string buff;
    WarehouseReference Buff;
    int c;
    
    ifstream in ("C:\\Users\\Ирина\\Desktop\\Таблица.txt");

    in >> count1;
    in >> a;
    for (int j = 0; j < count1; j++) {
        Category[j] = new char[20];
        in.getline(Category[j], 19, '$');
        ComboBox1 -> Items -> Add(Category[j]);
    } 
    
    while (!in.eof()){  
        in.getline(Buff._product, 20, '$');
        
        in >> Buff._qty;
        in >> a;

        in.getline(Buff._category, 20, '$');
        in.getline(Buff._receiptDate, 20, '$');
       
        in >> Buff._price;
        in >> a;

        in >> Buff._bonusPercentage;
        in >> a;
        
        directory.push_back(Buff);
    }
    in.close();

    directory.pop_back();
    SGOutput(directory);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
    Panel2 -> Enabled = 1;
    Panel2 -> Visible = 1;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{   //запись в справочника склада в файл
	WarehouseReference buff;
    bool cat = false;
    
    AnsiString as1 = Edit1 -> Text;
    AnsiString as2 = Edit3 -> Text;
    AnsiString as3 = Edit4 -> Text;

    strcpy(buff._product, as1.c_str());
    strcpy(buff._category, as2.c_str());
    strcpy(buff._receiptDate, as3.c_str());
    
    buff._qty = StrToInt(Edit2 -> Text);
    buff._price = StrToFloat(Edit5 -> Text);
    buff._bonusPercentage = StrToFloat(Edit6 -> Text); 

    directory.push_back(buff);

    for (int i = 0; i < count1; i++) {
    	if (strcmp(buff._category, Category[i]) == 0) {
        	cat = true;
            break;   
        }    
    }

    for (int i = 0; i < 9; i++) {
    	if (strcmp(buff._category, CATEGORY[i]) == 0) {
        	cat = true;
            break;    
        }    
    }

    if (!cat) {
         Category[count1] = new char[20];
         strcpy(Category[count1], as2.c_str());
         count1++;
         ComboBox1 -> Items -> Add(as2.c_str());
    }

    ofstream out("C:\\Users\\Ирина\\Desktop\\Таблица.txt");
    out << count1 << '$';
    for (int i = 0; i < count1; i++) {
    	out << Category[i] << '$';    
    }

    for (int i = 0; i < directory.GetSize(); i++) {
    	out << directory[i]._product << '$'; 
        out << directory[i]._qty << '$'; 
        out << directory[i]._category << '$'; 
        out << directory[i]._receiptDate << '$'; 
        out << directory[i]._price << '$'; 
        out << directory[i]._bonusPercentage << '$'; 	
    }

    out.close();  
    
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < StringGrid1 -> ColCount; j++) {
        	StringGrid1 -> Cells[i][j] = " ";    
        }
    }
    
    StringGrid1 -> RowCount = 0; 
    SGOutput(directory);

    Edit1 -> Clear();
    Edit2 -> Clear();
    Edit3 -> Clear();
    Edit4 -> Clear();
    Edit5 -> Clear();
    Edit6 -> Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
    Label13 -> Visible = true;      //начало создания фактуры 
    Label14 -> Visible = true;
    Label15 -> Visible = true;
    Label16 -> Visible = true;
	ListBox1 -> Visible = true;
    BitBtn2 -> Visible = true;
    ListBox1 -> Items -> Clear();
    for (int i = 0; i < directory.GetSize(); i++) {
    	ListBox1 -> Items -> Add(directory[i]._product + IntToStr(directory[i]._qty));
    }
    
    for (int i = 0; i < StringGrid1 -> ColCount; i++) {
        for (int j = 0; j < StringGrid1 -> RowCount; j++) {
        	StringGrid1 -> Cells[i][j] = " ";    
        }
    }
    
    StringGrid1 -> RowCount = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListBox1DblClick(TObject *Sender){

	int i = ListBox1 -> ItemIndex;      // добавление товара в фактуру 
    int j;
    bool a = false;	

    for (j = 0; j < invoice.GetSize(); j++) {
    	if (strcmp(invoice[j]._product, directory[i]._product) == 0) {
            a = true;
        	break;    
        }    
    }
    
    if (a){
    	invoice[j]._qty++;
        directory[i]._qty--;
        if (directory[i]._qty == 0) {
        	directory.removeAt(i);    
        }
    }
    else 
    {
    	invoice.push_back(directory[i]);
        invoice[j]._qty = 1;
        directory[i]._qty--;
        StringGrid1 -> RowCount = StringGrid1 -> RowCount + 1;
        if (directory[i]._qty == 0) {
        	directory.removeAt(i);    
        }
    }

    for (int i = 0; i < invoice.GetSize(); i++){
    	StringGrid1 -> Cells[0][i] = invoice[i]._product;
        StringGrid1 -> Cells[1][i] = invoice[i]._qty;
        StringGrid1 -> Cells[2][i] = invoice[i]._category;
        StringGrid1 -> Cells[3][i] = invoice[i]._receiptDate;
        StringGrid1 -> Cells[4][i] = invoice[i]._price;
        StringGrid1 -> Cells[5][i] = invoice[i]._bonusPercentage;
    }

    
    ListBox1 -> Items -> Clear();
    for (int i = 0; i < directory.GetSize(); i++) {
    	ListBox1 -> Items -> Add(directory[i]._product + IntToStr(directory[i]._qty));
    }

    ofstream out("C:\\Users\\Ирина\\Desktop\\Таблица.txt");
    out << count1 << '$';
    for (int i = 0; i < count1; i++) {
    	out << Category[i] << '$';    
    }

    for (int i = 0; i < directory.GetSize(); i++) {
    	out << directory[i]._product << '$'; 
        out << directory[i]._qty << '$'; 
        out << directory[i]._category << '$'; 
        out << directory[i]._receiptDate << '$'; 
        out << directory[i]._price << '$'; 
        out << directory[i]._bonusPercentage << '$'; 	
    }

    out.close();
    //------процент надбавки и общая сумма-----------

    bonusPercentage = bonusPercentage + invoice[j]._bonusPercentage;
    bonusPercentage = ((price * bonusPercentage / 100) + (invoice[j]._price * invoice[j]._bonusPercentage / 100)) * 100 / (price + invoice[j]._price);
    price = price + invoice[j]._price; 
    
    Label15 -> Caption = FloatToStr(price);
    Label16 -> Caption = FloatToStr(bonusPercentage);
    
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	directory.clear();
	invoice.clear();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
	invoice.clear();                                      // завершение создания
    for (int i = 0; i < StringGrid1 -> ColCount; i++) {   // фактуры
        for (int j = 0; j < StringGrid1 -> RowCount; j++) {
        	StringGrid1 -> Cells[i][j] = " ";    
        }
    }
    
    StringGrid1 -> RowCount = 1;
    BitBtn2 -> Visible = false;
    Label13 -> Visible = false;
    Label14 -> Visible = false;
    Label15 -> Visible = false;
    Label16 -> Visible = false;
    ListBox1 -> Visible = false;
    ListBox1 -> Items -> Clear();
    //-------можно добавить еще сохранение фактуры куда-то-------------------	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label7Click(TObject *Sender)
{// сортировка по названию товара 
	Sorting(prod);		
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label8Click(TObject *Sender)
{// сортировка по количеству товара
	Sorting(qt);		
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label9Click(TObject *Sender)
{// сортировка по категории товара
    Sorting(cat);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label10Click(TObject *Sender)
{// сортировка по дате
    Sorting(date);		
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label11Click(TObject *Sender)
{// сортировка по цене товара
	Sorting(pr);	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label12Click(TObject *Sender)
{// сортировка по проценту надбавки
    Sorting(bon);	
}
//---------------------------------------------------------------------------



void Sorting (sorting a){
	switch (a) {
    	case 1:
        {
        	for (int i = 1; i < directory.GetSize(); i++){
                for (int j = 0; j < directory.GetSize() - 1; j++) {
                    if (strcmp(directory[j]._product, directory[j + 1]._product) > 0) {
                        swap(directory[j], directory[j + 1]);
                    }
                }
            }

            Form1 -> StringGrid1 -> RowCount = 1;
            SGOutput(directory);
        }
        break; 
           
        case 2:
        {
        	for (int i = 1; i < directory.GetSize(); i++){
                for (int j = 0; j < directory.GetSize() - 1; j++) {
                    if (directory[j]._qty > directory[j + 1]._qty) {
                        swap(directory[j], directory[j + 1]);
                    }
                }
            }

            Form1 -> StringGrid1 -> RowCount = 1;
            SGOutput(directory);
        }
        break;
        
        case 3:
        {
        	for (int i = 1; i < directory.GetSize(); i++){       
                for (int j = 0; j < directory.GetSize() - 1; j++) {
                    if (strcmp(directory[j]._category, directory[j + 1]._category) > 0) {
                        swap(directory[j], directory[j + 1]);
                    }
                }
            }

            Form1 -> StringGrid1 -> RowCount = 1;
            SGOutput(directory);
        }
        break;
        
        case 4:
        {
            for (int i = 1; i < directory.GetSize(); i++){
                for (int j = 0; j < directory.GetSize() - 1; j++) {
                    if (cmp(directory[j]._receiptDate, directory[j + 1]._receiptDate)) {
                        swap(directory[j], directory[j + 1]);
                    }
                }
            }

            Form1 -> StringGrid1 -> RowCount = 1;
            SGOutput(directory);	
        }
        break;
        
        case 5:
        {
            for (int i = 1; i < directory.GetSize(); i++){
                for (int j = 0; j < directory.GetSize() - 1; j++) {
                    if (directory[j]._price > directory[j + 1]._price) {
                        swap(directory[j], directory[j + 1]);
                    }
                }
            }

            Form1 -> StringGrid1 -> RowCount = 1;
            SGOutput(directory);
        }
        break;
        
        case 6:
        {
        	for (int i = 1; i < directory.GetSize(); i++){
                for (int j = 0; j < directory.GetSize() - 1; j++) {
                    if (directory[j]._bonusPercentage > directory[j + 1]._bonusPercentage) {
                        swap(directory[j], directory[j + 1]);
                    }
                }
            }

            Form1 -> StringGrid1 -> RowCount = 1;
            SGOutput(directory);
        }
        break;
        
    }
}


void SGOutput(List<WarehouseReference> &dir)
{
	for (int j = 0; j < directory.GetSize(); j++){
    	Form1 -> StringGrid1 -> RowCount = Form1 -> StringGrid1 -> RowCount + 1;
    	Form1 -> StringGrid1 -> Cells[0][j] = dir[j]._product;
        Form1 -> StringGrid1 -> Cells[1][j] = dir[j]._qty;
        Form1 -> StringGrid1 -> Cells[2][j] = dir[j]._category;
        Form1 -> StringGrid1 -> Cells[3][j] = dir[j]._receiptDate;
        Form1 -> StringGrid1 -> Cells[4][j] = dir[j]._price;
        Form1 -> StringGrid1 -> Cells[5][j] = dir[j]._bonusPercentage;
    }
    Form1 -> StringGrid1 -> RowCount = Form1 -> StringGrid1 -> RowCount - 1;
}

bool cmp(char* dt1, char* dt2)
{
    char year1[5];
    char year2[5];
    for (int i = 0; i < 4; i++) {
        year1[i] = dt1[i + 6];
        year2[i] = dt2[i + 6];	    
    }
    
    year1[4] = '\0';
    year2[4] = '\0';
    
    if (atoi(year1) > atoi(year2)){ 
    	return 1;
    }
    
    else if (atoi(year1) == atoi(year2)) {
        char mo1[3];
    	char mo2[3];
        for (int i = 0; i < 2; i++) {
            mo1[i] = dt1[i + 3];
            mo2[i] = dt2[i + 3];	    
        }

        mo1[2] = '\0';
        mo2[2] = '\0';
        
        if (atoi(mo1) > atoi(mo2)){
        	return 1;
        }  
    
        else if (atoi(mo1) == atoi(mo2)) {
            char day1[3];
            char day2[3];
            for (int i = 0; i < 2; i++) {
                day1[i] = dt1[i];
                day2[i] = dt2[i];	    
            }

            day1[2] = '\0';
        	day2[2] = '\0';
            
            if (atoi(day1) > atoi(day2)){
                return 1;
            }        
        }
    }
    return 0;
}

