# include <ofVec2f.h>
# include <BarnesHutTree.h>
# include <iostream>
# include <string>
# include <sstream>

using namespace std;

int main(int argc, char *argv[]){

    int N = 400;
    vector < ofVec2f > points;

    for(int i=0; i<N; ++i){
        ofVec2f point(
                    rand() / (( float) RAND_MAX),
                    rand() / (( float) RAND_MAX)
                );
        points.push_back(point);
    }

    BarnesHutTree tree(points);

    float theta = 0.15;
    vector < pair < float, size_t > > distances = tree.get_pairwise_distances(theta);

    for(int i=0; i<N-1; ++i){
        for(int j=i+1; j<N; ++j){
            float d = (points[i] - points[j]).length();
            cout << "0 " <<  d << " " << "1" << endl; 
        }
    }
    for(auto &dist: distances)
    {
       cout << "1 " << dist.first << " " << dist.second << endl;
    }
}
