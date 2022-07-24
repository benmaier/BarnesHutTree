# include <ofVec2f.h>
# include <BarnesHutTree.h>
# include <iostream>
# include <algorithm>
#include <chrono>
using namespace std::chrono;

using namespace std;

void compute_force(
                 ofVec2f &force,
                 const ofVec2f &pos,
                 BarnesHutTree* tree,
                 float theta,
                 const float &mass = 1.f,
                 const float &gravitational_constant = 1.f
                 );

void compute_force(
                 ofVec2f &force,
                 const ofVec2f &pos,
                 BarnesHutTree* tree,
                 float theta,
                 const float &mass,
                 const float &gravitational_constant
                 )
{
    if (tree == NULL) return;

    auto _r = tree->this_pos;

    if (tree->is_leaf())
    {
        ofVec2f d = *(tree->this_pos) - pos;
        float norm = d.length();
        if (norm > 0)
            force += gravitational_constant * mass * (tree->total_mass) * d/pow(norm,3);
    }
    else
    {
        ofVec2f __r = tree->center_of_mass;
        ofVec2f d = (__r) - pos;
        float s = sqrt(tree->geom.width() * tree->geom.height()); // geometric mean of box dimensions
        float norm = d.length();
        if ((s/norm) < theta)
            force += gravitational_constant * mass * (tree->total_mass) * d/pow(norm,3);
        else
            for(auto &subtree: tree->subtrees.trees){
                if (subtree != NULL){
                    compute_force(force, pos, subtree, theta, mass, gravitational_constant);
                }
            }
    }
}

int main(int argc, char *argv[]){


    ///////     
    int n_meas = 1000;
    int n = 1000;
    float thetamax = 3.0f;
    float dtheta = thetamax/n;
    int N = 10000;
    vector < vector < float > > data;
    vector < vector < double > > time;

    for(int i = 0; i < n+1; ++i){
        vector < float > measurements(n_meas, 0.f);
        vector < double > time_measurements(n_meas, 0.f);
        data.push_back(measurements);
        time.push_back(time_measurements);
    }

    for(int meas = 0; meas < n_meas; ++meas)
    {
        vector < ofVec2f > points;

        for(int i=0; i<N; ++i){
            ofVec2f point(
                        rand() / (( float) RAND_MAX),
                        rand() / (( float) RAND_MAX)
                    );
            points.push_back(point);
        }

        BarnesHutTree tree(points);


        ofVec2f force(0.f, 0.f);

        float ref_force = 0.;
        for(int i=0; i<n+1; ++i){
            float theta = dtheta * i;
            float result;

            ofVec2f force;

            auto start = high_resolution_clock::now();

            compute_force(force, points[0], &tree, theta);

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start);
            auto elapsed = duration.count();
            if (i==0){
                ref_force = force.length();
                result = 1.0;
            }
            else
            {
                result = force.length() / ref_force;
            }
            data[i][meas] = result;
            time[i][meas] = elapsed;
        }
    }


    cout << "theta" << ","
         << "mean_relative_force" << "," 
         << "stddev_relative_force"  << ","
         << "median_relative_force" << ","
         << "lower_25_relative_force" << ","
         << "upper_75_relative_force"
         << "mean_time_mus" << "," 
         << "stddev_time_ns"  << ","
         << "median_time_ns" << ","
         << "lower_25_time_ns" << ","
         << "upper_75_time_ns"
         << endl;
    for(int i=0; i<n+1; ++i){
        float theta = dtheta * i;
        //

        float mean = 0.0;
        for(auto const &val: data[i]){
            mean += val;
        }
        mean /= n_meas;
        float var = 0.0;
        for(auto const &val: data[i]){
            var += pow(val-mean,2);
        }
        var /= (n_meas-1);
        float stddev = sqrt(var);

        sort(data[i].begin(), data[i].end());
        float i_l25 = (int) (n_meas / 4.0);
        float i_u75 = (int) (3.0 * n_meas / 4.0);
        float i_50 = (int) (2.0 * n_meas / 4.0);
        float l25 = data[i][i_l25];
        float u75 = data[i][i_u75];
        float med = data[i][i_50];
        //

        float tmean = 0.0;
        for(auto const &val: time[i]){
            tmean += val;
        }
        tmean /= n_meas;
        float tvar = 0.0;
        for(auto const &val: time[i]){
            tvar += pow(val-tmean,2);
        }
        tvar /= (n_meas-1);
        float tstddev = sqrt(tvar);

        sort(time[i].begin(), time[i].end());
        float tl25 = time[i][i_l25];
        float tu75 = time[i][i_u75];
        float tmed = time[i][i_50];

        //
        cout << theta << "," 
             << mean << "," << stddev << ","
             << med << "," 
             << l25 << "," << u75 << ","
             << tmean << "," << tstddev << ","
             << tmed << "," 
             << tl25 << "," << tu75
             << endl;
    }
}
