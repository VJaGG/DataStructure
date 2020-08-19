#include "listNode.h"
template <typename T>
class List
{
private:
    int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //规模、头哨兵、尾哨兵

protected:
    void init(); //列表创建初始化
    int clear(); //清除所有节点
    void copyNodes(ListNodePosi(T), int); //复制列表中自位置p起的n项
    void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int); //归并
    void mergeSort(ListNodePosi(T)&, int); //对从p开始连续的n个节点归并排序
    void selectionSort(ListNodePosi(T), int); //对从p开始连续的n个节点选择排序
    void insertionSort(ListNodePosi(T), int); //对从p开始连续的n个节点插入排序


public:
    //构造函数
    List(){init();} //默认构造函数
    List(List<T> const& L); //整体复制列表
    List(List<T> const& L, Rank r, int n); //复制列表L中自第r项起的n项
    List(ListNodePosi(T) p, int n); //复制列表中自位置p起的n项

    //析构函数
    ~List(); //释放(包括头，尾哨兵在内的)所有的节点

    //只读的访问接口
    Rank size() const{
        return _size;
    }
    bool empty() const{
        return _size <= 0;
    }
    T& operator[](Rank r) const; //重载，支持循秩访问(效率低)。

    //首节点的位置
    ListNodePosi(T) first() const{
        return header->succ;
    }

    //末节点的位置
    ListNodePosi(T) last() const{
        return trailer->pred;
    }

    //判断p是否对外合法
    bool valid(ListNodePosi(T) p){
        return p && (trailer!=p) && (header!=p);
    } 

    int disordered() const; // 判断列表是否已经排序
    ListNodePosi(T) find(T const& e) const{ //无序列表查找
        return find(e, _size, trailer);
    }
    ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const; //无序区间查找

    ListNodePosi(T) search(T const& e) const{ //有序列表查找
        return search(e, _size, trailer);
    }
    ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const; //有序区间查找

    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n); //在p及其n-1个后继中选出最大者
    ListNodePosi(T) selectMax(){ //整体的最大的元素
        return selectMax(header->succ, _size);
    }

    //可以写的访问接口
    ListNodePosi(T) insertAsFirst(T const& e); //将e当作首节点插入
    ListNodePosi(T) insertAsLast(T const& e); //将e当作末节点插入
    ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e); //将e作为p的后继插入
    ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e); //将e作为p的前驱插入

    T remove(ListNodePosi(T) p); //删除合法位置p处的节点，并且返回被删除节点
    void merge(List<T>& L){merge(first(), size, L, L.first(), L._size);} //全列表归并
    void sort(ListNodePosi(T) p, int n); //列表区间排序
    void sort() {sort(first(), _size);} //列表整体的排序
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
    void reverse(); //前后倒置
    //遍历

    void traverse(void(*) (T&)); //遍历，依次实施visit操作(函数指针，只读或者局部性修改)
    template <typename VST> //操作器
    void traverse(VST& ); //遍历，依次实施visit操作(函数对象，全局性修改)
}; //List


template <typename T>
void List<T>::init(){
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0;
}


template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n){
    init();
    // ListNodePosi(T) cur = header;
    // while (0 < n--){
    //     cur->insertAsSucc(p->data);
    //     p = p->succ;
    //     cur = cur->succ;       
    // }
    while (n--){
        insertAsLast(p->data);
        p = p->succ;
    }
}

template <typename T>
List<T>::List(List<T> const& L){
    copyNodes(L.first(), L._size);
    printf("------copy--------\n");
    // copyNodes(L.header->succ, L.size());
    // _size = L.size(); 在insertAsLast中插入的时候已经对_size进行修改。
}

template <typename T>
List<T>::List(List<T> const& L, Rank r, int n){
    ListNodePosi(T) p = L.first();
    while (r--)
        p = p->succ;
    copyNodes(p, n);
}

