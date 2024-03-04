// OOPLab2Tpl.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <clocale>
#include <string.h>
#include <Windows.h>
#include <vector>

/*Завдання 1. Обчислення виразів з використанням побітових операцій.
Задано цілі числа a, b, c та d.Обчислити вираз без використання операцій множення та
ділення(замінивши на їх операцій зсувів).
*/
void Example2()
{
    int a, b, x, y, c{}, d{};
#if !defined(VS_CODE)

    std::cout << "Приклад обчислення виразу використовуючи тiльки побiтовi операцiї. \n";
    std::cout << "Вираз : x = (18*a+312*d)/512-b*122+c*123. \n";
    std::cout << " Введiть a  b ";
#else 
    cout << "An example of calculating an expression using only bitwise operations.\n";
    cout << "Expression : x =(18*a+312*d)/512-b*122+c*123 . \n";
    cout << " Input a  b ";
#endif

    std::cin >> a >> b;
    auto st = std::cin.rdstate();
    if (st != std::cin.goodbit) { std::cin.clear(); std::cout << " error \n"; std::cin.get(); std::cin.get(); return; }
    x = a + (a << 5) + (((a << 4) - b - (b << 4)) >> 3) + (((b << 4) - b + 300) >> 7);
    y = (a * 18 + 312 * d) / 512 - b * 122 + c * 123;
    std::cout << "  x=" << x << "  y=" << y << " a=" << a << "  b=" << b;
    std::cin.get();
    std::cin.get();
    return;
}
/*Це фрагмент програми на мові програмування C++, який обчислює вираз
 використовуючи побітові операції замість операцій множення та ділення*/

 /*
   Вираз, який обчислюється: x = (18 * a + 312 * d) / 512 - b * 122 + c * 123.

 Значення a та b вводяться від користувача.

 Використовуються побітові операції для виконання обчислень без використання множення та ділення. Наприклад, (a << 5) еквівалентно
 множенню a на 32, а ((b << 4) - b + 300) >> 7 еквівалентно діленню ((b << 4) - b + 300) на 128.

 Обчислений результат виводиться на екран разом із введеними значеннями.

 */



 /*  Завдання 2
     3. Задано текст, який складається з 16 рядків до 4 символів у рядку. Доповнити пробілами рядки
 до 16 символів. Шифрувати тексти таким чином, щоб кожний символ тексту записувався у два
 байти. Два байти мають таку структуру:
 у бітах 0-3 знаходиться номер рядка символу (4 біти),
 у бітах 4-7 молодша частина ASCII - коду символу (4 біти),
 8 біт – біт парності перших двох полів (1 біт)
 у бітах 9-12 старша частина ASCII - коду символу (4 біти),
 у бітах 13-14 позиція символу в рядку (2 біти),
 15 біт - біт парності попередніх двох полів (1 біт)

 */



 // Функція для доповнення пробілами рядків
void PadStrings(std::string& input) {
    const int targetLength = 16;

    while (input.length() % targetLength != 0) {
        input += ' ';
    }
}

// Функція для шифрування тексту
void MyEncryption(const std::string& input, std::vector<unsigned short>& output) {
    const int rows = 16;
    const int columns = 4;

    output.clear();

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            char symbol = input[row * columns + col];

            // Створення байтів
            unsigned short firstByte = (row << 12) | ((symbol & 0xF) << 8) | (symbol & 0xF);
            unsigned short secondByte = ((symbol >> 4) & 0xF) | ((col & 0x3) << 13);


            // Додавання байтів до вектора
            output.push_back(firstByte);
            output.push_back(secondByte);
        }
    }
}

// Функція для розшифрування тексту
void MyDecryption(const std::vector<unsigned short>& input, std::string& output) {
    const int rows = 16;
    const int columns = 4;

    output.clear();

    for (size_t i = 0; i < input.size(); i += 2) {
        unsigned short firstByte = input[i];
        unsigned short secondByte = input[i + 1];

        // Видалення бітів парності
        firstByte &= ~(1 << 7);
        secondByte &= ~(1 << 15);

        // Видалення бітів позначення номера рядка та позиції символу
        unsigned char row = (firstByte >> 12) & 0xF;
        unsigned char lowerAscii = (firstByte >> 8) & 0xF;
        unsigned char upperAscii = (secondByte >> 4) & 0xF;

        // Відновлення символу та додавання його до результуючого рядка
        output.push_back((row * columns) + (i / 2) + 'A');
        output.push_back((lowerAscii << 4) | upperAscii);
    }
}

int main() {
    std::string inputText;

    std::cout << "Enter the text (16 lines, 4 characters each):" << std::endl;

    // Введення тексту
    for (int i = 0; i < 16; ++i) {
        std::string line;
        std::cin >> line;
        inputText += line;
    }

    // Доповнення пробілами
    PadStrings(inputText);

    std::vector<unsigned short> encryptedText;
    MyEncryption(inputText, encryptedText);

    // Виведення зашифрованого тексту
    std::cout << "Encrypted text:" << std::endl;
    for (const auto& code : encryptedText) {
        std::cout << code << ' ';
    }
    std::cout << std::endl;

    std::string decryptedText;
    MyDecryption(encryptedText, decryptedText);

    // Виведення розшифрованого тексту
    std::cout << "Decrypted text:" << std::endl;
    std::cout << decryptedText << std::endl;

    return 0;
}