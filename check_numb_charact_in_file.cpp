//Функция проверки корректности количества символов в файле scale.txt

/** АЛГОРИТМ

  1) Вычисляем длину строки (это будет количество значений функции)
  2) Так как количество значений должно быть 2^n, где n - количество переменных, то
  3) Берём логарифм log2(длина строки (количество значений))
  4) Если получившееся число не дробное, то можно выделить количество переменных n


*/
int check_number_of_characters(int lineLength) {

    double quantityOfVariables = log2(lineLength);

    if (((double)((int)quantityOfVariables) == quantityOfVariables))
        return quantityOfVariables;

    else
        return -1;
}
