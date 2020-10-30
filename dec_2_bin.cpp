/* До всего прочего нужно сначала объявить переменную “n” как константу: “const int n = 32;” Она отвечает за размерность массива “s[n]”,
 * в который будет помещаться двоичное представление числа.
И так, давайте рассмотрим процедуру “Dec2Bin(int ch)”, которая выполняет преобразование 10-го числа в 2-й вид. Что в этой процедуре мы делаем?

Наше число в 10-м виде делим на 2 с остатком и если при делении получается число с остатком, то в i-й элемент массива “s[i]” мы записываем число 1,
в противном случае записываем 0. Этому числу “ch” приравниваем значение равное “ch”деленное на 2, эти действия выполняются пока число “ch” не будут равно нулю.

Дальше проверяем, если наше 10-е число отрицательное инвертируем значения массива “s[n]”, т.е. число 1 заменяем на 0 и число 0 на 1.
Это правило распространяется только на отрицательные числа. Затем приводим наш массив “s[n]” в нормальный вид, инвертируя значения до тех пор,
пока ни встретится значение равное 0. В конце концов, прогоняя массив по циклу “for” выводим двоичное представление числа в 10-м виде. Вот и все, теперь посмотрите, что получилось:

*/

std::array<int, 4> dec_2_bin (int decValue, int numbOfVariableInFunction) {

    const int N = 4;
    std::array<int, N> binValue = {0};
    int tempDecValue = decValue;

    if (decValue == 0)
        binValue = {0,0,0,0};

    else if (decValue == 1)
        binValue = {0,0,0,1};

    else if (decValue > 1) {

        while (decValue > 1) {

            decValue /= 2;

            if (decValue == 1) {

                binValue.at(numbOfVariableInFunction - 1) = tempDecValue - (2 * decValue);
                binValue.at(numbOfVariableInFunction - 2) = 1;
            }

            else {

                binValue.at(numbOfVariableInFunction - 1) = tempDecValue - (2 * decValue);
                tempDecValue = decValue;
            }

            numbOfVariableInFunction--;
        }
    }

    return binValue;
}