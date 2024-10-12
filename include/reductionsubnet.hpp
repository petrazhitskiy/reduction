#include <iostream>
#include <unordered_map>
#include <memory>
#include <locale>

#include "subnets.hpp"
#include "redmatrices.hpp"
#include "subnets.hpp"

#pragma once 

class HoletskiyReduction;
class EigenReduction;

class SchemeReduction{
public:
    SchemeReduction(std::shared_ptr<SubNets> Subnets);
    ~SchemeReduction();                
private:
    std::shared_ptr<ConductMatrices>     Conduct;
    std::shared_ptr<CapacitiesMatrices>  Capacity;
    std::unique_ptr<HoletskiyReduction>  Holetsky;
    std::unique_ptr<EigenReduction>      EigenRed;
};


// Преобразование Холецкого
class HoletskiyReduction {
public:
    HoletskiyReduction(
        std::shared_ptr<CapacitiesMatrices>  Capacity,
        std::shared_ptr<ConductMatrices>     Conduct
        );
    ~HoletskiyReduction();
private:
    void HoletskiyForConductis();
    void HoletskiyForCapacities();
    void  InverseSparseMatrix(
            Eigen::SparseMatrix<double>& Matrix, 
            Eigen::SparseMatrix<double>& InverseMatrix
        );
    
    std::shared_ptr<ConductMatrices>     Conduct;
    std::shared_ptr<CapacitiesMatrices>  Capacity;

};


// Преобразование Собственных значений
class EigenReduction{
public:
    EigenReduction(
        std::shared_ptr<CapacitiesMatrices>  Capacity,
        std::shared_ptr<ConductMatrices>     Conduct
        );
private:
    void EigenvaluesSeach(
            std::shared_ptr<CapacitiesMatrices>  Capacity,
            std::shared_ptr<CapacitiesMatrices>  Conduct
        );

    void FindAllEigenvalues();

    Eigen::SparseMatrix<double> concatenateCols(
            const Eigen::SparseMatrix<double>& mat, 
            const std::vector<int>& indicesToKeep
        );

    void FindEigenvaluesSparseMatrix(
            Eigen::SparseMatrix<double>& Cii1
        );

    std::shared_ptr<ConductMatrices>     Conduct;
    std::shared_ptr<CapacitiesMatrices>  Capacity;

};

// класс для выгрузки редуцированной подсети в netlist 
// возможно будет shred_mtp для conduct_for_netlist и cap_for_netlist 
// для того чтобы при параллельном исполнее была возможность атоматрного доступа к данной переменной

class UnloadToNetlist {
    struct nodevalues
    {
        int node1; // номер первого узла
        int node2; // номер первого узла
        double values; 
    };  

    void UnloadingToMapCapacity(Eigen::SparseMatrix<double>& Cii, Eigen::SparseMatrix<double>& Cio, 
                        Eigen::SparseMatrix<double>& Coi, Eigen::SparseMatrix<double>& Coo, 
                        std::vector<int>& portsformatrix, std::vector<int>& intersformatrix, std::map<std::pair<int, int>, nodevalues>& conductfornetlist);


    void UnloadingToMapConduct(Eigen::SparseMatrix<double>& Gii, Eigen::SparseMatrix<double>& Goo, Eigen::SparseMatrix<double>& Gio,
                                    std::vector<int>& portsformatrix, std::vector<int>& intersformatrix, 
                                    std::map<std::pair<int, int>, nodevalues>& conductfornetlist);

    void RunNunziroElementsCond(Eigen::SparseMatrix<double>& Mii, 
                                Eigen::SparseMatrix<double>& Moo,
                                Eigen::SparseMatrix<double>& Mio,
                                std::vector<int>& ports, std::vector<int>& inters,  
                                std::map<std::pair<int, int>, nodevalues>& conductfornetlist);

    void RunNunziroElementsCap(Eigen::SparseMatrix<double>& Mii, 
                                Eigen::SparseMatrix<double>& Mio,
                                Eigen::SparseMatrix<double>& Moi,
                                Eigen::SparseMatrix<double>& Moo,
                                std::vector<int>& ports, std::vector<int>& inters,  
                                std::map<std::pair<int, int>, nodevalues>& conductfornetlist);



};

//нужно пройтись по каждой подсети и проделать над ней некоторые операции 

//          1. для каждой подсети сформировать матрицы проводимостей 
//          2. если матрица узлов пустая то выгружаем в нетлист 
//          3. если матрица проводимостей не полложительно определена то заполняем нетлист
//          4. Преобразование холецкого 
//          5. Преобразование на основе собственных значений
//          6. Заполнить новую матрицу 
//          7. Заполнить матрицу в netlist


//какие нашел варианты 

// 1. Не создавать отдельные классы для редукции а сделать методы для педукции частью класса сети 
//      но в этом случае нет явного вызова редукции и нелья остановиться на конерктном шаге


// 2. Отдельный класс для редукции подсети
//      Класс редукции принимаеи подсхему и выпроняет над ней действия 
//      думаю что процесс можно разделить на несколько этапов только 
//      создаем класс для матрци проводимости и емкости 
//      подсеть содержит класс который хранит каждый класс этих матриц 
//      например C (cii, cio, coi, coo) также для G
//      в классе редукции принимаем указатель на каждую из матриц
//      после этого выполяем нужные преразовани