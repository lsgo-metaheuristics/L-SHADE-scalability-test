/*
  L-SHADE implemented by C++ for Special Session & Competition on Real-Parameter Single Objective Optimization at CEC-2014

  Version: 1.1  Date: 9/Jun/2014
  Written by Ryoji Tanabe (rt.ryoji.tanabe [at] gmail.com)
*/
#define _USE_MATH_DEFINES

#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdlib.h>
#include<iostream>
#include <iomanip>
#include <string.h>
#include <vector>
#include<math.h>
#include "funsoft.h"

using namespace std;

typedef  double variable;
typedef variable *Individual;

extern int g_function_number;
extern int g_problem_size;
extern unsigned int g_max_num_evaluations;
extern int function_name;

extern int g_pop_size;
extern int g_memory_size;
extern double g_p_best_rate;
extern double g_arc_rate;

void SISOCO_test_func(double *x, Fitness *f, int nx, int mx, int func_num);
void SICOCO_SetParameters(Fitness &optimum, double &boundMin, double &boundMax, int func_num);

class searchAlgorithm {
public:
  virtual Fitness run() = 0;
protected:
  void evaluatePopulation(const vector<Individual> &pop, vector<Fitness> &fitness);
  void initializeFitnessFunctionParameters();

  void initializeParameters();
  Individual makeNewIndividual();
  void modifySolutionWithParentMedium(Individual child, Individual parent);
  void setBestSolution(const vector<Individual> &pop, const vector<Fitness> &fitness, Individual &bsf_solution, Fitness &bsf_fitness);

  //Return random value with uniform distribution [0, 1)
  inline double randDouble() {
    return (double)rand() / (double) RAND_MAX;
  }

  /*
    Return random value from Cauchy distribution with mean "mu" and variance "gamma"
    http://www.sat.t.u-tokyo.ac.jp/~omi/random_variables_generation.html#Cauchy
  */
  inline double cauchy_g(double mu, double gamma) {
    return mu + gamma * tan(M_PI*(randDouble() - 0.5));
  }

  /*
    Return random value from normal distribution with mean "mu" and variance "gamma"
    http://www.sat.t.u-tokyo.ac.jp/~omi/random_variables_generation.html#Gauss
  */
  inline double gauss(double mu, double sigma){
    return mu + sigma * sqrt(-2.0 * log(randDouble())) * sin(2.0 * M_PI * randDouble());
  }

  //Recursive quick sort with index array
  template<class VarType>
    void sortIndexWithQuickSort(VarType array[], int first, int last, int index[]) {
    VarType x = array[(first + last) / 2];
    int i = first;
    int j = last;
    VarType temp_var = 0;
    int temp_num = 0;

    while (true) {
      while (array[i] < x) i++;    
      while (x < array[j]) j--;      
      if (i >= j) break;

      temp_var = array[i];
      array[i] = array[j];
      array[j] = temp_var;

      temp_num = index[i];
      index[i] = index[j];
      index[j] = temp_num;

      i++;
      j--;
    }

    if (first < (i -1)) sortIndexWithQuickSort(array, first, i - 1, index);  
    if ((j + 1) < last) sortIndexWithQuickSort(array, j + 1, last, index);    
  }
  
  int function_number;
  int problem_size;
  variable max_region;
  variable min_region;
  Fitness optimum;
  // acceptable error value
  Fitness epsilon;
  unsigned int max_num_evaluations;
  int pop_size;
};

class LSHADE: public searchAlgorithm 
{
public:
  ~LSHADE();
  virtual Fitness run();
  void setSHADEParameters();
  void reducePopulationWithSort(vector<Individual> &pop, vector<Fitness> &fitness);
  void operateCurrentToPBest1BinWithArchive(const vector<Individual> &pop, Individual child, int &target, int &p_best_individual, variable &scaling_factor, variable &cross_rate, const vector<Individual> &archive, int &arc_ind_count);

  vector <Individual> pop; 
  vector <Individual> children;
  vector <Individual> archive;
  variable *pop_sf;
  variable *pop_cr;
  Individual bsf_solution;
  int *sorted_array;
  Fitness *temp_fit;
  int arc_size;
  double arc_rate;
  variable p_best_rate;
  int memory_size;
  int reduction_ind_num;
};

#endif


