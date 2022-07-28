# include <ofVec2f.h>
# include <BarnesHutTree.h>
# include <iostream>
# include <string>
# include <sstream>

using namespace std;

const vector < string > _QUADS = {" (nw)", " (ne)", " (se)", " (sw)"};
const vector < string > _POINTS = {"A", "B", "C", "D", "E", "F", "G", "H"};

void get_tree_str(BarnesHutTree* node,
                std::ostringstream &ss,
                string indent = "",
                string quad = ""
               ){

    
    ss << indent << "+-" << quad << " ";

    if (node->is_leaf()){
        ss << _POINTS[node->this_id]  << " (" << *(node->this_pos) << ")" << endl;
    }
    if (node->is_internal_node()){
        ss << "CM = " << node->center_of_mass << "; " << "M = " << node->total_mass << "; "
           << "n = " << node->number_of_contained_points << endl;

        int i = 0;
        for(auto &subtree: node->subtrees.trees){
            if (subtree != NULL)
                get_tree_str(subtree,ss,indent + "| ",_QUADS[i]);
            ++i;
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

    std::ostringstream ss;
    get_tree_str(&tree, ss);

    cout << ss.str();


}
