# include <ofVec2f.h>
# include <iostream>

using namespace std;

int main(int argc, char *argv[]){

    ofVec2f zero(0.f, 0.f);
    ofVec2f vec(1.f, 1.5f);
    ofVec2f tri(3.f, 4.f);

    cout << "ofVec2f zero(); zero = " << zero << endl;
    cout << "ofVec2f vec(1.f, 1.5f); vec = " << vec << endl;
    vec += ofVec2f(3.f, 0.5f);
    cout << "vec += ofVec2f(3.f, 0.5f); vec = " << vec << endl;
    vec = vec * 2;
    cout << "vec = vec * 2; vec = " << vec << endl;
    vec = (1/2.0) * vec;
    cout << "vec = (1/2.0) * vec; vec = " << vec << endl;
    vec = vec / 2.f;
    cout << "vec = vec / 2.f; vec = " << vec << endl;
    cout << "ofVec2f tri(3.f, 4.f); tri.length() = " << tri.length() << endl;
}
