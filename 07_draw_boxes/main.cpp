# include <ofVec2f.h>
# include <BarnesHutTree.h>
# include <iostream>

using namespace std;

void scan_tree(BarnesHutTree* node){

    if (node->is_leaf()){
        cout << (*(node->this_pos)).x << ","
             << (*(node->this_pos)).y << ","
             << "0,0" << endl;
    }
    if (node->is_internal_node() || node->is_leaf()){
        cout << (node->geom).left() << ","
             << (node->geom).bottom() << ","
             << (node->geom).width() << ","
             << (node->geom).height()
             << endl;

        for(int i=0; i<4; ++i){
            if ((node->subtrees).trees[i] != NULL)
                scan_tree((node->subtrees).trees[i]);
        }
    }
}

int main(int argc, char *argv[]){

    int N = 100;
    vector < ofVec2f > points;

    for(int i=0; i<N; ++i){
        ofVec2f point(
                    rand() / (( float) RAND_MAX),
                    rand() / (( float) RAND_MAX)
                );
        points.push_back(point);
    }

    BarnesHutTree tree(points);

    cout << "x,y,w,h" << endl;

    scan_tree(&tree);

}
