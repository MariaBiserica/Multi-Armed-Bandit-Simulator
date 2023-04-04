#include "BernoulliBandit.h"

BernoulliBandit::BernoulliBandit(const int n, double e, double l, double Qmax): Bandit(n, e, l) {

    for (int i=0; i<N; i++){
        true_values[i] = ((double) rand() / (RAND_MAX)); 
        // in this case true_values is p_a, the probability to get 1
        q[i] = Qmax;
        UCBvalues[i] = 10000;
        nt[i] = 0;
        preferences[i]  = 0;
        pii[i] = 0;
    }
    avg_reward = 0;

};

double BernoulliBandit::sample_return(int a){

    double r = 0;
    double randvar = r = ((double) rand() / (RAND_MAX));
    if (randvar < true_values[a]){
        r = 1;
    }
    return r;
    
};