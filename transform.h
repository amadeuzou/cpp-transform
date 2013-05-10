/*
 * =====================================================================================
 *
 *       filename:  transform.h
 *
 *    description:  STL container transform functions
 *
 *        version:  1.0
 *        created:  2013-04-08
 *       revision:  none
 *       compiler:  g++ -std=c++11
 *
 *         author:  amadeu zou
 *        company:  blog.youtueye.com
 *
 *      copyright:  2013 amadeuzou#gmail.com Inc. All Rights Reserved.
 *      
 * =====================================================================================
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>


/* function like object for container sort */
template<typename T1, typename T2>
struct less_second
{
	typedef std::pair<T1, T2> type;
	bool operator ()(type const &x, type const &y) const
	{
		/* sort descending , not ascending */
		return x.second > y.second;
	}
};

/*array to vector*/
template <typename T, size_t N>
static inline std::vector<T> array_to_vector(T const(& src)[N])
{
	return std::vector<T>(src, src + sizeof(src) / sizeof(T));
}

/*vector to array*/
template <typename T, size_t N>
static inline size_t vector_to_array(const std::vector<T> &src, T (dst)[N])
{
    size_t count = std::min(N, src.size());
    std::copy(src.begin(), src.begin()+count, dst);
    return count;
 }


/*array to vector pair*/
template <typename T, size_t N>
static inline std::vector< std::pair<T, T> > array_to_vector(T const(& src)[N][2]) 
{
	std::vector< std::pair<T, T> > result;
	result.reserve(N);
    std::transform(
        src, src+N, std::inserter(result, result.begin()),
        [] (T const(&p)[2]) { return std::make_pair(p[0], p[1]); }
        );

    return result;
}

/*array to vector*/
template <typename T1, typename T2, size_t N>
static inline std::vector< std::pair<T1, T2> > array_to_vector(T1 const(& first)[N], T2 const(& second)[N] ) 
{
	std::vector< std::pair<T1, T2> > result;
	result.reserve(N);
	std::transform(
				   first, first+N, second, std::inserter(result, result.begin()),
				   [] (T1 const &x, T2 const &y) { return std::make_pair(x, y); }
				   );
	
    return result;
}

/*array to vector*/
template <typename T1, typename T2, size_t N>
static inline std::vector< std::pair<T1, T2> > array_to_vector(const std::vector<T1> &first, const std::vector<T2> &second) 
{
	size_t count = std::min(N, std::min(first.size(), second.size()));
	std::vector< std::pair<T1, T2> > result;
	result.reserve(count);
	std::transform(
				   first, first+count, second, std::inserter(result, result.begin()),
				   [] (T1 const &x, T2 const &y) { return std::make_pair(x, y); }
				   );
	
    return result;
}


/*vector pair to array*/
template <typename T, size_t N>
static inline size_t vector_to_array(const std::vector< std::pair<T, T> > &src, T (dst)[N][2]) 
{
	size_t count = std::min(N, src.size());

    std::transform(
				   src.begin(), src.begin() + count, dst,
				   [] (const std::pair<T, T> &v) {T p[2]; p[0] = v.first; p[1] = v.second; return p; }
        );

    return count;
}



/*vector pair to array*/
template <typename T1, typename T2, size_t N>
static inline size_t vector_to_array(const std::vector< std::pair<T1, T2> > &src, T1 (first)[N], T2 (second)[N]) 
{
	size_t count = std::min(N, src.size());

    std::transform(
				   src.begin(), src.begin() + count, first,
				   [] (const std::pair<T1, T2> &v) { return v.first; }
        );

	std::transform(
				   src.begin(), src.begin() + count, second,
				   [] (const std::pair<T1, T2> &v) { return v.second; }
        );
	
    return count;
}

/*vector pair to array*/
template <typename T1, typename T2, size_t N>
static inline size_t vector_to_array(const std::vector< std::pair<T1, T2> > &src, std::vector<T1> &first, std::vector<T2> &second) 
{
	size_t count = std::min(N, src.size());
	first.resize(count);
	second.resize(count);
	
    std::transform(
				   src.begin(), src.begin() + count, std::inserter(first, first.begin()),
				   [] (const std::pair<T1, T2> &v) { return v.first; }
        );

	std::transform(
				   src.begin(), src.begin() + count, std::inserter(second, second.begin()),
				   [] (const std::pair<T1, T2> &v) { return v.second; }
        );
	
    return count;
}

