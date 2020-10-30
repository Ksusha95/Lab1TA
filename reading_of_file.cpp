//Функция чтения из файла
//Считываем из файла строку и передаём эту строку другим функциям
std::string reading_of_file() {

    std::string line;	//Строка, в которую будет записываться значение из файла

    std::fstream F;
    //открываем файл в режиме чтения

    //F.open("D:\scale.txt");  // - ДЛЯ ВЕНДЫ
    F.open("/home/ksussha/Lab1TA/scale.txt"); // - ДЛЯ ЛИНУКСА

    //если открытие файла прошло корректно, то
    if (F) {
        //цикл для чтения значений из файла; выполнение цикла прервется,
        //когда достигнем конца файла, в этом случае F.eof() вернет истину.
        while (!F.eof()) {
            //чтение очередного значения из потока F в переменную a
            F >> line;
        }
        //закрытие потока
        F.close();
    }
    //если открытие файла прошло некорректно, то вывод
    //сообщения об отсутствии такого файла
    else {

        std::cout << "Файл не существует" << std::endl;
        exit(0);
    }

    return line;

}