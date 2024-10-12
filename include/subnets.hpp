#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <unordered_map>

#include "elemenst.hpp"

// ОПИСАНИЕ ПОДСЕТЕЙ 
// КЛАССЫ ОТВЕЧАЮТ ЗА СОЗДАНИЕ И РАБОТУ С ПОДСЕТЯМИ

#pragma once 

class SubNet{
public: 
    SubNet(
        std::vector<int>& component, 
        std::map<int, std::vector<int>>& port_connect,
        std::shared_ptr<SchemeElements> _Resistance,
        std::shared_ptr<SchemeElements> _Capacitors
        );

    ~SubNet() {}
    std::vector<int> IntersNode;
    std::vector<int> PortsNode;
    std::shared_ptr<SchemeElements> Resistance;
    std::shared_ptr<SchemeElements> Capacitors;
private:
    void FindPortsSubnet(std::map<int, std::vector<int>>& port_connect);
};

class SubNets{
public:
    SubNets(std::shared_ptr<SchemeElements> _Resistance, std::shared_ptr<SchemeElements> _Capacitors, std::shared_ptr<SchemeNodes> Ports);
    ~SubNets() {};
    std::shared_ptr<SchemeElements> Resistance;
    std::shared_ptr<SchemeElements> Capacitors;
    std::vector<std::shared_ptr<SubNet>> SubnetsList;                   // список подсетей
private:
    std::map<int, std::vector<int>> adjacencyList;                      // Узловые соединения 
    std::map<int, std::vector<int>> port_connect;                       // портовые соединения
    std::map<std::pair<int, int>, std::pair<int, int>> ports_subnet;    // подсети из портов
    void CreateSubnets();
    void dfs(int node, std::map<int, std::vector<int>>& adjacencyList, 
            std::unordered_set<int>& visited, std::vector<int>& component);
};





//Описание к данному файлу 
// 1. Если ни один узел не содержится в портах добавляем его в adjacencyList причем делаем два узла с сылкой на данный 
// 2. Если оба узла портовые то добавляем в ports_subnet - подсеть из портов грубо говоря 
// 3. Если только порт - узел то соответственно port_connect для 
        // узел - порт 

// логика добавления такая, 
// Задачи
// 1) 
    // написать класс который будет брать портовые и узловые элементы 
    // и создавать с какими узлами связан порт 
    // и с какими портами связан узел - это все что нужно 

// 2) 
    // Потом определить из какиз портов и узлов состоит каждая посдесеть 

// 3) 
    // Создаем класс который выполняет редукцию каждой подсети 
    // Принимает указатель на данную подсеть и выполняет над ней определенные действия можно создать два класса 
    // для выполнения первого и второго преобразования соответственно 



