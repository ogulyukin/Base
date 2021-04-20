//
// Created by oleg on 13.04.2021.
//
#pragma once
#include <iostream>
#include <string>
#include <regex>
//#include "List.h"
#include "FileIO.h"
class interface{
    List list;
    offence_types of_types;
    FileIO workFile;
    bool check_choise(int max_choise, int choise){
        if (choise < 0 || choise > max_choise)
            return false;
        return true;
    }
    void print_head(){
        system("clear");//для Windows изменить на "cls"
        cout << "----------------------------------------------------------------------------------" << endl;
        cout << "|                           База автомобилей                                     |" << endl;
        cout << "----------------------------------------------------------------------------------" << endl;
    }
    void print_offense_types(){
        cout << "\t\tПеречень нарушений ПДД:\n\n";
        for(int i = 0; i < of_types.get_size(); i++){
            cout << of_types.get_article(i) << endl;
        }
        cout << endl;
    }
    string input_number(){
        string input;
        cout << "Введите номер транспортного средства: "; cin >> input;
        if (!list.is_car_in_list(input)){
            cout << "Транспортное средство с таким номером отсутствует в базе!" << endl;
            system("sleep 3");
            return "0";
        }
        return input;
    }
    bool check_data(string data){
        regex data_mask("[0123]\\d\\.[01][012]\\.[12][09]\\d\\d");
        return regex_match(data.begin(), data.end(), data_mask);
    }
public:
    interface():list(),workFile(){
        workFile.readFromFile(list);
    }
    ~interface(){};
    int print_menu(){
        int choise = 0;
        do {
            print_head();
            cout << "Выберите пункт меню:" << endl;
            cout << "1. Печать всех автомобилей базы" << endl;
            cout << "2. Добавить новый автомобиль в базу" << endl;
            cout << "3. Добавить новое нарушение ПДД в базу" << endl;
            cout << "4. Поиск автомобиля по номеру" << endl;
            cout << "5. Поиск автомобилей с нарушениями по типу" << endl;
            cout << "0. Завершить работу с базой" << endl;
            cout << endl << "Ввод: "; cin >> choise;
        }while(!check_choise(5, choise));
        return choise;
    }
    void print_all(){
        print_head();
        cout << "\t\t Вывод всех транспортных средств базы.\n\n";
        list.print_all();
        system("sleep 3");
        return;
    }
    void add_car(){
        print_head();
        cout << "\t\t Добавление нового транспортного средства в базу.\n\n";
        string input;
        cout << "Введите номер добавляемой машины, маска: (A123AA11) : "; cin >> input;
        int result = list.add_car(input);
        switch (result) {
            case 100:
                cout << "Введен некорректный номер!" << endl;
                break;
            case 200:
                cout << "Введенный номер уже присутствует в базе!" << endl;
                break;
            case 0:
                cout << "Транспортное средство успешно добавлено." << endl;
        }
        system("sleep 3");
        return;
    }
    void add_offense(){
        print_head();
        cout << "\t\tДобавление нового правонарушения.\n\n";
        string input = input_number();
        if (input == "0"){
            system("sleep 3");
            return;
        }
        print_head();
        cout << "\t\tГосномер транспортного средства : " << input << endl;
        print_offense_types();
        int offense_type = 0;
        cout << "Введите тип правонарушения: "; cin >> offense_type;
        if (!check_choise(10, offense_type)){
            cout << "Введен некорректный тип нарушения ПДД!" << endl;
            system("sleep 3");
            return;
        }
        string data;
        cout << "Введите дату совершения нарушения в формате ДД.ММ.ГГГГ:  "; cin >> data;
        if (!check_data(data)){
            cout << "Введена неверная дата!" << endl;
            system ("sleep 3");
            return;
        }
        list.add_offence(input, offense_type - 1, data);
        cout << "Правонарушение добавлено." << endl;
        system("sleep 3");
    }
    void find_car(){
        print_head();
        cout << "\t\tПоиск транспотроного средства в базе.\n\n";
        string input = input_number();
        if (input == "0"){
            system("sleep 3");
            return;
        }
        list.find_car(input);
        system("sleep 3");
    }
    void print_car_by_offense_type(){
        print_head();
        int input;
        cout << "\t\tПоиск транспортных средств по типу нарушения ПДД\n\n";
        print_offense_types();
        cout << "Введите тип нарушения ПДД: "; cin >> input;
        if(!check_choise(10, input)){
            cout << "Введен некорректный тип нарушения!" << endl;
            system("sleep 3");
            return;
        }
        list.print_car_with_offence_type(input - 1);
        system("sleep 3");
    }
    void main_form(){
        int choise = 0;
        do{
            choise = print_menu();
            switch (choise) {
                case 1:
                    print_all();
                    break;
                case 2:
                    add_car();
                    break;
                case 3:
                    add_offense();
                    break;
                case 4:
                    find_car();
                    break;
                case 5:
                    print_car_by_offense_type();
                    break;
            }
        }while(choise);
        workFile.wrightToFile(list);
    }
};
