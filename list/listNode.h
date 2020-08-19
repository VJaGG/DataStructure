typedef int Rank;  //秩
#define ListNodePosi(T) ListNode<T>* //列表节点位置
#include <iostream>
using namespace std;

template <typename T> 
struct ListNode //列表节点模板类（以双向链表形式实现）
{
    //成员
    T data; ListNodePosi(T) pred; ListNodePosi(T) succ;//数值、前驱、后继
    //构造函数
    ListNode() {} //针对header和trailer的构造
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) :data(e), pred(p), succ(s){} //默认构造函数

    //操作接口
    ListNodePosi(T) insertAsPred(T const& e);
    ListNodePosi(T) insertAsSucc(T const& e);
};

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e){
    ListNodePosi(T) p = new ListNode<T>(e, pred, this); //创建新的节点。
    pred->succ = p;
    pred = p;

    // this->pred = p;
    //  p->pred->succ = p;
    return p;
}


template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e){
    ListNodePosi(T) p = new ListNode<T>(e, this, succ); //创建新节点
    succ->pred = p; //设置逆向的链接
    succ = p; 
    // this->succ = p;
    // p->succ->pred = p;
    return p;
}


