#include "elemenst.hpp"


void SchemeNodes::InsertElement(std::string LineFromNetlist){
    std::istringstream iss(LineFromNetlist);
    char type;
    int index;
    int node1, node2;
    iss >> type >> index >> node1 >> node2;
    std::cout << node1 << " " << node2 << std::endl;
	std::pair<int, int> nodes = {node1, node2};
    if (!this->nodes.count(node1))
        this->nodes[node1] = {this->NodesCount++, node1};
    if (!this->nodes.count(node2))
        this->nodes[node2] = {this->NodesCount++, node2};
}

void SchemeNodes::InsertElement(int node){
    this->nodes[node] = {this->NodesCount++, node};
}

void SchemeNodes::DisplayElements(){
    for (auto node: this->nodes){
        std::cout << "Node : " << node.second.first << " " << node.second.second << std::endl;
    }
}

bool SchemeNodes::FindElement(int node){
    if (this->nodes.count(node))
        return 1;
    return 0;
}


SchemeNodes::~SchemeNodes() {std::cout << "~SchemeNodes()" << std::endl;}
PortsNodes::~PortsNodes() {std::cout << "~PortsNodes()" << std::endl;}
IntersNodes::~IntersNodes() {std::cout << "~IntersNodes()" << std::endl;}

//создаем внутренние узлы
void IntersNodes::AddInternalNodes(std::shared_ptr<SchemeElements> Resistance, std::shared_ptr<SchemeElements> Capacitors, std::shared_ptr<SchemeNodes> Ports){
    for (auto& NodesPair : Resistance->elements) {
        if (!Ports->FindElement(NodesPair.first.first)) {
			this->InsertElement(NodesPair.first.first);
		}
		if (!Ports->FindElement(NodesPair.first.second)) {
			this->InsertElement(NodesPair.first.second);
		}
    }

    for (auto& NodesPair : Capacitors->elements) {
        if (!Ports->FindElement(NodesPair.first.first)) {
			this->InsertElement(NodesPair.first.first);
		}
		if (!Ports->FindElement(NodesPair.first.second)) {
			this->InsertElement(NodesPair.first.second);
		}
    }

}

void ResistanceElements::InsertElement(std::string LineFromNetlist){
    std::istringstream iss(LineFromNetlist);
    char type;
    int index;
    int node1, node2;
    std::string value_str;
	double value;
    iss >> type >> index >> node1 >> node2 >> value_str;
	std::pair<int, int> nodes = {node1, node2};
	value = this->NetlistValueConverter(value_str);

	// Если резистор между узлами уже есть, обрабатываем параллельное 
	if (this->FindElement(node1, node2))
        this->elements[{node1, node2}] = 1./value;
	else
        this->elements[{node1, node2}] += 1./value;
}

void CapacitorsElements::InsertElement(std::string LineFromNetlist){
    std::istringstream iss(LineFromNetlist);
    char type;
    int index;
    int node1, node2;
    std::string value_str;
	double value;
    iss >> type >> index >> node1 >> node2 >> value_str;
	std::pair<int, int> nodes = {node1, node2};
	value = this->NetlistValueConverter(value_str);
	// Если резистор между узлами уже есть, обрабатываем параллельное 
	if (this->FindElement(node1, node2))
        this->elements[{node1, node2}] = value;
	else
        this->elements[{node1, node2}] += value;
}

double SchemeElements::NetlistValueConverter(std::string& line){
    //предполгаем что буква находится в конце строки
    char unit = line.back();
	
	if (isdigit(unit))
    	return std::stod(line.substr(0, line.length()));
	else {
        double base_value;
		base_value = std::stod(line.substr(0, line.length() - 1));
        switch (unit) {
            case 'p': return base_value * pow(10, -12);
            case 'n': return base_value * pow(10, -9);
            case 'u': return base_value * pow(10, -6);
            case 'm': return base_value * pow(10, -3);
            case 'k': return base_value * pow(10, 3);
            case 'M': return base_value * pow(10, 6);
            case 'G': return base_value * pow(10, 9);
            default :  return base_value; // Если нет суффикса, предполагаем, что последний символ — часть числа.
        }
    }
    	
    
}

void SchemeElements::DisplayElements() {
    for (auto& element: this->elements){
        std::cout << element.first.first << " " << element.first.second << " " << element.second << std::endl;
    }
}

bool SchemeElements::FindElement(int node1, int node2){
    if (this->elements.count({node1, node2}))
        return 1;
    return 0;
}

SchemeElements::~SchemeElements() {std::cout << "~SchemeElements()" << std::endl;}
ResistanceElements::~ResistanceElements() {std::cout << "~ResistanceElements()" << std::endl;}
CapacitorsElements::~CapacitorsElements() {std::cout << "~CapacitorsElements()" << std::endl;}


