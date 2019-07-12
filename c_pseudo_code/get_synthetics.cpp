
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;


// number of components
static int NC = 2;

// number of stations
static int NS = 20;

// number of time samples
static int NT = 950;

// number of Green's functions
static int NG = 6;

// number of moment tensors
static int NM = 50000;

static int min_shift = -100;
static int max_shift = 100;

// length of padding
int NP = max_shift - min_shift + 1;

// length of padded records
int NTP = NT + max_shift - min_shift + 1;




void get_synthetics(double greens[], double synthetics[], double mt[]) {

    for (int j=0 ; j<NC*NS*NTP; j++) { 
        synthetics[j] = 0.;
    }

    for (int i=0 ; i<NG; i++) {
        for (int j=0 ; j<NC*NS*NTP; j++) {
            synthetics[j] += greens[i*NC*NS*NTP + j] * mt[i];
        }
    }
}


int main() {

    double *data;
    double *synthetics;
    double *mask;
    double *greens;
    double *corr;
    double *corr_sum;
    int *shifts;
    double *mt;
    double *results;

    data = new double [NC*NS*NT];
    synthetics = new double [NC*NS*NT];
    mask = new double [NC*NS*NT];

    greens = new double [NG*NC*NS*NT];
    corr = new double [NG*NC*NS*NT];
    shifts = new int [NC*NS];

    corr_sum = new double [3*NS*NT];

    mt = new double [NG*NM];
    results = new double [NM];


    //populate_array(data, NC*NS*NT);
    //populate_array(greens, NG*NC*NS*NT);

    std::clock_t start;
    double duration;

    start = std::clock();


    for( int i = 0; i < NM; i++ ) {
        //cout << "value of i: " << i << endl;
        get_synthetics(greens, synthetics, &mt[i]);
    }

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"seconds: "<< duration <<'\n';


    return 0; 

}

