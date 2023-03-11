#ifndef LAB1_EX2_LIB
#define LAB1_EX2_LIB

#define STR(s) #s
#define XSTR(s) STR(s)
#define dtype int

// Put here the declaration of mu_fn and sigma_fn

float mean(int *v, int n);

float variance(int *v, float mean, int n);

// ----------------------------------------------

#endif
