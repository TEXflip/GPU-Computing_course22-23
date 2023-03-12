#include "../include/lab1_ex2_lib.h"

// Put here the implementation of mu_fn and sigma_fn


double mean(dtype *v, int n){
	double sum = 0;
	for (int i = 0; i < n; i++)
		sum += (double) v[i];
	return sum / (double)n;
}

double variance(dtype *v, double mean, int n){
	double sum = 0, mu_diff;
	for (int i = 0; i < n; i++){
		mu_diff = (((double)v[i]) - mean);
		sum += mu_diff*mu_diff;
	}
	return sum/n;
}

// -------------------------------------------------
