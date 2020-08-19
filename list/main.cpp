#include "list.h"
#include <iostream>
using namespace std;

template <typename T>
void visit(T data){
    printf("%d ", data);
}


int main(){
    ListNode<int> head(0);
    List<int> list;
    cout<<list.size()<<endl;
    list.insertAsFirst(2);
    list.insertAsFirst(1);
    cout<<list.size()<<endl;
    list.insertAsLast(3);
    list.insertAsLast(4);
    cout<<list.size()<<endl;
    List<int> list1(list);
    cout<<list1.size()<<endl;
    list.traverse(visit);
    list1.traverse(visit);
    ListNodePosi(int) first = list.first();
    List<int> list2(first, 3);
    printf("-------list2-------\n");
    list2.traverse(visit);
    printf("%d", list2.size());
    ListNodePosi(int) second = first->succ;
    list.insertA(second, 10);
    list.insertB(second, 9);
    list.insertAsFirst(0);
    list.insertAsLast(2);
    printf("-------list-------\n");
    list.traverse(visit);
    printf("%d\n", list.size());
    List<int> list3(list, 3, 4);
    printf("-------list3-------\n");
    list3.traverse(visit);
    printf("%d\n", list3[1]);
    first = list3.first();
    list3.remove(first);
    list3.traverse(visit);
    printf("%d\n", list3[1]);
    printf("%d\n", list3.size());
    list.traverse(visit);
    List<int> list4 = list;
    printf("-------list4---------\n");
    list4.traverse(visit);
    ListNodePosi(int) last = list4.last();
    ListNodePosi(int) p = list4.find(2);
    cout<<p->data<<endl;
    
    ListNodePosi(int) p1 = list4.find(5);
    cout<<(p1==NULL)<<endl;
    ListNodePosi(int) max = list4.selectMax();
    printf("%d\n", max->data);
    list4.sort();
    list4.traverse(visit);
    
    
    return 0;
}


