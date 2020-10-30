#ifndef IMPLICANT_H
#define IMPLICANT_H

//Определение типа данных Implicant (эти таблички М1, М2, М3...)
class implicant {

    public:

        implicant();

        implicant(std::string lineOfFunction, size_t lineLength, int numbOfVariableInFunction); //Конструктор

        void print_int_array(std::vector<int> arrayVal);   //Функция для печати массивов int
        void print_char_array(std::vector<char> arrayVal);   //Функция для печати массивов int
        void print_full_table();


        // *** ВСЕ ФУНКЦИИ, ПОМОГАЮЩИЕ СОЗДАТЬ, СФОРМИРОВАТЬ И ВЫВЕСТИ МАССИВ Num: ***

        void set_Num(int elementNum, size_t pos);   //Функция для формирования Num
        std::vector<int>get_Num();  //Получение приватной переменной Num всеми, кто не входит в члены класса Implicant
        void print_Num();   //Печать массива Num:

        // *** ВСЕ ФУНКЦИИ, ПОМОГАЮЩИЕ СОЗДАТЬ, СФОРМИРОВАТЬ И ВЫВЕСТИ МАССИВ Ind: ***

        void set_Ind(int numbOfVariableInFunction);
        std::vector<int> get_Ind();
        void print_Ind();

        // *** ВСЕ ФУНКЦИИ, ПОМОГАЮЩИЕ СОЗДАТЬ, СФОРМИРОВАТЬ И ВЫВЕСТИ МАССИВ P: ***

        void set_P_start();
        std::vector<int> get_P();
        void print_P();

        // *** ВСЕ ФУНКЦИИ, ПОМОГАЮЩИЕ СОЗДАТЬ, СФОРМИРОВАТЬ И ВЫВЕСТИ МАССИВ Pw: ***

        void set_Pw_start();
        std::vector<char> get_Pw();
        void print_Pw();
        bool check_Pw_splice_flag();

        //Склейка:
        implicant splice_implicants();

        //Поиск и добавление к итоговой таблице столбцов без флажка склейки:
        void check_columms_without_Pw_flag(implicant &finalTable);

        //Удаление повторов:
        implicant delete_repeats_in_table(implicant finalTable);



   private:

        std::vector<int> Num;     //Получение массива значений Num
        std::vector<int> Ind;     //Сколько единиц в двоичном представлении номера Num
        std::vector<int> P;
        std::vector<char> Pw;     //Флаг, показывающий, были склеены столбцы или нет

};

#endif // IMPLICANT_H
