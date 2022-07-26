# BarnesHutTree

Simple C++-11 implementation for 2D Barnes-Hut trees. Based on openFrameworks syntax, but usable without openFrameworks. Implemented for `float`, but easily adaptable to `double` by replacing types (specifically didn't use templates to be more beginner-friendly).

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


## Usage

### Define box

```cpp
Extent box(0.f, // origin-x
           0.f, // origin-y
           1.f, // width
           1.f  // height
          );
```

### Define tree

```cpp
BarnesHutTree tree(box);
```

### Insert location


```cpp
tree.insert(ofVec2f(0.2,0.3));
```

This will default to `mass = 1` and `id = -1`.

### Insert location with explicit mass and id

```cpp
int id = 0;
float mass = 2.f;
tree.insert(ofVec2f(0.2,0.3),  mass, id);
```

### Construct tree from positions right away

```cpp
vector <ofVec2f> positions
positions.push_back(ofVec2f(2.4, 6.0));
positions.push_back(ofVec2f(1.4, 3.1));

BarnesHutTree tree(positions);
```

### Construct tree from positions and masses

```cpp
vector <ofVec2f> positions;
positions.push_back(ofVec2f(2.4, 6.0));
positions.push_back(ofVec2f(1.4, 3.1));

vector <ofVec2f> masses;
masses.push_back(1.3);
masses.push_back(3.1);
BarnesHutTree tree(positions, masses);
```

### Construct tree, insert positions afterwards

```cpp
BarnesHutTree tree(box);
tree.insert_positions(positions);
```

### Construct tree, insert positions and masses afterwards

```cpp
BarnesHutTree tree(box);
tree.insert_positions(positions);
tree.insert_positions_and_masses(positions, masses);
```

### Compute force on position

```cpp
ofVec2f force; // 0-vector
ofVec2f loc(0.2, 0.4);
tree.compute_force(loc, force); // defaults to theta = 0.5
```

### Compute force with controlled theta

Referring to theta as [defined here](http://arborjs.org/docs/barnes-hut).

```cpp
float theta = 0.3;
tree.compute_force(loc, force, theta); 
```

### Scale the force

#### Gravitational attractive force

```cpp
ofVec2f force; // 0-vector
float G = 1.f;
float loc_mass = 2.f;
tree.compute_force(loc, force, theta); 

force = force * G * loc_mass;
```

#### Electro-static repulsive force

```cpp
ofVec2f force; // 0-vector
float Z = -1.f;
float loc_charge = 2.f;
tree.compute_force(loc, force, theta); 

force = force * Z * loc_charge;
```

### Access a tree node's subtrees

```cpp
tree.subtrees.trees // this is a vector < BarnesHutTree * >
                    // and empty subtrees are NULL
```

### Check if tree node is internal or leaf or empty

```cpp
tree.is_leaf();
tree.is_internal_node();
tree.is_empty();
```

### Access a tree node's box (geometry)

```cpp
tree.geom;

tree.geom.get_bottom_left();
tree.geom.get_top_right();
tree.geom.get_top_left();
tree.geom.width();
tree.geom.height();
```

## Examples

### Simple tree construction

See [01\_tree\_example](./01_tree_example/main.cpp).

```cpp
# include <ofVec2f.h>
# include <BarnesHutTree.h>
# include <iostream>

using namespace std;


int main(int argc, char *argv[]){

    // coordinates of points in http://arborjs.org/docs/barnes-hut,
    // or https://www.cs.princeton.edu/courses/archive/fall03/cs126/assignments/barnes-hut.html
    // respectively
    vector < ofVec2f > points;

    points.push_back(ofVec2f(0.2, 0.76));
    points.push_back(ofVec2f(0.5+1/8.0+0.01, 7/8.0 + 0.01));
    points.push_back(ofVec2f(0.5 + 0.02, 0.75 + 0.02));
    points.push_back(ofVec2f(0.75 + 0.01, 0.75 - 0.02));
    points.push_back(ofVec2f(0.5 - 0.02, 0.5 - 0.02));
    points.push_back(ofVec2f(0.1, 0.1));
    points.push_back(ofVec2f(3/8.0+0.02, 0.15));
    points.push_back(ofVec2f(5/8.+0.01, 0.12));

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
}
```

### Simple tree traversal and data access

See [01\_tree\_example](./01_tree_example/main.cpp).

```cpp
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
            int i = 0;
            for(auto &subtree: node->subtrees.trees){
                if (subtree != NULL)
                    cout << i << ", ";
                ++i;
            }
            cout << ")" << endl;
        }
        cout << "center of mass = " << node->center_of_mass << endl;
        cout << "total mass = " << node->total_mass << endl;
        cout << endl;

        for(auto &subtree: node->subtrees.trees){
            if (subtree != NULL)
                scan_tree(subtree);
        }
    }
}
```

### Compute force

See [02\_force\_example](./02_force_example/main.cpp).

```cpp
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
```

### Generate data to draw tree as boxes

See [07\_draw\_boxes](./07_draw_boxes/main.cpp).

```cpp
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

        for(auto &subtree: (node->subtrees).trees){
            if (subtree != NULL)
                scan_tree(subtree);
        }
    }
}

```

Then generate csv-data as

```cpp
cout << "x,y,w,h" << endl;
scan_tree(&tree);
```

Plot with Python script in [07\_draw\_boxes](./07_draw_boxes/main.cpp).

![pointsinboxes](https://github.com/benmaier/BarnesHutTree/raw/main/07_draw_boxes/boxes.png)



### Test the accuracy and duration of force computation depending on theta

See [05\_theta\_scan\_statistics](./05_theta_scan_statistics/).

Testing (i) how accurate and (ii) how fast the computation of force is on a single point,
depending on the `theta`-parameter.

![accuracy-and-time](https://github.com/benmaier/BarnesHutTree/raw/main/05_theta_scan_statistics/accuracy_and_time.png)

### ofVec2f

See [00\_vector\_example](./00_vector_example//main.cpp).

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

Output:

```
ofVec2f zero(); zero = 0, 0
ofVec2f vec(1.f, 1.5f); vec = 1, 1.5
vec += ofVec2f(3.f, 0.5f); vec = 4, 2
vec = vec * 2; vec = 8, 4
vec = (1/2.0) * vec; vec = 4, 2
vec = vec / 2.f; vec = 2, 1
ofVec2f tri(3.f, 4.f); tri.length() = 5
```
