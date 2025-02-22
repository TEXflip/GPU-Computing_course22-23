#ifndef LAB1_EX2_LIB
#define LAB1_EX2_LIB

#define STR(s) #s
#define XSTR(s) STR(s)
#define dtype double

// Put here the declaration of mu_fn and sigma_fn

double mean(dtype *v, int n);

double variance(dtype *v, double mean, int n);

// ----------------------------------------------

#endif
