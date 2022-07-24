// minimal clone of openFrameworks 2d vector,
// only containing the methods needed in BarnesHutTree.h

#ifndef minimal_clone_ofVec2f_h
#define minimal_clone_ofVec2f_h

#include <iostream>

using namespace std;

class ofVec2f {

    public:

        float x, y;

        ofVec2f(const float &_x,
                const float &_y
                )
        {
            x = _x;
            y = _y;
        }

        ofVec2f& operator+=( const ofVec2f& vec );
        ofVec2f  operator+( const ofVec2f& vec ) const;
        ofVec2f  operator-( const ofVec2f& vec ) const;

        ofVec2f  operator*( const float f ) const;
        ofVec2f  operator/( const float f ) const;

        friend ostream& operator<<(ostream& os, const ofVec2f& vec);
        friend istream& operator>>(istream& is, const ofVec2f& vec);
};


// define header for non-member operators
ofVec2f operator*( float f, const ofVec2f& vec );


// implementations

inline ofVec2f ofVec2f::operator+( const ofVec2f& vec ) const {
	return ofVec2f( x+vec.x, y+vec.y);
}

inline ofVec2f& ofVec2f::operator+=( const ofVec2f& vec ) {
	x += vec.x;
	y += vec.y;
	return *this;
}

inline ofVec2f ofVec2f::operator-( const ofVec2f& vec ) const {
	return ofVec2f(x-vec.x, y-vec.y);
}


inline ofVec2f ofVec2f::operator*( const float f ) const {
	return ofVec2f(x*f, y*f);
}

inline ofVec2f ofVec2f::operator/( const float f ) const {
	if(f == 0) return ofVec2f(x, y);

	return ofVec2f(x/f, y/f);
}

inline ofVec2f operator*( float f, const ofVec2f& vec ) {
    return ofVec2f( f*vec.x, f*vec.y);
}

inline ostream& operator<<(ostream& os, const ofVec2f& vec) {
	os << vec.x << ", " << vec.y;
	return os;
}

inline istream& operator>>(istream& is, ofVec2f& vec) {
	is >> vec.x;
	is.ignore(2);
	is >> vec.y;
	return is;
}

#endif /* minimal_clone_ofVec2f_h */
