//
// Created by oleg on 19.04.2021.
//
#include "List.h"
#include <iostream>
#include <fstream>
using namespace std;
class Element{
    string number;
    int offenseType;
    string data;
public:
    string get_string(){
        return string(number + ";" + to_string(offenseType) + ";" + data + ";");
    }
    void setNumber(string number){this->number = number;}
    void setOffenseType(int type){this->offenseType = type;}
    void setData(string data){ this->data = data;}
    string getNumber()const{return this->number;}
    string getData()const{return this->data;}
    int getOffenseType()const{return this->offenseType;}
    Element(string number, int offenseType = 0, string data = ""): number(number), offenseType(offenseType), data(data){}
};
class FileIO {
    string filename;
    void read_all(Car* Root, ofstream& fstr){
        if(Root == nullptr)
            return;
        if(Root->getOffenseList().getHead() == nullptr){
            Element* temp = new Element(Root->getNumber());
            fstr << temp->get_string() << endl;
            delete temp;
        }else{
            readOffense(Root->getNumber(),Root->getOffenseList().getHead(),fstr);
        }
        read_all(Root->get_pRight(), fstr);
        read_all(Root->get_pLeft(), fstr);
    }
    void readOffense(string number, administrative_offense *root, ofstream& fstr){
        if( root == nullptr)
            return;
        Element* temp = new Element(number, root->getType(), root->getData());
        fstr << temp->get_string() << endl;
        delete temp;
        readOffense(number, root->get_pNext(), fstr);
    }
    void getDataFromCsv(char* temp, List& list){
        string number = "";
        string data = "";
        int type;
        for(int i = 0; i < 8; i++)
            number.push_back(temp[i]);
        cout << "Number:\t" << number << endl;
        int count = 9;
        string str;
        for(int i = 9; temp[i] != ';'; i++){
            str.push_back(temp[i]);
            count++;
        }
        type = stoi(str);
        cout << "OffenceType:\t" << type << endl;
        for (int i = count + 1; temp[i] != ';' ; i++){
            data.push_back(temp[i]);
        }
        cout << "Data:\t" << data << endl;
        list.add_car(number);
        if (type != 0)
            list.add_offence(number, type, data);
    }
public:
    FileIO(string filename = "base.csv"): filename(filename){}
    void wrightToFile(List& list){
        ofstream ofstr;
        ofstr.open(filename);
        if(!ofstr.is_open()){
            cout << "Ошибка открытия файла!";
            return;
        }
        read_all(list.getRoot(), ofstr);
        ofstr.close();
        cout << "База сохранена в файл:\t" << this->filename << endl;
    }
    string getFileName()const{return this->filename;}
    void setFileName(string filename){this->filename = filename;}
    void readFromFile(List& list){
        ifstream ifstr;
        ifstr.open(filename);
        if(!ifstr.is_open()){
            cout << "Файл базы не обнаружен! Загрузка базы пропущена." << endl;
            system("sleep 3");
            return;
        }
        cout << "Загрузка базы данных..." << endl;
        char temp[50]{};
        while (!ifstr.eof()){
           ifstr.getline(temp, 50);
           cout << temp << endl;
           getDataFromCsv(temp,list);
        }
        system ("sleep 3");
    }
};