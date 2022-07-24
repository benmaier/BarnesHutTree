//
//  BarnesHutTree.hpp
//  QuadTreeIllustrator
//
//  Created by Ben F. Maier on 09.07.22.
//

#ifndef BarnesHutTree_h
#define BarnesHutTree_h

#include <ofVec2f.h> // comment this out if you want to use this codebase in openFrameworks
// #include <ofMain.h> //comment this in if you want to use this codebase in openFrameworks 
#include <stdio.h>
#include <vector>

const int _NW = 0;
const int _NE = 1;
const int _SE = 2;
const int _SW = 3;

using namespace std;

// reserve name to allow circular reference in class SubTrees
class BarnesHutTree;

class SubTrees
{
  public:
    size_t occupied_trees;
    std::vector< BarnesHutTree* > trees;

    SubTrees(){

        // initially, the node carries no subtrees
        occupied_trees = 0;
        
        // therefore, all quadrant pointers point to nothing
        trees.clear();
        trees.push_back(NULL);
        trees.push_back(NULL);
        trees.push_back(NULL);
        trees.push_back(NULL);
    }
    
    ~SubTrees(){
        // delete all subtrees that were created in runtime
        if (trees[3]) delete trees[3];
        if (trees[2]) delete trees[2];
        if (trees[1]) delete trees[1];
        if (trees[0]) delete trees[0];
    }
    
    // add a new tree to one of the quadrants,
    // where iqad corresponds to the mapping above
    void add_tree(int iquad, BarnesHutTree* tree){
        occupied_trees += 1;
        trees[iquad] = tree;
    }
};

// this class takes care of the geometry of a tree node 
class Extent
{
  private:
    ofVec2f botLeft; // a vector containing the position of a box's lower left corner
    ofVec2f topRight; // a vector containing the position of a box's upper right corner
    ofVec2f vec; // a vector pointing from the lower left towards the upper right
    float w; // width of the box
    float h; // height of the box
    
  public:

    // initiate this empty, zero dimension
    Extent(){
        botLeft = ofVec2f(0.f,0.f);
        topRight = ofVec2f(0.f,0.f);
        vec = topRight - botLeft;
        w = vec.x;
        h = vec.y;
    }

    // initiate this from bottom-left and top-right vectors
    Extent(const ofVec2f &_botLeft,
           const ofVec2f &_topRight
           )
    {
        botLeft = _botLeft;
        topRight = _topRight;
        vec = topRight - botLeft;
        w = vec.x;
        h = vec.y;
    }
    
    // initiate this from bottom-left, width and height
    Extent(const ofVec2f &_botLeft,
           const float &_w,
           const float &_h
           )
    {
        botLeft = _botLeft;
        vec = ofVec2f(_w,_h);
        topRight = botLeft + vec;
        w = _w;
        h = _h;
    }

    // initiate this from bottom-left, width, and height, but the bottom-left coordinates are given explicitly
    Extent(const float &_x_bottom_left,
           const float &_y_bottom_left,
           const float &_w,
           const float &_h
           )
    {
        botLeft = ofVec2f(_x_bottom_left, _y_bottom_left);
        vec = ofVec2f(_w,_h);
        topRight = botLeft + vec;
        w = _w;
        h = _h;
    }

    // initiate from another box (copy attributes)
    Extent(const Extent &other){
        botLeft = other.botLeft;
        topRight = other.topRight;
        vec = other.vec;
        w = other.w;
        h = other.h;
    }
    
    // initiate from a list of 2d positions
    Extent(const vector <ofVec2f> &positions){
        
        if (positions.empty())
            return;
        
        // find the respective x and y min and max
        float minX, maxX, minY, maxY;
        bool noPointSet = true;
        for(auto const &pos: positions){
            if (noPointSet){
                minX = pos.x;
                maxX = pos.x;
                minY = pos.y;
                maxY = pos.y;
                noPointSet = false;
            } else {
                if (pos.x < minX)
                    minX = pos.x;
                if (pos.x > maxX)
                    maxX = pos.x;
                if (pos.y < minY)
                    minY = pos.y;
                if (pos.y > maxY)
                    maxY = pos.y;
            }
        }
        
        // set the extent attributes
        botLeft = ofVec2f(minX,minY);
        topRight = ofVec2f(maxX,maxY);
        vec = topRight - botLeft;
        w = vec.x;
        h = vec.y;
    }
    
