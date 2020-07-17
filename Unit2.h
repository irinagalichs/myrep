//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
#include <string>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
class WarehouseReference        // класс для хранения элемента таблицы 
{
public:
	char* _product;
    int _qty;
    char* _category;
    char* _receiptDate;
    float _price;
    float _bonusPercentage;

    WarehouseReference();
    WarehouseReference(char*, int, char*, char*, float, float);
    const WarehouseReference& operator =(const WarehouseReference &obj);

    friend void swap(WarehouseReference &obj, WarehouseReference &obj1);

};

const WarehouseReference& WarehouseReference :: operator =(const WarehouseReference &obj){
    if (&obj == this) {
        return *this;           // перегруженный оператор присваивания
    }
    strcpy(this -> _product, obj._product);
    this -> _qty = obj._qty;
    strcpy(this -> _category, obj._category);                            
    strcpy(this -> _receiptDate, obj._receiptDate);
    this -> _price = obj._price;
    this -> _bonusPercentage = obj._bonusPercentage;
    
    return *this; 
}

WarehouseReference :: WarehouseReference(){    // конструктор без параметров
    _product = new char[20];
	strcpy(_product, "Стол\0");
    _qty = 1;
	_category = new char[20];
    strcpy(_category, "Мебель\0");
	_receiptDate = new char[11];
    strcpy(_receiptDate, "22.22.2020");
    _price = 200;
    _bonusPercentage = 10;
}

WarehouseReference :: WarehouseReference(char* _product, int _qty, char* _category, char* _receiptDate, float _price, float _bonusPercentage){
	this -> _product = new char[20];           // конструктор с параметрами
    strcpy(this -> _product, _product);
    this -> _qty = _qty;
	_category = new char[20];
    strcpy(this -> _category, _category);
	_receiptDate = new char[11];
    strcpy(this -> _receiptDate, _receiptDate);
    this -> _price = _price;
    this -> _bonusPercentage = _bonusPercentage;
}

void swap(WarehouseReference &obj1, WarehouseReference &obj2){
    char buff1[20];                     // метод для обменна данных 2х экземпляров класа
    char buff2[20];
    
	strcpy(buff1, obj1._product);
    strcpy(buff2, obj2._product);
    strcpy(obj1._product, buff2);
    strcpy(obj2._product, buff1);

    strcpy(buff1, obj1._category);
    strcpy(buff2, obj2._category);
    strcpy(obj1._category, buff2);
    strcpy(obj2._category, buff1);

    strcpy(buff1, obj1._receiptDate);
    strcpy(buff2, obj2._receiptDate);
    strcpy(obj1._receiptDate, buff2);
    strcpy(obj2._receiptDate, buff1);
    
    int buff = obj1._qty;
    obj1._qty = obj2._qty;
    obj2._qty = buff;
    
    float bufff = obj1._price;
    obj1._price = obj2._price;
    obj2._price = bufff;
    
    bufff = obj1._bonusPercentage;
    obj1._bonusPercentage = obj2._bonusPercentage;
    obj2._bonusPercentage = bufff;
}

#endif


