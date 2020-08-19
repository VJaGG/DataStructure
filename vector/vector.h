#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T> 
class Vector
{
protected:  
    int _size; int _capacity; T *_elem;
    void copyFrom(T const* A, Rank lo, Rank hi);
    void expand();  //空间不足的时候扩容
    void shrink();
    bool bubble(Rank lo, Rank hi); //扫描交换
    void bubbleSort(Rank lo, Rank hi); //气泡排序
    Rank max(Rank lo, Rank hi);
    void selectionSort(Rank lo, Rank hi); //选择排序算法
    void merge(Rank lo, Rank mi, Rank hi); //归并算法
    void mergeSort(Rank lo, Rank hi); //归并排序算法
    Rank partition(Rank lo, Rank hi);
    void quickSort(Rank lo, Rank hi); //快速排序
    void heapSort(Rank lo, Rank hi);
public:
    Vector(int c =  DEFAULT_CAPACITY, int s = 0, T value = 0){
        _elem = new T[_capacity=c];
        for (_size = 0; _size < s; _size++)
            _elem[_size] = value;
    }
    Vector(T const* A, Rank n){ //数组整体赋值
        copyFrom(A, 0, n);
    }
    Vector(T const* A, Rank lo, Rank hi){ //区间整体赋值
        copyFrom(A, lo, hi);
    }
    Vector(Vector<T> const& vec){ //向量整体赋值
        copyFrom(vec._elem, 0, vec._size);
    }
    Vector(Vector<T> const& vec, Rank lo, Rank hi){ //向量部分赋值
        copyFrom(vec._elem, lo, hi);
    }

    //析构函数
    ~Vector(){delete _elem;};


    //只读访问接口
    int size() const{
        return _size;
    } 
    int capacity() const{
        return _capacity;
    }
    bool empty() const{
        return !_size;
    }
    int disordered() const; //返回逆序对的总数

    Rank find(T const& e) const{  //无序全部查找
        return find(e, 0, _size);
    }  
    Rank find(T const& e, int lo, int hi) const; // 无序区间查找

    Rank search(T const& e) const {// 有序向量整体查找
        return (0 >= _size) ? -1 : search(e, 0, _size);//判断是否有元素存在，如果不存在返回-1   
    }
    Rank search(T const& e, Rank lo, Rank hi) const;
    


    //可写访问接口
    T& operator[](Rank r) const;
    Vector<T>& operator=(Vector<T> const &); //赋值用算符的重载

    T remove(Rank r); //删除秩为r的元素
    int remove(Rank lo, Rank hi); //删除[lo, hi)之间的元素

    Rank insert(Rank r, T const& e); // 插入元素
    Rank insert(T const& e){
        return insert(_size, e);//默认在末尾插入
    }

    void sort(Rank lo, Rank hi); // 对[lo, hi)排序
    void sort(){   //整体排序
        sort(0, _size);
    }

    void unsort(Rank lo, Rank hi); //对[lo, hi)置乱
    void unsort(){
        unsort(0, _size); //对整体置乱
    }

    int deduplicate();//无序去重
    int uniquify();//有序去重

    //遍历
    void traverse(void(*) (T &));//遍历(使用函数指针， 只读或者局部性修改)
    template<typename VST> void traverse(VST&); //遍历使用函数对象



};

template <typename T>
void Vector<T>::shrink(){
    if(_capacity < DEFAULT_CAPACITY << 1)
        return;
    if(_size<< 2 > _capacity) //以25%为界
        return;
    T* oldElem = _elem;
    _elem = new T[_capacity>>=1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}


template<typename T>
void Vector<T>::copyFrom (T const* A, Rank lo, Rank hi){
    _elem = new T[_capacity = 2 * ( hi - lo ) ]; //预分配两倍的空间
    _size = 0;
    while (lo < hi)
        _elem[_size++] = A[lo++];
}

template<typename T>
void Vector<T>:: expand(){
    if (_size < _capacity) //尚未满的时候不要扩容
        return;
    if(_capacity < DEFAULT_CAPACITY) //不低于最小的容量
        _capacity = DEFAULT_CAPACITY;
    T *oldElem = _elem;
    _elem = new T[_capacity<<=1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
    
}

template<typename T>
int Vector<T>:: disordered() const{
    int count = 0;
    for (int i = 1; i < _size; i++){
        if(_elem[i-1] > _elem[i])
            count++;
    }   /* code */
    return count;
}

template<typename T>
// 返回最后一个元素e的位置,失败的时候返回lo-1
Rank Vector<T>::find(T const& e, int lo, int hi) const{
    while ((lo<hi--) && e!=_elem[hi]);
    return hi;
}

template<typename T>
static Rank binSearchA(T* A ,T const& e, Rank lo, Rank hi){
    while (lo < hi)
    {
        Rank mi = (lo + hi) >> 1; //选择中轴的点
        if(A[mi] < e)       
            lo = mi + 1;
        else if(e < A[mi])
            hi = mi;
        else
            return mi;    
    }
    return -1;
}

template<typename T>
static Rank binSearchB(T* A, T const& e, Rank lo, Rank hi){
    while (1 < hi - lo) //每步迭代仅做一次比较判断，有两个分支，成功查找不能提前终止。
    {
        Rank mi = (lo + hi) >> 1; //以中心为轴点
        (e < A[mi]) ? hi = mi : lo = mi; //经比较后深入[lo, mi)，[mi, hi)两个区间
        //如果e < A[mi]成立则在[lo, mi)中查找，不成立则 A[mi]<=e所以在区间[mi, hi)
    }
    return (e == A[lo]) ? lo : -1; //出口时候hi = lo + 1,查找区间仅有一个元素A[lo]
}  

template<typename T>
static Rank binSearchC(T* A, T const& e, Rank lo, Rank hi){
      while (lo < hi)
      {
          Rank mi = (lo + hi) >> 1;
          (e < A[mi]) ? hi = mi : lo = mi+1;  
          //如果e < A[mi]则，A[mi]右边的元素都大于e所以e < [hi, n)向左边扩展
          //当e < A[mi]不成立时候，则A[mi] <= e，所以左边界向右扩展则[0, lo) <= e       
      }
      return --lo;
      //有多个元素命中的时候，总能保证返回最后一个，查找失败的时候，返回失败的位置便于后续的插入。
      
}


template<typename T>
Rank Vector<T>::search(T const& e, int lo, int hi) const{
    srand((unsigned)time(0));  
    int choose = rand()%3;
    if(choose == 0)
        return binSearchA(_elem, e, lo, hi);
    else if(choose == 1)
        return binSearchB(_elem, e, lo, hi);
    else
        return binSearchC(_elem, e, lo, hi);

}

template<typename T>
T& Vector<T>::operator[](Rank r) const{
    return _elem[r];
}

template<typename T>
//赋值中，向量已经存在，只是对其进行修改，用其它的值代替。
Vector<T>& Vector<T>::operator=(Vector<T> const& vec){
    if(_elem)
        delete[] _elem; //释放原有的内容
    copyFrom(vec._elem, 0 , vec.size());
    return *this;
}

template<typename T>
T Vector<T> :: remove(Rank r){
    T e = _elem[r];
    remove(r, r+1);
    return e;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi){
    if (lo == hi)
        return 0; //出于效率的考虑，单独处理退化的情况。
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

template<typename T>
Rank Vector<T> ::insert(Rank r, T const& e){//将e作为秩为r的元素插入
    expand();
    for (int i = _size; i > r; i--)
        _elem[i] = _elem[i-1];
    _elem[r] = e;
    _size++;
    return r;//返回秩
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi){
       
}
