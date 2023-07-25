std::vector<int> a, b;
swap(a, b);

template <typename T> 
void swap(T& a, T& b){
  T tmp(a);
  a = b;
  b = tmp; 
}
template <typename T> 
void swap(T& a, T& b){ 
  T tmp(std::move(a));
  a = std::move(b);
  b = std::move(tmp);
}
