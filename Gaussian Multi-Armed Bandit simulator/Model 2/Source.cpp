#include "NormalBandit.h"
#include "Experiment.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>  
#include <climits>
using namespace std;

int main() {

    cout << "~~~~~~~ Welcome to the Gaussian Multi-Armed Bandit simulator! ~~~~~~~" << endl;
    cout << "In order to proceed with the simulation I need:" << endl;
    cout << "* The number of arms" << endl;
    cout << "* The length of each run" << endl;
    cout << "* The number of runs" << endl;
    cout << "* The exploration strategy as an integer, where:" << endl;
    cout << "  * 0 - epsilon-greedy" << endl;
    cout << "  * 1 - Boltzmann" << endl;
    cout << "  * 2 - UCB" << endl;
    cout << "  * 3 - gradient bandit with softmax action preference" << endl;

    int N;
    int run_length;
    int n_runs;
    int exploration_strategy;
    float max_percentage_best_action = INT_MIN; //for reward computing and percentage of best action
    float max_pba = INT_MIN;
    int nr_step;

    cin >> N;
    cin >> run_length;
    cin >> n_runs;
    cin >> exploration_strategy;

    if (exploration_strategy > 3 || exploration_strategy < 0) {
        cout << endl << "**Unexpected number for the exploration strategy**" << endl;
        cout << endl << "**Please choose a number between 0 and 3**" << endl;
        return -1;
    }

    double var = 1;
    double epsilon = 0.1;
    double learning_rate = 0.1;
    double c = 0.1;
    double T = 0.1;

    double* re;
    int* op;
    double* ret = new double[n_runs * run_length];
    int* opt_action = new int[n_runs * run_length];
    double* means = new double[run_length]();
    double* means1 = new double[run_length]();
    double* percentage_best_action = new double[run_length]();
    double* stddev = new double[run_length]();

    double Qmax = 0.;
    ofstream myfile;
    myfile.open("data_normal.txt");
    myfile << "step   first_run   mean_reward_runs   std_reward_runs   percentage_opt_action" << endl;

    //  RUN LOOPS 
    for (int i = 0; i < n_runs; i++) {
        if (i % 100 == 0) {
            cout << "Run number " << i << endl;
        }

        NormalBandit b(N, epsilon, learning_rate, var, Qmax);
        Experiment e(epsilon, learning_rate, run_length);

        if (exploration_strategy == 0) {
            e.single_run(b);
        }
        else if (exploration_strategy == 1) {
            e.single_run_Boltzmann(b, T);

        }
        else if (exploration_strategy == 2) {
            e.single_run_UCB(b, c);

        }
        else if (exploration_strategy == 3) {
            e.single_run_gradient(b);

        }

        re = e.get_returns();
        op = e.get_opt_actions();

        if (i == 0 || i == n_runs - 1) {
            b.print_true_values();
        }
        for (int j = 0; j < run_length; j++) {
            ret[i * run_length + j] = *(re + j);
            opt_action[i * run_length + j] = *(op + j);
        }

        if (i == 0 || i == n_runs - 1) {
            b.print_q();
            b.print_action_preferences();
        }
    }

    // COMPUTE REWARD MEANS AND PERCENTAGE OF CORRECT ACTION 
    for (int j = 0; j < run_length; j++) {
        for (int i = 0; i < n_runs; i++) {
            means[j] += ret[i * run_length + j];
            if (opt_action[i * run_length + j] == 1) {
                percentage_best_action[j] += 1. / n_runs;
            }
            if (percentage_best_action[j] > max_percentage_best_action)
            {
                max_percentage_best_action = percentage_best_action[j];
            }
            if (max_pba != max_percentage_best_action) //keep first step where we get the best percentage
            {
                max_pba = max_percentage_best_action;
                nr_step = j;
            }
        }

        means[j] = means[j] / n_runs;
        for (int i = 0; i < n_runs; i++) {
            stddev[j] += (ret[i * run_length + j] - means[j]) * (ret[i * run_length + j] - means[j]);
        }
        stddev[j] = sqrt(stddev[j] / n_runs);
        myfile << j << " " << ret[j] << " " << means[j] << " " << stddev[j] << " " << percentage_best_action[j] << "\n";
    }
    cout << "Simulation data saved in data_normal.txt" << endl;
    myfile << "--------------------------------------------------------------------------------------------------------------------------" << endl;
    myfile << "The best percentage of optimal action selection for ";
    if (exploration_strategy == 0)
    {
        myfile << "epsilon-greedy is: " << max_percentage_best_action << ", at step: " << nr_step;
    }
    else if (exploration_strategy == 1)
    {
        myfile << "Boltzmann is: " << max_percentage_best_action << ", at step: " << nr_step;
    }
    else if (exploration_strategy == 2)
    {
        myfile << "UCB is: " << max_percentage_best_action << ", at step: " << nr_step;
    }
    else if (exploration_strategy == 3)
    {
        myfile << "gradient bandit with softmax action preference is: " << max_percentage_best_action << ", at step: " << nr_step;
    }
    myfile << endl << "--------------------------------------------------------------------------------------------------------------------------" << endl;
    
    delete[] ret;
    delete[] means;
    delete[] means1;
    delete[] percentage_best_action;
    delete[] stddev;
    delete[] opt_action;

    myfile.close();
    
    return 0;
}