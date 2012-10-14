#include "../Include/Poisson.h"

double U_Rand(double a, double b)		//    均匀分布   
{
	const int MAX_VAL = 32767;
	double x = rand()%MAX_VAL;
	return a + (b - a) * (x + 1) / (MAX_VAL + 1);   
}   
    
double P_Rand(double Lamda)				//    泊松分布   
{
	double x = -1, u;  
	double log1, log2;

	log1 = 0;
	log2 = -Lamda;

  do
  {
		u = U_Rand(0, 1);   
	   log1 += log(u);
		 x++;   
  }
  while(log1 >= log2);

  return x;   
}  