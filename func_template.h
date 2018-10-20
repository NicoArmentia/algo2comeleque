#ifndef	FUNC_TEMPLATE_H
#define FUNC_TEMPLATE_H

template <typename T>
inline T const& Max(T const& a, T const& b){
	return a > b ? a : b;
}

template <typename T>
inline T const& Min(T const& a, T const& b){
	return a < b ? a : b;
}

template <typename T>
inline void swap(T &a, T &b){
	T temp = a;
	a = b;
	b = temp;
}



#endif