    // return a new geometry referring to a box that corresponds to one of the quadrants,
    // accessed by integer id
    Extent get_quadrant(const int &q){
        if (q==_NW){
            return get_NW();
        } else if (q==_NE) {
            return get_NE();
        } else if (q==_SE) {
            return get_SE();
        } else if (q==_SW) {
            return get_SW();
        }
        return;
    }
    
    // return the north-western quadrant
    Extent get_NW(){
        ofVec2f base = botLeft + ofVec2f(0.f,vec.y/2);
        return Extent(base, base + vec/2);
    }
    
    // return the north-eastern quadrant
    Extent get_NE(){
        ofVec2f base = botLeft + vec/2;
        return Extent(base, base + vec/2);
    }
    
    // return the south-eastern quadrant
    Extent get_SE(){
        ofVec2f base = botLeft + ofVec2f(vec.x/2,0.f);
        return Extent(base, base + vec/2);
    }
    
    // return the south-western quadrant
    Extent get_SW(){
        return Extent(botLeft, botLeft + vec/2);
    }
    
    // return the minimum x-coordinate of this box
    float left(){
        return botLeft.x;
    }
    
    // return the minimum y-coordinate of this box
    float bottom(){
        return botLeft.y;
    }

    // return the maximum x-coordinate of this box
    float right(){
        return topRight.x;
    }
    
    // return the maximum y-coordinate of this box
    float top(){
        return topRight.y;
    }
    
    // check whether a point lies within a box
    bool contains(const ofVec2f &pos){
        return ( pos.x >= left() &&
                 pos.x <= right() &&
                 pos.y <= top() &&
                 pos.y >= bottom()
                );
    }
    
    // Returns the integer id of the quadrant, 
    // this position would lie in.
    // Returns -1 if the position does not
    // lie within the extent of this box
    int quad_to_insert_to(const ofVec2f &pos){
        if (contains(pos)){
            // left space
            if (pos.x < right()-w/2) {
                // bottom space
                if (pos.y < top()-h/2){
                    return _SW;
                } else {
                    return _NW;
                }
            } else{
                // bottom space
                if (pos.y < top()-h/2){
                    return _SE;
                } else {
                    return _NE;
                }
            }
        }
        else{
            return -1;
        }
    }

    // returns width of this box
    float width(){
        return w;
    }

    // returns height of this box
    float height(){
        return h;
    }
    
    // returns the vector that points from the lower left to the upper right of the box
    ofVec2f get_vec(){
        return vec;
    }
    
    // returns the vector that contains the coordinates of the box's lower left
    ofVec2f get_bottom_left(){
        return botLeft;
    }

    // returns the vector that contains the coordinates of the box's upper right
    ofVec2f get_top_right(){
        return topRight;
    }
    
    // returns the vector that contains the coordinates of the box's upper left
    ofVec2f get_top_left(){
        return ofVec2f(botLeft.x, topRight.y);
    }
};


// A tree root that contains positions and subtrees
class BarnesHutTree
{
    
  private:

    // insert data into this node
    void _update_data(ofVec2f &pos, float mass){

        // to compute center of mass and total mass
        total_mass_position += mass * pos;
        total_mass += mass;
        center_of_mass = total_mass_position/total_mass;

        // number of points that lie within this tree (box) increases by one
        number_of_contained_points++;
    }

  public:

    ofVec2f* this_pos; // a pointer to the vector of the mass point that this tree carries.
                       // (this pointer only contains data if it's a leaf node, otherwise it's NULL)
    int this_id;       // integer id of the data point in this node
    float this_mass;   // the mass of the data point in this node
    float total_mass;  // total mass of all data points that are contained in this node
                       // xor in all subtrees of this node
    ofVec2f total_mass_position; // total mass-position of all data points that are contained
                                 // in this node xor all subtrees of this node
    ofVec2f center_of_mass; // center of mass of all data points in this node
    size_t number_of_contained_points; // the total number of all data points that are contained
                                       // in this node xor in all its subtrees
    int current_data_quadrant; // the quadrant the current data lies in
    Extent geom;           // the geometry of the box of this node
    SubTrees subtrees;     // the subtrees of this node
    BarnesHutTree* parent; // the parent of this node (if root, parent is NULL)

    // create an empty root node
    BarnesHutTree(){
        this_pos = NULL;
        this_id = -1;
        this_mass = 0.f;
        total_mass = 0.f;
        total_mass_position = ofVec2f(0.f,0.f);
        center_of_mass = ofVec2f(0.f,0.f);
        number_of_contained_points = 0;
        parent = NULL;
        current_data_quadrant = -1;
    };
    
