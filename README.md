# Контрольная работа для второго курса по теме ООП
## Установка GTest
Несколько команд в терминал:
```
sudo apt-get install libgtest-dev
cd /usr/src/googletest/googletest
sudo mkdir build
cd build
sudo cmake ..
sudo make
sudo cp libgtest* /usr/lib/
```