# include <ofVec2f.h>
# include <BarnesHutTree.h>
# include <iostream>

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
        compute_force(force, points[0], &tree, theta);
        cout << theta << "," << (force.length()) << endl;
    }
}
