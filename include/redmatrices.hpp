#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SparseCholesky>
#include <Eigen/SparseCore>
#include "subnets.hpp"

#pragma once 

struct ConductMatrices{
public: 
    ConductMatrices (std::shared_ptr<SubNet> subnet); //принимает подсеть
    bool InterConductisPositive(); // проверка положительности матрицы внутренней проводимости 
    
    Eigen::SparseMatrix<double> Gii; // матрица внутренней проводимости 
    Eigen::SparseMatrix<double> Gio; // матрица внутренние-внешние
    Eigen::SparseMatrix<double> Goi; // матрица внешние-внутренние
    Eigen::SparseMatrix<double> Goo; // матрица портовая

};


struct CapacitiesMatrices{
public: 
    CapacitiesMatrices(std::shared_ptr<SubNet> subnet);
    Eigen::SparseMatrix<double> Cii; // матрица внутренней проводимости 
    Eigen::SparseMatrix<double> Cio; // матрица внутренние-вне	шние
    Eigen::SparseMatrix<double> Coi; // матрица внешние-внутренние
    Eigen::SparseMatrix<double> Coo; // матрица портовая

};


