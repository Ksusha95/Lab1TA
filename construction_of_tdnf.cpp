//Нам тут будут нужны массив переменных, Num, P, и функция dec_2_bin

std::vector<tdnf> construct_of_tdnf(implicant table, int numbOfVariableInFunction, std::string *tdnf1) {

    const int tableSize = table.get_Num().size();
    const int N = 4;

    std::array<int, N> binNum;
    std::array<int, N> binP;

    std::string arrayOfSymbVariables[numbOfVariableInFunction]; //Массив с буквенными переменными x, y, z..
    std::string arrayOfSymbNegationVariables[numbOfVariableInFunction]; //Массив с отрицательными буквенными переменными !x, !y, !z..

    std::vector<tdnf> tdnfPart;

    //Заполняем массивы символами
    creating_array_of_symb_variables(arrayOfSymbVariables, arrayOfSymbNegationVariables, numbOfVariableInFunction);


    //Перебираем столбцы Num и Ind и рассматриваем каждый слолбец отдельно
    for (int i = 0; i < tableSize; i++) {

        std::string symbColumnResult;
        tdnfPart.push_back(tdnf());

        //Переводим Num и P в двоичные значения:
        binNum = dec_2_bin(table.get_Num().at(i), numbOfVariableInFunction);
        binP = dec_2_bin(table.get_P().at(i), numbOfVariableInFunction);

        //Теперь рассматриваем конкретный столбец отдельно
        for (int j = 0; j < numbOfVariableInFunction; j++) {

            //Нам надо рассматривать те номера Num, где P = 0:
            if (binP.at(j) == 0) {

                //Смотрим, что в Num
                if (binNum.at(j) == 0) {

                    symbColumnResult = symbColumnResult + arrayOfSymbNegationVariables[j];
                    tdnfPart.at(i).set_tdnf(arrayOfSymbNegationVariables[j]);
                }

                else if (binNum.at(j) == 1) {

                    symbColumnResult = symbColumnResult + arrayOfSymbVariables[j];
                    tdnfPart.at(i).set_tdnf(arrayOfSymbVariables[j]);
                }
            }
        }

        tdnf1[i] = symbColumnResult;
    }

    return tdnfPart;
}
