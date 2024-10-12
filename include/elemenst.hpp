#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <memory>

class SchemeElements;
// ОПИСАНЫ ОСНОВНЫЕ ЭЛЕМЕНТЫ ПРИ РЕДУКЦИИ СХЕМЫ 
// ПОРТОВЫЕ ВНУТРЕННИЕ УЗЛЫ 
// МАТРИЦЫ R C ПОРТОВЫХ ЭЛЕМЕНТОВ 

#pragma once
// интерфейс для узлов
class SchemeNodes{
public: 
    virtual ~SchemeNodes();
    virtual void InsertElement(std::string LineFromNetlist);
    virtual void InsertElement(int node);
    virtual bool FindElement(int node);
    virtual void DisplayElements();
protected:
    std::unordered_map<int, std::pair<int, int>> nodes;
    unsigned NodesCount;
private:
};


class PortsNodes: public SchemeNodes{
public: 
    PortsNodes() {this->NodesCount = 0; std::cout << "PortsNodes()" << std::endl;}
    virtual ~PortsNodes() override;
private:
};

class IntersNodes: public SchemeNodes{
public: 
    IntersNodes() {this->NodesCount = 0; std::cout << "IntersNodes()" << std::endl;}
    virtual ~IntersNodes() override;
    void AddInternalNodes(std::shared_ptr<SchemeElements> Resistance, std::shared_ptr<SchemeElements> Capacitors, std::shared_ptr<SchemeNodes> Ports);
private:
};

// интерфейс для элементов 
class SchemeElements{
public:
    virtual ~SchemeElements();
    virtual bool FindElement(int node1, int node2);
    virtual void InsertElement(std::string LineFromNetlist) = 0;
    virtual double NetlistValueConverter(std::string& value); // перевод единиц измерения 
    virtual void DisplayElements();
    std::map<std::pair<int, int>, double> elements;
protected:
private:
};

class ResistanceElements: public SchemeElements {
public: 
    ResistanceElements() {}
    virtual ~ResistanceElements();
    virtual void InsertElement(std::string LineFromNetlist) override;
private:
};

class CapacitorsElements: public SchemeElements {
public: 
    CapacitorsElements() {}
    virtual ~CapacitorsElements();
    virtual void InsertElement(std::string LineFromNetlist) override;
private:
};
