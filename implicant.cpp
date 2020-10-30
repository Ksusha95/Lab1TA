//Определение функций-элементов для класса Implicant

#include "implicant.h"
#include <algorithm>

//Конструктор без параметров
implicant::implicant() {}

//Конструктор c первоначальными параметрами
implicant::implicant(std::string lineOfFunction, size_t lineLength, int numbOfVariableInFunction){

    //Формируем Num
    //Заполняем массив номерами
    for (size_t i = 0; i < lineLength; i++) {

        if (lineOfFunction[i] == '1' || lineOfFunction[i] == '-') {

              this->Num.insert(this->Num.end(), i);
        }
    }


    //Формируем Ind
    for (size_t i = 0; i < Num.size(); i++) {

        int element = number_of_units(dec_2_bin(Num[i], numbOfVariableInFunction));
        this->Ind.insert(this->Ind.end(), element);
    }

    //Формируем P
    //Массив P:
    for (size_t i = 0; i < Num.size(); i++)
        this->P.insert(this->P.end(), 0);


    //Массив Pw:
    for (size_t i = 0; i < Num.size(); i++)
        this->Pw.insert(this->Pw.end(), ' ');
}


//ФУНКЦММ ДЛЯ ПЕЧАТИ
//Функция для печати массивов int
void implicant::print_int_array(std::vector<int> arrayVal) {

    for (size_t i = 0; i < arrayVal.size(); i++)

        if (arrayVal[i] >= 10 || arrayVal[i] < 0)
            std::cout << arrayVal[i] << " |";

        else
            std::cout << arrayVal[i] << "  |";

}

//Функция для печати массивов char
void implicant::print_char_array(std::vector<char> arrayVal) {

    for (size_t i = 0; i < arrayVal.size(); i++)
        std::cout << arrayVal[i] << "  |";

}

//Функция для печати всей таблицы
void implicant::print_full_table() {

    print_Num();
    print_Ind();
    print_P();
    print_Pw();

}

// *** ВСЕ ФУНКЦИИ, ПОМОГАЮЩИЕ СОЗДАТЬ, СФОРМИРОВАТЬ И ВЫВЕСТИ МАССИВ Num: ***

//Функция для формирования Num
void implicant::set_Num(int elementNum, size_t pos) {

    this->Num.at(pos) = elementNum;

}

//Так как переменная Num доступна только в пределах класса, main её не увидит. Это функция получения закрытой переменной Num всеми, кто её захочет:
std::vector<int> implicant::get_Num() {

    return Num;
}

//Печать массива Num:
void implicant::print_Num() {

    std::cout << "| Num\t|";
    print_int_array(Num);
    std::cout << std::endl;
}

//****************** КОНЕЦ ФУНКЦИЙ ДЛЯ МАССИВА Num *****************************


// *** ВСЕ ФУНКЦИИ, ПОМОГАЮЩИЕ СОЗДАТЬ, СФОРМИРОВАТЬ И ВЫВЕСТИ МАССИВ Ind: ***

//Функция для формирования Ind
void implicant::set_Ind(int numbOfVariableInFunction) {

    for (size_t i = 0; i < Num.size(); i++) {

        int element = number_of_units(dec_2_bin(Num[i], numbOfVariableInFunction));
        this->Ind.insert(this->Ind.end(), element);
    }
}

//Так как переменная Ind доступна только в пределах класса, main её не увидит. Это функция получения закрытой переменной Ind всеми, кто её захочет:
std::vector<int> implicant::get_Ind() {

    return Ind;
}

//Печать массива Ind:
void implicant::print_Ind() {

    std::cout << "| Ind\t|";
    print_int_array(Ind);
    std::cout << std::endl;
}

//****************** КОНЕЦ ФУНКЦИЙ ДЛЯ МАССИВА Ind *****************************


// *** ВСЕ ФУНКЦИИ, ПОМОГАЮЩИЕ СОЗДАТЬ, СФОРМИРОВАТЬ И ВЫВЕСТИ МАССИВ P: ***

//Функция для формирования P нулями в начальной таблице
void implicant::set_P_start() {

    //Массив P:
    for (size_t i = 0; i < Num.size(); i++)
        this->P.insert(this->P.end(), 0);
}

//Так как переменная P доступна только в пределах класса, main её не увидит. Это функция получения закрытой переменной P всеми, кто её захочет:
std::vector<int> implicant::get_P() {

    return P;
}