    // create a root node that corresponds to a box and might have
    // been created from a parent node
    BarnesHutTree(const Extent &_geom,
                  BarnesHutTree* _parent = NULL
                  )
    {
        this_pos = NULL;
        this_id = -1;
        parent = _parent;
        total_mass = 0.f;
        this_mass = 0.f;
        total_mass_position = ofVec2f(0.f,0.f);
        center_of_mass = ofVec2f(0.f,0.f);
        number_of_contained_points = 0;
        current_data_quadrant = -1;
        geom = Extent(_geom);
    };
    
    // recursively create a whole tree from a list of positions,
    // masses will be set to m = 1 for every data point
    BarnesHutTree(vector < ofVec2f > & positions){
        this_pos = NULL;
        this_id = -1;
        parent = NULL;
        total_mass = 0.f;
        this_mass = 0.f;
        total_mass_position = ofVec2f(0.f,0.f);
        center_of_mass = ofVec2f(0.f,0.f);
        number_of_contained_points = 0;
        current_data_quadrant = -1;
        geom = Extent(positions);
        
        int i = 0;
        for(auto &pos: positions){
            insert(pos,1.0,i);
            ++i;
        }
    }

    // recursively create a whole tree from a list of positions and masses
    BarnesHutTree(vector < ofVec2f > & positions,
                  vector < float > & masses
                  ){
        this_pos = NULL;
        this_id = -1;
        parent = NULL;
        total_mass = 0.f;
        this_mass = 0.f;
        total_mass_position = ofVec2f(0.f,0.f);
        center_of_mass = ofVec2f(0.f,0.f);
        number_of_contained_points = 0;
        current_data_quadrant = -1;
        geom = Extent(positions);
        
        // check that every point has a mass
        if (masses.size() != positions.size())
            throw length_error("masses and positions must be of equal length");
        
        auto mass = masses.begin();
        int i = 0;
        for(auto &pos: positions){
            insert(pos, *mass, i);
            ++mass;
            ++i;
        }
    }

    // insert a data point into the tree, including a mass and an
    // integer id of the data point (to reference the data point later)
    void insert(ofVec2f &new_pos, float mass = 1.0f, int id = -1){
        
        // find the quadrant of this box that the data point would be inserted to
        int candidate_quad = geom.quad_to_insert_to(new_pos);
        if (candidate_quad < 0) return; // if the candidate is -1, the point lies outside the box
        
        // if this tree node carries no data and no subtrees (i.e. is empty),
        // put the position and the mass inside this node and return
        if (this_pos == NULL && subtrees.occupied_trees == 0){
            this_pos = &new_pos;
            current_data_quadrant = candidate_quad;
            this_mass = mass;
            _update_data(new_pos, mass);
            this_id = id;
            return;
        }
        
        // if this tree node carries no data but has subtrees (i.e. is an internal node of the tree),
        // find the subtree/quadrant this position would lie in and insert it in there
        if (this_pos == NULL && subtrees.occupied_trees > 0){
            
            BarnesHutTree* tree_to_insert_to = subtrees.trees[candidate_quad];
            
            // if the candidate tree/quadrant is empty, create a new tree in this quadrant
            if (tree_to_insert_to == NULL){
                tree_to_insert_to = new BarnesHutTree(geom.get_quadrant(candidate_quad), this);
                subtrees.add_tree(candidate_quad, tree_to_insert_to);
            }

            // insert the data into either (a) this new leaf node or (b) the already existing tree
            tree_to_insert_to->insert(new_pos,mass,id);
            _update_data(new_pos, mass);

            return;
        }

        // if this tree node carries data and has no subtrees (i.e. is a leaf of the tree),
        // create a new tree in the quadrant of the old data, insert the old data into the subtree,
        // reset all data pointers of this former leaf node, then start the procedure
        // to insert the new data into this tree again
        if (this_pos != NULL && subtrees.occupied_trees == 0){
            
            // create subtree to which the new data will be inserted and insert new data
            BarnesHutTree* new_tree = new BarnesHutTree(geom.get_quadrant(current_data_quadrant), this);
            subtrees.add_tree(current_data_quadrant,new_tree);
            new_tree->insert(*this_pos,this_mass,this_id);

            // reset the data pointers of this former leaf node that just became an internal node
            this_mass = 0.f;
            this_pos = NULL;
            this_id = -1;
            current_data_quadrant = -1;
            
            // insert the new data into this tree, which is now an internal node 
            insert(new_pos, mass, id);
        }
    }
    
};


#endif /* BarnesHutTree_h */

