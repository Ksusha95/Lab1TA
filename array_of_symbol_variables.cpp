//Заполнение массива переменных символами:

void creating_array_of_symb_variables(std::string *arrayOfSymbVariables, std::string *arrayOfSymbNegationVariables, int numbOfVariableInFunction) {

    char i; int j;
    std::string negation = "!";

    for (i = 'x', j = 0;  j < numbOfVariableInFunction; i++, j++) {

        arrayOfSymbVariables[j] = i;
        arrayOfSymbNegationVariables[j] = negation + i;

    }

    if (numbOfVariableInFunction >= 4) {

        arrayOfSymbVariables[numbOfVariableInFunction-1] = "u";
        arrayOfSymbNegationVariables[numbOfVariableInFunction-1] = negation + "u";
    }

}
