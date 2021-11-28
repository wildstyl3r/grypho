#include "interfaces.hpp"
#include <vector>
#include <algorithm>


template <typename T> std::ostream& operator<< (std::ostream& os, const std::vector<T>& data)
{
    for(const T& elem:data){
	os << elem << ' ';
    }
    os << '\n';
    return os;
}


template <typename T> class Matrix : public Displayable
{
    std::vector< std::vector<T> > _m;
    /*long long _det;
    bool _detset;*/
public:
    Matrix (const size_t size = 0);

    void resize (const size_t size);
    std::ostream& write (std::ostream& os) const;
    Matrix<T> operator& (const T value);
    inline std::vector<T>& operator[] (const size_t i) { return _m[i]; };
    long long det();
};



template <typename T> Matrix<T>::Matrix(const size_t size) : _m(std::vector< std::vector<T> >(size, std::vector<T>(size))) {}


template <typename T> void Matrix<T>::resize(const size_t size)
{
    _m.resize(size);
    for(const auto& vv:_m){
	vv.resize(size);
    }
}


template <typename T> std::ostream& Matrix<T>::write (std::ostream& os) const
{
    os << _m;
    return os;
}


template <typename T> Matrix<T> Matrix<T>::operator& (const T value) 
{
    
    Matrix<T> result = this;
    for (auto& vec:result) {
	for_each(vec.begin(), vec.end(), [&value](T& elem){ elem = (elem == value); });
    }
}

template <typename T> long long Matrix<T>::det()
{
    if (_m.size() == 1) {
	return _m[0][0];
    }

    if (_m.size() == 2) {
	return _m[0][0]*_m[1][1] - _m[0][1]*_m[1][0];
    }

    Matrix<T> m(_m);
    long long det = 1, tot = 1;
    std::vector<long long> t(m.size());
    for (int i = 0; i < m.size(); ++i) {
	int x = i;
	while (m[x][i] == 0 && x < m.size()) {
	    x++;
	}
	if (x == m.size()) {
	    continue;
	}
	if (x != i) {
	    for (int j = 0; j < m.size(); ++j)
		std::swap(m[x][j], m[i][j]);
	    det = det * (x - i) % 2 ? -1 : 1;
	}

	for (int j = 0; j < m.size(); ++j)
	    t[j] = m[i][j];

	for (int j = i + 1; j < m.size(); ++j) {
	    long long d = t[i];
	    long long nr = m[j][i];

	    for (int k = 0; k < m.size(); ++k) {
		m[j][k] = d * m[j][k] - nr * t[k];
	    }
	    tot *= d;
	}
    }

    for (int i = 0; i < m.size(); ++i) {
	det *= m[i][i];
    }
    return det/tot;
}
