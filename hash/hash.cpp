#include <string>
#include <iostream>

class Hash {
public:
    std::string GetHash(std::string str, unsigned hashLenght);
    int GetControlSum(std::string str);

private:
    std::string hash;
    int receivingExistCodes(int x);
};
int Hash::receivingExistCodes(int x) {
    x += 256;
    while (!(((x <= 57) && (x >= 48)) || ((x <= 90) && (x >= 65)) || ((x <= 122) && (x >= 97)))) {
        if (x < 48) { x += 24; }
        else { x -= 47; }
    }
    return x;
}

int Hash::GetControlSum(std::string str) {
    unsigned sault = 0;
    for (size_t i = 0; i < str.size(); i++) {  // Исправлен тип на size_t
        sault += static_cast<unsigned char>(str[i]);  // Безопасное приведение
    }
    return sault;
}

std::string Hash::GetHash(std::string str, unsigned hashLenght) {
    if (hashLenght < 4) {
        return " ";
    }

    unsigned minLength = 2;
    const unsigned originalLenghtStr = str.size();

    if (originalLenghtStr == 0) {
        return " ";
    }

    while (minLength < originalLenghtStr) {
        minLength *= 2;
    }
    if ((minLength - originalLenghtStr) < minLength) {
        minLength *= 2;
    }

    const int addCount = minLength - originalLenghtStr;
    for (int i = 0; i < addCount; i++) {
        const size_t idx1 = i % originalLenghtStr;
        const size_t idx2 = (i + 1) % originalLenghtStr;
        str += receivingExistCodes(str[idx1] + str[idx2]);
    }

    // Получаем контрольные значения
    const unsigned originalSault = GetControlSum(str);
    const unsigned maxLenghtStr = str.size();
    const int maxSault = GetControlSum(str);

    // Сжимаем хэш
    std::string tempHash;
    while (str.size() > hashLenght) { 
        tempHash.clear();
        const size_t center = str.size() / 2;

        for (size_t i = 0; i < center; i++) {
            const size_t left = center - i - 1;
            size_t right = center + i;
            if (right >= str.size()) {
                right = str.size() - 1;
            }
            tempHash += receivingExistCodes(str[left] + str[right]);
        }
        str = tempHash;
    }

    // Формируем итоговый хэш
    hash.clear();
    for (size_t i = 0; hash.size() < hashLenght - 4 && i < str.size(); i++) {
        hash += str[i];
    }

    // Добавляем контрольные значения
    hash += receivingExistCodes(originalSault);
    hash += receivingExistCodes(originalLenghtStr);
    hash += receivingExistCodes(maxSault);
    hash += receivingExistCodes(maxLenghtStr);

    // Обрезаем до нужной длины (на случай переполнения)
    if (hash.size() > hashLenght) {
        hash.resize(hashLenght);
    }

    return hash;
}