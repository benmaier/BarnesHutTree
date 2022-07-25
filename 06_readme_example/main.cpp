#include <vector>
#include <ofVec2f.h>
#include <BarnesHutTree.h>
#include <iostream>

int main(){
    int n = 1000;
    vector < ofVec2f > positions;
    for(int i=0; i<n; ++i){
        positions.push_back(
            ofVec2f(
                     rand() / (float) RAND_MAX,
                     rand() / (float) RAND_MAX
            )
        );
    }

    BarnesHutTree tree(positions);
    ofVec2f force; // 2d-vector (0, 0)
    tree.compute_force(ofVec2f(0.9f,0.9f), force);
    float force_abs = force.length();

    cout << force_abs << endl;
}
