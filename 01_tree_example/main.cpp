# include <ofVec2f.h>
# include <BarnesHutTree.h>
# include <iostream>

using namespace std;

void scan_tree(BarnesHutTree* node){

    if (node->is_leaf()){
        cout << "this node is a leaf and carries data with id = " << node->this_id 
             << " and position = " << *(node->this_pos)
             << endl << endl;
    }
    if (node->is_internal_node()){
        if (node->parent == NULL)
            cout << "this node is the root node" << endl;

        cout << "this node is an internal node with " << (node->subtrees).occupied_trees
             << " occupied quadrants";
        if ((node->subtrees).occupied_trees > 0){
            cout << " (";
            for(int i=0; i<4; ++i){
                if ((node->subtrees).trees[i] != NULL)
                    cout << i << ", ";
            }
            cout << ")" << endl;
        }
        cout << "center of mass = " << node->center_of_mass << endl;
        cout << "total mass = " << node->total_mass << endl;
        cout << endl;

        for(int i=0; i<4; ++i){
            if ((node->subtrees).trees[i] != NULL)
                scan_tree((node->subtrees).trees[i]);
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

    scan_tree(&tree);


}
