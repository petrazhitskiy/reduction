#include <iostream>
#include <fstream>
#include <memory>

#include "elemenst.hpp"

#pragma once 
// ФАЙЛ ДЛЯ КЛАССОВ РАБОТАЮЩИХ С ФАЙЛАМИ

// обработка файла создание 
// класс отвечает за открытие нетлиста и 
// его первичную обработку 
class FileHendler {
public:
    FileHendler(std::string netlistname);
    ~FileHendler();
    std::shared_ptr<SchemeElements> GetResistorsContainer();
    std::shared_ptr<SchemeElements> GetCapasitorsContainer();
    std::shared_ptr<SchemeNodes>    GetPortsNodes();
private:
    void NetlistProcessing();
    std::ifstream   netlistfile;    // Нетлист 
    std::shared_ptr<SchemeElements> Resistors;      // Резисторы 
    std::shared_ptr<SchemeElements> Capaсitors;     // Конденсаторы 
    std::shared_ptr<SchemeNodes>    Ports;          // Портовые узлы  
};


// создание нового нетлиста













