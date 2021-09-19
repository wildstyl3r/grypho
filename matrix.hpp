#include "interfaces.hpp"

#include <vector>


template <typename T> ostream& operator<< (ostream& os, const vector<T>& data)
{
    for(const T& elem:data){
	os << elem << ' ';
    }
    os << '\n';
    return os;
}


template <typename T> class Matrix : public Displayable
{
    vector< vector<T> > _m;
    /*long long _det;
    bool _detset;*/
public:
    Matrix (const size_t size = 0);

    void resize (const size_t size);
    ostream& operator<< (ostream& os) const;
    Matrix operator& (const T value);
    inline vector<T>& operator[] (const size_t i) { return _m[i] };
};
