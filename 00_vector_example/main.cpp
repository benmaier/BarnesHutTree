# include <ofVec2f.h>
# include <iostream>

using namespace std;

int main(int argc, char *argv[]){

    ofVec2f vec(0.f, 0.f);

    cout << "vec = ofVec2f(0.f, 0.f); vec = " << vec << endl;
    vec += ofVec2f(4.f, 2.f);
    cout << "vec += ofVec2f(4.f, 2.f); vec = " << vec << endl;
    vec = vec * 2;
    cout << "vec = vec * 2; vec = " << vec << endl;
    vec = (1/2.0) * vec;
    cout << "vec = (1/2.0) * vec; vec = " << vec << endl;
    vec = vec / 2.f;
    cout << "vec = vec / 2.f; vec = " << vec << endl;


}