template <typename T>
List<T>::List(ListNodePosi(T) p, int n){
    copyNodes(p, n);
    // _size = n;
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e){
    // ListNodePosi(T) p = header->insertAsSucc(e);
    // _size++;
    // return p;
    _size++;
    return header->insertAsSucc(e); //e当作首节点插入
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e){
    // ListNodePosi(T) p = trailer->insertAsPred(e);
    // _size++;
    // return p;
    _size++;
    return trailer->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e){
    // ListNodePosi(T) temp = p->insertAsSucc(e);
    // _size++;
    // return temp;
    _size++;
    return p->insertAsSucc(e); //e当做p的后继插入(after)
}

template <typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e){
    // ListNodePosi(T) temp = p->insertAsPred(e);
    // _size++;
    // return temp;
    _size++;
    return p->insertAsPred(e); //e当做p的前驱插入(before)
}

template <typename T>
T& List<T>::operator[](Rank r) const{
    ListNodePosi(T) p = first();
    while (r--)
        p = p->succ;
    return p->data;
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p){ //删除节点p并且返回其中的值
    T e = p->data;
    p->succ->pred = p->pred;
    p->pred->succ = p->succ;
    delete p; _size--;
    return e;
}

template <typename T>
int List<T>::clear(){
    int oldSize = _size;
    while (0 < _size){
        remove(header->succ); //反复删除首节点，直到列表为空
    }
    return oldSize;
}

template <typename T>
void List<T>::traverse(void(*visit)(T&)){
    for (ListNodePosi(T) p = header->succ; p!=trailer; p=p->succ)
        visit(p->data);
    printf("\n");
}

template <typename T> template <typename VST> 
void List<T>::traverse(VST& visit){
    for (ListNodePosi(T) p = header->succ; p!=trailer; p=p->succ)
        visit(p->data);
}

template <typename T> //在无序列表
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const{
    while (n--){
        if(e == (p = p->pred)->data)
            return p;
    }
    return NULL;
}

template <typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const{ //不包含p
    while (0<=n--){
        if((p = p->pred)->data <= e)
            break;
    }
    return p;
}

template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n){
    ListNodePosi(T) max = p;
    while (1 < n--)
    {
        if((p=p->succ)->data > max->data)  //直接用后继节点进行比较
            max = p;
    }
    return max;
}

template <typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n){ //起始于p的n个元素排序
    for (int r = 0; r < n; r++){
        insertA(search(p->data, r, p), p->data); // 查找适当的位置并且插入
        p = p->succ;remove(p->pred);
    }
}

template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n){
    // ListNodePosi(T) cur = trailer; 
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) tail = p;
    for (int i = 0; i < n; i++)
        tail = tail->succ;     //寻找待排序的最后一个节点
    
    // for(int i = n; i>1; i--){
    //    ListNodePosi(T) pmax = selectMax(p, i);
    //    if (p == pmax)
    //        p = p->succ;
    //    cur = insertB(cur, pmax->data);
    //    remove(pmax);
    // }
    while(1 < n){
        ListNodePosi(T) max = selectMax(head->succ, n);
        insertB(tail, remove(max));
        tail = tail->pred; n--;
    }

}

template <typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q,  int m){
    ListNodePosi(T) pp = p->pred;
    while (0 < m){
        if((0 < n) && (p->data <= q->data)){
            if (q == (p = p->succ))
                break;
            n--;
        }
        else
        {
            insertB(p, L.remove((q = q->succ)->pred));
            m--;
        }
    }
    p = pp->succ;
}

template <typename T>
void List<T>:: mergeSort(ListNodePosi(T)& p, int n){
    if(n < 2)
        return;
    int m = n>>1;
    ListNodePosi(T) q = p;
    for (int i = 0; i < m; i++)
        q = q->succ;
    mergeSort(p, m);
    mergeSort(q, n-m);
    merge(p, m, *this, q, n-m);
}

template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n){
    // insertionSort(p, n);
    // selectionSort(p, n);
    mergeSort(p, n);
}

template <typename T>
List<T>::~List(){
    clear();
    delete header; delete trailer;
    printf("clear......\n");
}
