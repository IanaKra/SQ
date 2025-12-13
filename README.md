# Проект SQ: Stack и Queue с тестами

## Как собрать и запустить тесты

### 1. Клонирование с подмодулем
```bash
git clone --recursive https://github.com/IanaKra/SQ.git
cd SQ
```

### 2. Сборка библиотеки Google Test
```bash
cd gtest/googletest
g++ -std=c++17 -I./include -I./ -c ./src/gtest-all.cc -o gtest-all.o -pthread
ar rcs libgtest.a gtest-all.o
cd ../..
```

### 3. Компиляция и запуск тестов
```bash
cd tests
g++ -std=c++17 -I../gtest/googletest/include -I.. test_gtest.cpp -L../gtest/googletest -lgtest -pthread -o test_gtest.exe
./test_gtest.exe
```

## Структура проекта
- `tests/test_gtest.cpp` — 34 теста
- `gtest/` — Google Test как подмодуль
- `Stack.h`, `Stack.hpp` — реализация стека
- `Queue.h`, `Queue.hpp` — реализация очереди
- `Containers.h`, `Containers.hpp` — базовые классы

## Описание
34 теста из 9 тестовых наборов. Все тесты проходят.
