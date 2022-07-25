# BarnesHutTree

Simple C++-11 implementation for 2D Barnes-Hut Trees. Based on openFrameworks syntax, but usable without openFrameworks. Implemented for `float`, but easily adaptable to `double` by replacing types (specifically didn't use templates to be more beginner-friendly).

Implemented after ["The Barnes-Hut Algorithm"](http://arborjs.org/docs/barnes-hut) by Tom Ventimiglia, Kevin Wayne and Christian Swinehart, which is an adaption of ["Barnes-Hut Galaxy Simulator"](https://www.cs.princeton.edu/courses/archive/fall03/cs126/assignments/barnes-hut.html) by Tom Ventimiglin and Kevin Wayne.

```cpp
#include <vector>
#include <ofVec2f.h>
#include <BarnesHutTree.h>

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
}
```

## License

This project is licensed under the [MIT License](https://github.com/benmaier/epipack/blob/master/LICENSE).

The class `ofVec2f` was adapted from the [openFrameworks library](https://github.com/openframeworks/openFrameworks/blob/master/libs/openFrameworks/math/ofVec2f.h) under the [MIT License](https://github.com/openframeworks/openFrameworks/blob/master/LICENSE.md).

![fixedpoints](https://github.com/benmaier/epipack/raw/master/img/fixed_points.png)

## Examples

### Simple tree

see [01\_tree\_example](./01_tree_example).


### ofVec2f

```cpp
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
```

```
ofVec2f zero(); zero = 0, 0
ofVec2f vec(1.f, 1.5f); vec = 1, 1.5
vec += ofVec2f(3.f, 0.5f); vec = 4, 2
vec = vec * 2; vec = 8, 4
vec = (1/2.0) * vec; vec = 4, 2
vec = vec / 2.f; vec = 2, 1
ofVec2f tri(3.f, 4.f); tri.length() = 5
```
