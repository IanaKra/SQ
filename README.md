# Проект SQ: Stack и Queue с тестами

## Как собрать и запустить тесты

```bash
cd tests
g++ -std=c++17 -I../gtest/googletest/include -I.. test_gtest.cpp -L../gtest/googletest -lgtest -pthread -o test_gtest.exe
./test_gtest.exe
```

## Что нужно
- Компилятор **g++ с поддержкой C++17**
- Google Test в папке `gtest/`

## Описание
34 теста из 9 тестовых наборов. Все тесты проходят.