/*array to map*/
template <typename T, size_t N>
static inline std::map<T, T> array_to_map(T const(& src)[N][2]) 
{
	std::map<T, T> result;

    std::transform(
        src, src+N, std::inserter(result, result.begin()),
        [] (T const(&p)[2]) { return std::make_pair(p[0], p[1]); }
        );

    return result;
}



/*array to map*/
template <typename T1, typename T2, size_t N>
static inline std::map<T1, T2> array_to_map(T1 const(& first)[N], T2 const(& second)[N] ) 
{
	std::map<T1, T2> result;
	std::transform(
				   first, first+N, second, std::inserter(result, result.begin()),
				   [] (T1 const &x, T2 const &y) { return std::make_pair(x, y); }
				   );
	
    return result;
}

/*array to map*/
template <typename T1, typename T2, size_t N>
static inline std::map<T1, T2> array_to_map(const std::vector<T1> &first, const std::vector<T2> &second) 
{
	size_t count = std::min(N, std::min(first.size(), second.size()));
	std::map<T1, T2> result;
	std::transform(
				   first, first+count, second, std::inserter(result, result.begin()),
				   [] (T1 const &x, T2 const &y) { return std::make_pair(x, y); }
				   );
	
    return result;
}

/*map to array*/
template <typename T, size_t N>
static inline size_t map_to_array(const std::map<T, T>src, T (dst)[N][2]) 
{
	size_t count = std::min(N, src.size());

    std::transform(
				   src.begin(), src.begin() + count, dst,
				   [] (const std::pair<T, T> &v) {T p[2]; p[0] = v.first; p[1] = v.second; return p; }
        );

    return count;
}

/*map to array*/
template <typename T1, typename T2, size_t N>
static inline size_t map_to_array(const std::map<T1, T2> &src, T1 (first)[N], T2 (second)[N]) 
{
	size_t count = std::min(N, src.size());

    std::transform(
				   src.begin(), src.begin() + count, first,
				   [] (const std::pair<T1, T2> &v) { return v.first; }
        );

	std::transform(
				   src.begin(), src.begin() + count, second,
				   [] (const std::pair<T1, T2> &v) { return v.second; }
        );
	
    return count;
}

/*map to array*/
template <typename T1, typename T2, size_t N>
static inline size_t map_to_array(const std::map<T1, T2> &src, std::vector<T1> &first, std::vector<T2> &second) 
{
	size_t count = std::min(N, src.size());
	first.resize(count);
	second.resize(count);
	
    std::transform(
				   src.begin(), src.begin() + count, std::inserter(first, first.begin()),
				   [] (const std::pair<T1, T2> &v) { return v.first; }
        );

	std::transform(
				   src.begin(), src.begin() + count, std::inserter(second, second.begin()),
				   [] (const std::pair<T1, T2> &v) { return v.second; }
        );
	
    return count;
}

/*map to array*/
template <typename T1, typename T2, size_t N>
static inline std::vector<std::pair<T1, T2> > map_to_vector(const std::map<T1, T2> &src) 
{
	size_t count = std::min(N, src.size());
	std::vector< std::pair<T1, T2> > dst;
	dst.reserve(count);
	
	std::transform(
				   src.begin(), src.begin() + count, std::inserter(dst, dst.begin()),
				   [] (const std::pair<T1, T2> &v) { return v; }
        );
	
    return count;
}

/*vector to map*/
template <typename T1, typename T2, size_t N>
static inline std::map<T1, T2>  vector_to_map(const std::vector<std::pair<T1, T2> > &src) 
{
	size_t count = std::min(N, src.size());
	std::map<T1, T2> dst;
	
	
	std::transform(
				   src.begin(), src.begin() + count, std::inserter(dst, dst.begin()),
				   [] (const std::pair<T1, T2> &v) { return v; }
        );
	
    return count;
}
#endif
