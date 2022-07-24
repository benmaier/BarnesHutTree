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

    // coordinates of points in http://arborjs.org/docs/barnes-hut,
    // or https://www.cs.princeton.edu/courses/archive/fall03/cs126/assignments/barnes-hut.html
    // respectively
    ofVec2f A(0.2, 0.76);
    ofVec2f B(0.5+1/8.0+0.01, 7/8.0 + 0.01);
    ofVec2f C(0.5 + 0.02, 0.75 + 0.02);
    ofVec2f D(0.75 + 0.01, 0.75 - 0.02);
    ofVec2f E(0.5 - 0.02, 0.5 - 0.02);
    ofVec2f F(0.1, 0.1);
    ofVec2f G(3/8.0+0.02, 0.15);
    ofVec2f H(5/8.+0.01, 0.12);

    vector < ofVec2f > points;

    points.push_back(A);
    points.push_back(B);
    points.push_back(C);
    points.push_back(D);
    points.push_back(E);
    points.push_back(F);
    points.push_back(G);
    points.push_back(H);

    Extent box(0.f, // origin x
               0.f, // origin y
               1.f, // width
               1.f  // height
               );

    BarnesHutTree tree(box);

    float mass = 1.f;
    int id = 0;

    for(auto &point: points){
        tree.insert(point,mass,id);
        ++id;
    }

    ///////     

    ofVec2f force(0.f, 0.f);
    float theta = 0.5;
    compute_force(force, A, &tree, theta);

    cout << force << endl;


}
