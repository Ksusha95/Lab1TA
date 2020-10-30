
//#include "stdafx.h"  //-- ВКЛЮЧИТЬ В ВЕНДЕ
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <math.h>
#include <array>
#include <vector>
#include <implicant.h>
#include <algorithm>
#include <tdnf.h>

//Подключаю свои собственные файлы
#include "reading_of_file.cpp"  //Чтение из файла
#include "check_numb_charact_in_file.cpp"   //Проверка корректности количества символов в файле scale.txt
#include "dec_2_bin.cpp"    //Перевод числа из десятичного в двоичное
#include "number_of_units.cpp"  //Вычисляет количество единиц в двоичном числе
#include "implicant.cpp"    //Класс Импликант, функции этого класса
#include "array_of_symbol_variables.cpp"    //Заполнение массива переменных символами
#include "construction_of_tdnf.cpp"     //Вычисление ТДНФ
#include "dynamic_table_line.cpp"   //Типа динамическое обрамление табличек
#include "filling_the_mdnf_table.cpp" //Заполнение итоговой таблицы МДНФ
#include "tdnf.cpp"

//Для красоты
std::string line;
const std::string line2(std::string(140, '_'));

int main() {

    setlocale(LC_ALL, "Rus");

    std::string functionLine = reading_of_file();  //Сюда записывается исходная функция
    int numbOfVariableInFunction = 0; //Количество переменных для данной функции
    size_t lineLength = functionLine.length(); //Количество значений данной функции в файле
    size_t tableNumber = 0; //Номер таблицы с импликантами

    std::vector<implicant> tablesM; //Динамический массив табличек М
    tablesM.push_back(implicant()); //Нулевая таблица М0 будет пустой, чтобы не путаться


    std::cout << line2 << "\nАЛГОРИТМ КВАЙНА МАК-КЛАСКИ:" << std::endl <<line2 <<std::endl;

    //Сначала просто посмотрим, что у нас есть в файле
    std::cout << "\nВывод содержимого файла \"scala.txt\": \n\n" << functionLine << std::endl <<line2 <<std::endl;

    //Проверяем, какое количество значений в строке из файла (должно быть кратное степени 2-ки)
    numbOfVariableInFunction = check_number_of_characters(lineLength);

    std::cout << "Количество значений данной функции в файле \"scala.txt \": " << lineLength << std::endl;

    if (numbOfVariableInFunction > 0) {

        std::cout << "   => количество переменных для данной функции: " << numbOfVariableInFunction << std::endl << line2 <<std::endl;


        //Начинаем составлять таблицы с импликантами:

        tablesM.push_back(implicant(functionLine, lineLength, numbOfVariableInFunction));
        tableNumber++;

        line = dynamic_table_line(tablesM.at(tableNumber).get_Num().size());

        std::cout << "1) Составляем таблицу M" << tableNumber <<":\n\n" << line <<"\n";
        tablesM.at(tableNumber).print_full_table();
        std::cout << line <<"\n";

        //Начинаем склеивать начальную таблицу:
        std::cout << "\n" << line2 << "\n2) Начинаем \"склейку\"" <<":\n\n" <<"\n";

        size_t pastTableNumber = 0;

        do  {

            pastTableNumber++;
            tablesM.push_back(tablesM.at(tableNumber).splice_implicants());
            tableNumber++;

            line = dynamic_table_line(tablesM.at(pastTableNumber).get_Num().size());

            std::cout << "Составлена таблица M" << pastTableNumber <<":\n" << line << "\n";
            tablesM.at(pastTableNumber).print_full_table();
            std::cout << line << "\n\n\n";


        } while (tablesM.at(pastTableNumber).check_Pw_splice_flag());

        size_t resultTableNumber = pastTableNumber; //М4 - итоговая таблица, например, у которой уже ничего нельзя склеить. Значит, это будет 4-я таблица по счёту

        //Неотмеченные флагом столбцы кидаем в массив дополнений
        std::cout << line2 << "\n3) Формируем массив дополнений из столбцов, не отмеченных \"*\" и присоединяем его к M4" <<":\n\n" <<"\n";

        for (size_t i = 1; i < resultTableNumber; i++) {

            tablesM.at(i).check_columms_without_Pw_flag(tablesM.at(resultTableNumber));

        }

        line = dynamic_table_line(tablesM.at(pastTableNumber).get_Num().size());

        std::cout << "Таблица M" << pastTableNumber <<" дополнена:\n" << line << "\n";
        tablesM.at(resultTableNumber).print_full_table();
        std::cout << line << "\n";

        //Нам уже не нужен массив таблиц, поэтому просто создаём итоговую таблицу:
        implicant finalTable = tablesM.at(resultTableNumber);

        //Исключаем повторы
        finalTable = finalTable.delete_repeats_in_table(finalTable);


        line = dynamic_table_line(finalTable.get_Num().size());
        std::cout << "\n" << line2 << "\n4) Исключаем повторы" <<":\n" << "\n" << line << "\n";
        finalTable.print_full_table();
        std::cout << line << "\n";

        //Создаём строку, в которой будет ТДНФ
        std::string tdnf1[finalTable.get_Num().size()];

        std::vector<tdnf> tdnfVec;

        //Вызываем функцию для вычисления ТДНФ
        tdnfVec = construct_of_tdnf(finalTable, numbOfVariableInFunction, tdnf1);

        std::cout << "\n" << line2 << "\n5) Получаем ТДНФ:" <<"\n"  << "\n";

        std::cout << " ";

        for (size_t i = 0; i < finalTable.get_Num().size() -1; i++)
            std::cout << tdnf1[i] << " + ";
        std::cout << tdnf1[finalTable.get_Num().size() -1] << ";";

        std::cout << "\n\n";

       //Создаём итоговую таблицу, с помощью которой вычислим МДНФ:

        std::cout << line2 << "\n6) Создаём итоговую таблицу для вычисления МДНФ:" <<"\n"  << "\n";

        //В столбцах таблицы у нас будут номера, у которых начальная функция была равна 1
        std::vector<int> Num;

        //Заполняем массив номерами
        for (size_t i = 0; i < lineLength; i++) {

            if (functionLine[i] == '1')
                  Num.push_back(i);
        }

        int stringTableOfMdnf = finalTable.get_Num().size() + 1; //Количество строк
        int columnTableOfMdnf = Num.size() + 1; //Количество столбцов

        //Передаём эту таблицу в функцию заполнения таблицы:
        filling_the_mdnf_table(stringTableOfMdnf, columnTableOfMdnf, Num, tdnf1, numbOfVariableInFunction, tdnfVec);

}


    else {

        std::cout << "\n  Неккоректное количество значений.\n  Программа завершена. \n\n";
        exit(0);
    }


}
