# include <ofVec2f.h>
# include <BarnesHutTree.h>
# include <iostream>

using namespace std;

int main(int argc, char *argv[]){


    int N = 10000;
    vector < ofVec2f > points;

    for(int i=0; i<N; ++i){
        ofVec2f point(
                    rand() / (( float) RAND_MAX),
                    rand() / (( float) RAND_MAX)
                );
        points.push_back(point);
    }

    BarnesHutTree tree(points);

    ///////     

    ofVec2f force(0.f, 0.f);

    int n = 1000;
    float thetamax = 3.0f;
    float dtheta = thetamax/n;
    cout << "theta,F" << endl;
    for(int i=0; i<n+1; ++i){
        float theta = dtheta * i;
        ofVec2f force;
        tree.compute_force(points[0], force, theta);
        cout << theta << "," << (force.length()) << endl;
    }
}
