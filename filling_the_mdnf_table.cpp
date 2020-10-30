
bool search_string (tdnf stringObj, tdnf colm) {

    size_t sizeFlag = 0;
    bool flag = false;

    for(size_t i = 0; i < stringObj.get_tdnf().size(); i++) {

        for (size_t j = 0; j < colm.get_tdnf().size(); j++) {

            if (stringObj.get_tdnf().at(i) ==  colm.get_tdnf().at(j))
                sizeFlag++;
        }
    }

    if (sizeFlag == stringObj.get_tdnf().size())
        flag = true;

    return flag;
}


void filling_the_mdnf_table(int stringTable, int columnTable, std::vector<int> Num,  std::string *tdnf1, int numbOfVariableInFunction, std::vector<tdnf> tdnfVec) {

    const std::string line(std::string(135, '-'));

    std::string tableOfMdnf[stringTable][columnTable];
    std::vector<tdnf> tableColm;

    tableOfMdnf [0][0] = " ";

    std::array<int, 4> binNum;

    std::string arrayOfSymbVariables[numbOfVariableInFunction]; //Массив с буквенными переменными x, y, z..
    std::string arrayOfSymbNegationVariables[numbOfVariableInFunction]; //Массив с отрицательными буквенными переменными !x, !y, !z..


    //Заполняем массивы символами
    creating_array_of_symb_variables(arrayOfSymbVariables, arrayOfSymbNegationVariables, numbOfVariableInFunction);


    /* ****************** Заполняем шапку таблицы: ******************* */
    //Сначала столбцы таблицы:
    int str = 0;

    for (int col = 1; col < columnTable; col++) {

        std::string symbColumnResult;
        tableColm.push_back(tdnf());

        //Переводим Num и P в двоичные значения:
        binNum = dec_2_bin(Num.at(col-1), numbOfVariableInFunction);

        //Теперь рассматриваем конкретный столбец отдельно
        for (int j = 0; j < numbOfVariableInFunction; j++) {

            //Смотрим, что в Num
            if (binNum.at(j) == 0) {

                symbColumnResult = symbColumnResult + arrayOfSymbNegationVariables[j];
                tableColm.at(col-1).set_tdnf(arrayOfSymbNegationVariables[j]);

            }


            else if (binNum.at(j) == 1) {

                symbColumnResult = symbColumnResult + arrayOfSymbVariables[j];
                tableColm.at(col-1).set_tdnf(arrayOfSymbVariables[j]);
            }
        }

        tableOfMdnf[str][col] = symbColumnResult;
    }

    //Заполняем строки таблицы:
    int col = 0;

    for (int str = 1; str < stringTable; str++)
        tableOfMdnf[str][col] = tdnf1[str-1];

    /* **************** конец заполнения шапки таблицы ***************** */

    /* **************** расставление плюсиков ************************** */

    //Ищем строки
    for (size_t i = 0; i < tdnfVec.size(); i++) {

        for (size_t j = 0; j < tableColm.size(); j++) {

            bool flag = search_string(tdnfVec.at(i), tableColm.at(j));

            if (flag)
                tableOfMdnf[i+1][j+1] = "     +";
            else
                tableOfMdnf[i+1][j+1] = "      ";
        }
    }

    /* ********************** Печать таблицы *********************** */

    std::cout << "\n" << line << "\n";

    for (int i = 0; i < stringTable; i++) {

       for (int j = 0; j < columnTable; j++)
           std::cout << tableOfMdnf[i][j] << "     ";

       std::cout << "\n" << line << "\n";
   }

    /* ******************** Вычисление МДНФ **************************** */ 

     for (int i = 1; i < stringTable; i++) {

         size_t sumPlus = 0;
         size_t sumTrueFlag = 0;

          for (int j = 1; j < columnTable; j++) {

          //если есть плюсик:
              if (tableOfMdnf[i][j] == "     +") {

                  sumPlus++;


                  //Смотрим столбец построчно:
                  for (int k = 1; k < stringTable; k++) {

                    if (tableOfMdnf[k][j] == tableOfMdnf[i][j] && k != i) {

                        sumTrueFlag++;
                        break;
                    }

                  }
              }
          }

          //Если совпадают, очищаем строку
          if (sumPlus == sumTrueFlag) {

              for (int l = 0; l < columnTable; l++)
                  tableOfMdnf[i][l] = "   ";

              tdnfVec.at(i-1).clear_value();

          }

     }

     /* ************************* конец вычисления МДНФ ********************* */


     /* ********************** Печать таблицы *********************** */

     std::cout << "\n\n  Вычёркиваем лишние строки:" <<"\n"  << "\n";

     std::cout << "\n" << line << "\n";

     for (int i = 0; i < stringTable; i++) {

        for (int j = 0; j < columnTable; j++)
            std::cout << tableOfMdnf[i][j] << "     ";

        std::cout << "\n" << line << "\n";
     }

     std::cout << "\n";


     /* ********************** Выводим МДНФ на печать: *********************** */
     const std::string line2(std::string(140, '_'));

     std::cout << line2 << "\n7) Итоговая МДНФ:" <<"\n"  << "\n";

     col = 0;

      std::cout << " ";

     for (int i = 1; i < stringTable-1; i++) {

         if (tableOfMdnf[i][col] != "   ")
             std::cout << tableOfMdnf[i][col] << " + ";
     }

     std::cout << tableOfMdnf[stringTable-1][col] << ";";

     std::cout << "\n" << line2 <<"\n\n";

}



