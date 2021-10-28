#include <iostream>
#include <cstring>
#include <cassert>

template <typename T>
class SuperArray{
  T* _start;
  size_t _capacity;

 public:

  template <typename... Ts>
  explicit SuperArray(size_t capacity, Ts... data){
	_start = (T*)calloc(capacity, sizeof(T));

	assert(_start != nullptr);
	_capacity = capacity;
	T values[] = { data... };
	if(sizeof(values)/sizeof(T) > capacity) {
	  throw std::runtime_error("Input data larger than capacity.");
	}
	memcpy(_start,  values, sizeof(values));
  }

  ~SuperArray(){
	delete _start;
  }

  T& operator[](size_t ix){
	if(ix >= _capacity){
	  throw std::runtime_error("Array out of bounds");
	}
	return *(_start + ix);
  }

  const T& operator[](size_t ix) const{
	if(ix >= _capacity){
	  throw std::runtime_error("Array out of bounds");
	}
	return *(_start + ix);
  }

  [[nodiscard]] size_t size() const{
	return _capacity;
  }

  // Iterators.
  T* begin() noexcept{
	return _start;
  }

  T* end() noexcept{
	return _start + _capacity;
  }

  const T* cbegin() noexcept{
	return const_cast<T*>(_start);
  }

  T* cend() noexcept{
	return const_cast<T*>(_start + _capacity);
  }

};

int main() {
  //SuperArray<double> arr{10};
  SuperArray<double> arr{10, 1.0, 2.0, 3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0 };
  //arr[2] = 100;
  //arr[4] = 100;
  /*for(double i : arr){
	std::cout << i << std::endl;
  }*/
  for(auto it = arr.cbegin(); it != arr.cend(); ++it){
	std::cout << *it << std::endl;
  }
  std::cout << "Hello, World!" << arr[1] << std::endl;
  return 0;
}
