#include "subnets.hpp"

SubNet::SubNet(
        std::vector<int>& component, std::map<int, 
        std::vector<int>>& port_connect,
        std::shared_ptr<SchemeElements> _Resistance,
        std::shared_ptr<SchemeElements> _Capacitors
    ): Resistance{_Resistance}, Capacitors{_Capacitors} {
    std::cout << "Subnet create" << std::endl;
    for (auto& nodes: component){
        std::cout << nodes << " ";
    }
    std::cout << std::endl;
    this->PortsNode.resize(0);
    this->FindPortsSubnet(port_connect);
}

void SubNet::FindPortsSubnet(std::map<int, std::vector<int>>& port_connect){
    std::map<int, int> visited_port;
    for (auto& node : this->IntersNode) 			
        if (port_connect.count(node))
            for (const auto& ports: port_connect[node])
                if (!visited_port.count(ports))
                    visited_port[ports] = ports;


}


SubNets::SubNets(std::shared_ptr<SchemeElements> _Resistance, 
                 std::shared_ptr<SchemeElements> _Capacitors, 
                 std::shared_ptr<SchemeNodes> Ports): Resistance{_Resistance}, Capacitors{_Capacitors}
{
    for (const auto&  nodes: Resistance->elements) {
        int node1 = nodes.first.first;
        int node2 = nodes.first.second;
        bool f1 = Ports->FindElement(node1); // найден ли узел в портовых или нет 
        bool f2 = Ports->FindElement(node2); // найден ли узел в портовых или нет 
        if (!f1 && !f2)
        {
            adjacencyList[node1].push_back(node2);
            adjacencyList[node2].push_back(node1); 
        }
        else if (f1 && f2)
        {
            this->ports_subnet[{node1, node2}] = {node1, node2};
        }
        else if (f2){
            port_connect[node1].push_back(node2);
        }
        else {
            port_connect[node2].push_back(node1);

        }
    }

    for (const auto&  nodes: Capacitors->elements) {
        int node1 = nodes.first.first;
        int node2 = nodes.first.second;
        bool f1 = Ports->FindElement(node1); // найден ли узел в портовых или нет 
        bool f2 = Ports->FindElement(node2); // найден ли узел в портовых или нет 
        if (!f1 && !f2)
        {
            adjacencyList[node1].push_back(node2);
            adjacencyList[node2].push_back(node1); 
        }
        else if (f1 && f2)
        {
            this->ports_subnet[{node1, node2}] = {node1, node2};
        }
        else if (f2){
            port_connect[node1].push_back(node2);
        }
        else {
            port_connect[node2].push_back(node1);

        }
    }
    this->SubnetsList.resize(0);
    this->CreateSubnets();

}

void SubNets::CreateSubnets(){
    std::unordered_set<int> visited;
    for (auto& nodes : this->adjacencyList) {
        if (!visited.count(nodes.first)) {
            std::vector<int> component;
            dfs(nodes.first, adjacencyList, visited, component);
            this->SubnetsList.push_back(std::make_shared<SubNet>(component, this->port_connect));
        }
    }
}

void SubNets::dfs(int node, std::map<int, std::vector<int>>& adjacencyList,
             std::unordered_set<int>& visited, std::vector<int>& component) 
{
    visited.insert(node);
    component.push_back(node);
    for (auto& neighbor : adjacencyList[node]) {
        if (visited.find(neighbor) == visited.end()) {
            dfs(neighbor, adjacencyList, visited, component);
        }
    }
}