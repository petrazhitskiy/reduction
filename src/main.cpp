#include <iostream>
#include <memory>
#include <locale>

// my includes
#include "fileprocessing.hpp"
#include "elemenst.hpp"
#include "subnets.hpp"

// lib include 
#ifndef EIGEN_SPARSELU_H
#define EIGEN_SPARSELU_H
#include <Eigen/SparseLU>
#endif



int main(int argc, char *argv[]){

    if (argc < 2) 
        return 1;

    std::unique_ptr<FileHendler> FileWorder {std::make_unique<FileHendler>(argv[1])};
    std::shared_ptr<SchemeElements> Resistors = FileWorder->GetResistorsContainer();
    std::shared_ptr<SchemeElements> Capasitors = FileWorder->GetCapasitorsContainer();
    std::shared_ptr<SchemeNodes> Ports = FileWorder->GetPortsNodes();
    std::shared_ptr<IntersNodes> Inters = std::make_shared<IntersNodes>();
    Inters->AddInternalNodes(Resistors, Capasitors, Ports);
    std::shared_ptr<SubNets> Subnets = std::make_shared<SubNets>(Resistors, Capasitors, Ports);

return 0;
}
















// написать класс подсети который принимает список узлов подсети и создает
// и находит портовые узлы данной подсети для этого ей необходим список портов всей схемы 
// 



// У нас будет класс который принимает порты резисторы конденсаторы узлы в конструкторе на основе этого ищет подсети 
// Содержит контейнер с подсетями 
// Напишем класс который будет принимать класс subnet и редуцировать кажду. подсеть 
// У насeсть все портовые и внутренние кзлы 
// Необходимо разбить эти узлы по подсетям 
// 1. узел - контейнер узлов связанных с ним 
// 2. порт - контенер узлов связанных с ним
// 3. порт - порт 

// Получаем подсети при помози обхода графа в ширину findComponents
// Получае список портов каждой подсети 


