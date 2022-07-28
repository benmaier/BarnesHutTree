# include <ofVec2f.h>
# include <BarnesHutTree.h>
# include <iostream>
# include <string>
# include <sstream>

using namespace std;

int main(int argc, char *argv[]){

    int N = 1000;
    vector < ofVec2f > points;

    for(int i=0; i<N; ++i){
        ofVec2f point(
                    rand() / (( float) RAND_MAX),
                    rand() / (( float) RAND_MAX)
                );
        points.push_back(point);
    }

    BarnesHutTree tree(points);

    ostringstream ss;
    tree.get_tree_str(ss);

    cout << ss.str();


}