//Печать массива P:
void implicant::print_P() {

    std::cout << "| P  \t|";
    print_int_array(P);
    std::cout << std::endl;
}

//****************** КОНЕЦ ФУНКЦИЙ ДЛЯ МАССИВА P *****************************


// *** ВСЕ ФУНКЦИИ, ПОМОГАЮЩИЕ СОЗДАТЬ, СФОРМИРОВАТЬ И ВЫВЕСТИ МАССИВ Pw: ***

//Функция для формирования Pw нулями в начальной таблице
void implicant::set_Pw_start() {

    //Массив Pw:
    for (size_t i = 0; i < Num.size(); i++)
        this->Pw.insert(this->Pw.end(), ' ');
}

//Так как переменная Pw доступна только в пределах класса, main её не увидит. Это функция получения закрытой переменной Pw всеми, кто её захочет:
std::vector<char> implicant::get_Pw() {

    return Pw;
}

//Печать массива Pw:
void implicant::print_Pw() {

    std::cout << "| Pw \t|";
    print_char_array(Pw);
    std::cout << std::endl;
}

//Смотрим, есть ли флаги склейки в Pw:
bool implicant::check_Pw_splice_flag() {

    bool pwFlag = false;

    for (size_t i = 0; i < Pw.size(); i++) {

        if (Pw.at(i) == '*')
            pwFlag = true;
    }

    return pwFlag;
}
//****************** КОНЕЦ ФУНКЦИЙ ДЛЯ МАССИВА Pw ****************************


//ФУНКЦИИ ДЛЯ СКЛЕЙКИ
implicant implicant::splice_implicants() {

    implicant nextTable;

    for (size_t i = 0; i < Num.size(); i++) {

        for(size_t j = 1; j < Num.size(); j++) {

            if ((P.at(j) == P.at(i)) && (check_number_of_characters(Num.at(j) - Num.at(i)) >= 0) && (Ind.at(j) - Ind.at(i) == 1)) {

                nextTable.Num.push_back(this->Num.at(i));
                nextTable.Ind.push_back(this->Ind.at(i));
                nextTable.P.push_back(this->Num.at(j) - this->Num.at(i) + this->P.at(i));

                //Ставим флаг склейки в таблице, в которой склеиваем:
                this->Pw.at(i) = '*';
                this->Pw.at(j) = '*';

            }
        }
    }

    nextTable.set_Pw_start();


    return nextTable;

}


//ФУНКЦИЯ ДЛЯ ПРОВЕРКИ СТОЛБЦОВ БЕЗ ФЛАГА
void implicant::check_columms_without_Pw_flag(implicant &finalTable) {

    for (size_t i = 0; i < this->Num.size(); i++) {

        if (this->Pw.at(i) == ' ') {

            finalTable.Num.push_back(this->Num.at(i));
            finalTable.Ind.push_back(this->Ind.at(i));
            finalTable.P.push_back(this->P.at(i));
            finalTable.Pw.push_back(' ');
        }
    }

}

//ФУНКЦИЯ ДЛЯ УДАЛЕНИЯ ПОВТОРОВ:
implicant implicant::delete_repeats_in_table(implicant finalTable) {

    size_t position = 0;

    /* Так как номер Num не может быть отрицательным, то я у всех повторов сделала Num равным -1. А потом вектора с отрицательным Num просто потёрла*/

    //Сначала "клеймим" повторы значением -1
    for (size_t i = 0; i < finalTable.Num.size(); i++) {

        for(size_t j = i+1; j < finalTable.Num.size(); j++) {

            if ((finalTable.Num.at(i) == finalTable.Num.at(j)) && (finalTable.Ind.at(i) == finalTable.Ind.at(j)) && (finalTable.P.at(i) == finalTable.P.at(j)))
                finalTable.Num.at(j) = -1;

        }
    }


    //Удаляем повторы
    while (position < finalTable.Num.size()) {

            if (finalTable.Num.at(position) == -1) {

                finalTable.Num.erase(finalTable.Num.begin() + position);
                finalTable.Ind.erase(finalTable.Ind.begin() + position);
                finalTable.P.erase(finalTable.P.begin() + position);
                finalTable.Pw.erase(finalTable.Pw.begin() + position);
            }

            else
                position++;
    }

     return finalTable;

}

//

