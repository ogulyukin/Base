//
// Created by oleg on 12.04.2021.
//
#include <iostream>
#include <string>
#include <regex>
using namespace std;
class offence_types{
    int size;
    string articles[10];
//класс не сталл распысывать поскольку не было такого задания и нужен лишь для теста, однако в реальной базе - может быть отдельной базой
public:
    offence_types(){
        this->size = 10;
        articles[0] = "1. Управление ТС, не зарегистрированным в установленном порядке";
        articles[1] = "2. Управление транспортным средством без государственных регистрационных знаков, а равно управление транспортным средством без установленных на предусмотренных для этого местах государственных регистрационных знаков либо управление транспортным средством с государственными регистрационными знаками, видоизмененными или оборудованными с применением устройств или материалов, препятствующих идентификации государственных регистрационных знаков либо позволяющих их видоизменить или скрыть";
        articles[2] =  "3. Передача управления ТС лицу, не имеющему при себе документов на право управления им";
        articles[3] =  "4. Управление ТС, на которое незаконно нанесена цветографическая схема легкового такси";
        articles[4] =  "5. Управление ТС водителем, не пристегнутым ремнем безопасности, перевозка пассажиров, не пристегнутых ремнями безопасности, если конструкцией транспортного средства предусмотрены ремни безопасности, а равно управление мотоциклом либо перевозка на мотоцикле пассажиров без мотошлемов или в незастегнутых мотошлемах";
        articles[5] =  "6. Управление ТС водителем, не имеющим права управления транспортным средством (за исключением учебной езды)";
        articles[6] =  "7. Управление ТС водителем, находящимся в состоянии опьянения.";
        articles[7] =  "8. Превышение установленной скорости движения ТС на величину более 20, но не более 40 километров в час";
        articles[8] =  "9. Превышение установленной скорости движения ТС на величину более 40, но не более 60 километров в час";
        articles[9] =  "10. Выезд в нарушение Правил дорожного движения на полосу, предназначенную для встречного движения, либо на трамвайные пути встречного направления, за исключением случаев, предусмотренных частью 3 настоящей статьи";
    }
    string get_article(int i){return this->articles[i];}
    int get_size(){return this->size;}
};
class offense_list{
    class administrative_offense{
        int type;
        string data;
        administrative_offense* pNext;
        offence_types of_types;
    public:
        administrative_offense(int type, string data, administrative_offense* pNext = nullptr) : type(type), data(data), pNext(pNext){}
        ~administrative_offense(){}
        administrative_offense(){
            this->type = 0;
            this->data = "01.01.1900";
            this->pNext = nullptr;
        }
        friend class offense_list;
    };
    administrative_offense* Head;
public:
    offense_list(){
        Head = nullptr;
    }
    ~offense_list(){
        while(Head)
            pop_front();
    }
    void push_front(int type, string data){
        administrative_offense* temp = new administrative_offense(type, data, Head);
        Head = temp;
    }
    void pop_front(){
        if(Head == nullptr)
            return;
        administrative_offense* temp = Head;
        Head = Head->pNext;
        delete temp;
    }
    void print(){
        if(Head == nullptr)
            return;
        administrative_offense* temp = Head;
        while(temp != nullptr){
            cout << endl << temp->data << "\t" << temp->of_types.get_article(temp->type) << endl;
            temp = temp->pNext;
        }
    }
    bool hase_type(int type){
        if(Head == nullptr)
            return false;
        administrative_offense* temp = Head;
        while(temp != nullptr){
            if(temp->type == type)return true;
            temp = temp->pNext;
        }
        return false;
    }
};
class List {
    class Car{
        string number;
        offense_list offenseList;
        Car* pLeft;
        Car* pRight;
    public:
        Car(string number = "0", Car* pLeft = nullptr, Car* pRight = nullptr):
        number(number),offenseList(), pLeft(pLeft), pRight(pRight){}
        ~Car(){}
        void Print(){
            cout << "Регистрационный номер: " << number << endl;
        }
        void Print_offense(){
            cout << "Регистрационный номер: " << number << endl;
            offenseList.print();
        }
        void add_offence(int type, string data){
            this->offenseList.push_front(type, data);
        }
        bool has_type(int type){
            return offenseList.hase_type(type);
        }
        friend class List;
    };
    Car* Root;
    void add_car(string number, Car* Root){
        if(number < Root->number){
            if(Root->pLeft == nullptr){
                Root->pLeft = new Car(number);
                return;
            }else
                add_car(number, Root->pLeft);
        }else{
            if(Root->pRight == nullptr){
                Root->pRight = new Car(number);
                return;
            }else
                add_car(number, Root->pRight);
        }
    }
    void clear(Car* Root){
        if(Root == nullptr) return;
        clear(Root->pLeft);
        clear(Root->pRight);
        delete Root;
    }
    void find_car(string number, Car* Root, Car*& Catched){
        if(Root->number == number){
            Catched = Root;
            return;
        }
        if(number < Root->number && Root->pLeft != nullptr)
            find_car(number, Root->pLeft, Catched);
        if(number > Root->number && Root->pRight != nullptr)
            find_car(number, Root->pRight, Catched);
        return;
    }
    bool check_number(string number){
        //regex number_mask("[АВЕКМНОРСТУХ]\\d{3}[АВЕКМНОРСТУХ]{2}\\d{2}");//проблема с русскими буквами... ups!
        regex number_mask("[ABEKMHOPCTYX]\\d{3}[ABEKMHOPCTYX]{2}\\d{2}");
        if(!regex_match(number.begin(), number.end(), number_mask)){
            return false;
        }
        //if(number.size() < 8 || number.size() > 8) return false;
        return true;
    }
    void find_car_with_offence_type(int number, Car* Root){
        if (Root == nullptr)
            return;
        if(Root->has_type(number))
            Root->Print();
        find_car_with_offence_type(number,Root->pLeft);
        find_car_with_offence_type(number,Root->pRight);
    }
    void print_all(Car* Root){
        if(Root == nullptr)
            return;
        cout << endl;
        Root->Print();
        print_all(Root->pLeft);
        print_all(Root->pRight);
    }
public:
    List(){
        Root = nullptr;
    }
    ~List(){
        clear(this->Root);
    }
    int add_car(string number){
        if(!check_number(number)){
            return 100; //введен неверный номер
        }
        if(Root == nullptr){
            Root = new Car(number);
            return 0; //первый эелемент в базу добавлен
        }
        Car* temp = new Car;
        find_car(number, this->Root, temp);
        if(temp->number != "0")
           return 200; //номер уже есть в базе
        add_car(number, this->Root);
        return 0; //номер добавлен
    }
    void add_offence(string number, int type, string data){
        Car* temp = new Car;
        find_car(number, this->Root, temp);
        if(!check_number(temp->number)){
            cout << temp->number << endl;
            return;
        }
        temp->add_offence(type,data);
    }
    void find_car(string number){
        Car* temp = new Car;
        find_car(number, this->Root, temp);
        temp->Print_offense();
    }
    void print_car_with_offence_type(int number){
        find_car_with_offence_type(number, this->Root);
    }
    void print_all(){
        print_all(this->Root);
    }
    bool is_car_in_list(string number){
        Car* temp = new Car;
        find_car(number, this->Root, temp);
        if(check_number(temp->number))
            return true;
        return false;
    }
};
