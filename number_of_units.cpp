//Функция, подсчитывающая количество единиц в числе, служит для формирования массива Ind
int number_of_units(std::array<int, 4> arrayVal) {

    int numbOfUnitsValue = 0;

    for (size_t i = 0; i < arrayVal.size(); i++) {

        if (arrayVal[i] == 1)
            numbOfUnitsValue++;
    }

    return numbOfUnitsValue;
}
