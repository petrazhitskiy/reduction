#include "reductionsubnet.hpp"


//SCHEMEREDUCTION
SchemeReduction::SchemeReduction(std::shared_ptr<SubNets> Subnets)
{
    for (int i = 0; i < Subnets->SubnetsList.size();++i){
        this->Conduct  = std::make_shared<ConductMatrices>(Subnets->SubnetsList[i]);
        this->Capacity = std::make_shared<CapacitiesMatrices>(Subnets->SubnetsList[i]); 
        this->Holetsky = std::make_unique<HoletskiyReduction>(this->Capacity, this->Conduct);
        this->EigenRed = std::make_unique<EigenReduction>(this->Capacity, this->Conduct);
    }
}


//HOLETSKIY
HoletskiyReduction::HoletskiyReduction(
        std::shared_ptr<CapacitiesMatrices>  _Capacity,
        std::shared_ptr<ConductMatrices>     _Conduct)
{
    this->Capacity = _Capacity;
    this->Conduct  = _Conduct;
    this->HoletskiyForConductis();
    this->HoletskiyForCapacities();
}

HoletskiyReduction::~HoletskiyReduction(){}
void HoletskiyReduction::HoletskiyForCapacities(){}
void HoletskiyReduction::HoletskiyForConductis(){}
void HoletskiyReduction::InverseSparseMatrix(
            Eigen::SparseMatrix<double>& Matrix, 
            Eigen::SparseMatrix<double>& InverseMatrix){}

//EIGENREDUCTION
EigenReduction::EigenReduction(
        std::shared_ptr<CapacitiesMatrices>  _Capacity,
        std::shared_ptr<ConductMatrices>     _Conduct)
{
    this->Capacity = _Capacity;
    this->Conduct  = _Conduct;
    this->FindAllEigenvalues();
}

void EigenReduction::EigenvaluesSeach(
    std::shared_ptr<CapacitiesMatrices>  Capacity,
    std::shared_ptr<CapacitiesMatrices>  Conduct)
{
    
}

Eigen::SparseMatrix<double> EigenReduction::concatenateCols(
    const Eigen::SparseMatrix<double>& mat, 
    const std::vector<int>& indicesToKeep) 
{

}

void EigenReduction::FindEigenvaluesSparseMatrix(
    Eigen::SparseMatrix<double>& Cii1)
{

}




