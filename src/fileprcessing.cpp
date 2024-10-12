#include "fileprocessing.hpp"
// обработка файла создание 
FileHendler::FileHendler(std::string netlistname){
    std::cout << "Открытие файла:	" << netlistname << std::endl;
    netlistfile.open(netlistname);
    if (netlistfile.is_open()){
        std::cout << "Файл успешно открыт" << std::endl;
    }
    this->Capaсitors   =   std::make_shared<CapacitorsElements>();
    this->Resistors    =   std::make_shared<ResistanceElements>();
    this->Ports        =   std::make_shared<PortsNodes>();
    this->NetlistProcessing();
}

FileHendler::~FileHendler(){
    std::cout << "~FileHendler" << std::endl;
    netlistfile.close();
}

void FileHendler::NetlistProcessing(){
    std::string line;
    while (getline(netlistfile, line)){ 
        if (!line.empty()){
            switch (line[0]){
                case 'R':{ this->Resistors->InsertElement(line);  break; }
                case 'C':{ this->Capaсitors->InsertElement(line); break; }
                case 'V':{ this->Ports->InsertElement(line);      break; }
                case 'D':{ this->Ports->InsertElement(line);      break; }
                case 'L':{ this->Ports->InsertElement(line);      break; }
                default: { break; }
            }
        }
    }
}

std::shared_ptr<SchemeElements> FileHendler::GetResistorsContainer(){
    return this->Resistors;
}

std::shared_ptr<SchemeElements> FileHendler::GetCapasitorsContainer(){
    return this->Capaсitors;
}

std::shared_ptr<SchemeNodes> FileHendler::GetPortsNodes(){
    return this->Ports;
}



