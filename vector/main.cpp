#include "vector.h"
#include <iostream>
using namespace std;

int main(){
    Vector<int> arr0(4);
    Vector<int> arr1(3, 3, 2);
    cout<<"Vector(int c =  DEFAULT_CAPACITY, int s = 0, T value = 0)"<<endl;
    for (int i = 0; i < arr1.size(); i++)
    {
        cout<<arr1[i]<<" ";
    }
    cout<<endl;
    cout<<"Vector(T const* A, Rank n)"<<endl;
    int arr2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Vector<int> arr3(arr2, 10);
    for (int i = 0; i < arr3.size(); i++)
        cout<<arr3[i]<<" ";
    cout<<endl;
    
    cout<<"Vector(Vector<T> const& vec)"<<endl;
    Vector<int> arr4(arr3);
    for (int i = 0; i < arr4.size(); i++)
        cout<<arr4[i]<<" ";
    cout<<endl;


    cout<<"Vector(Vector<T> const& vec, Rank lo, Rank hi)"<<endl;

    Vector<int> arr5(arr3, 3, 9);
    for (int i = 0; i < arr5.size(); i++)
        cout<<arr5[i]<<" ";
    cout<<endl;


    cout<<"size()"<<endl;
    cout<<"arr0.size = "<<arr0.size()<<endl;
    cout<<"arr1.size = "<<arr1.size()<<endl;

    cout<<"empty()"<<endl;
    cout<<"arr0.empty = "<<arr0.empty()<<endl;
    cout<<"arr1.empty = "<<arr1.empty()<<endl;

    int arr6[6] = {0, 1, 7, 4, 1, 6};
    Vector<int> arr7(arr6, 6);
    cout<<"disordered()"<<endl;
    cout<<"arr7.disordered() = "<<arr7.disordered()<<endl;
    cout<<"arr3.disordered() = "<<arr3.disordered()<<endl;

    cout<<"find(T const& e)"<<endl;
    cout<<"arr7.find(1) = "<<arr7.find(1)<<endl;
    cout<<"arr7.find(0) = "<<arr7.find(0)<<endl;
    cout<<"arr7.find(2) = "<<arr7.find(2)<<endl;
    
    cout<<"find(T const& e, int lo, int hi)"<<endl;
    cout<<"arr7.find(1, 0, 2) = "<<arr7.find(1, 0, 2)<<endl;
    cout<<"arr7.find(0, 1, 3) = "<<arr7.find(0, 1, 3)<<endl;
    cout<<"arr7.find(4, 4, 6) = "<<arr7.find(4, 4, 6)<<endl;
    cout<<"arr7.find(2, 4, 6) = "<<arr7.find(2, 4, 6)<<endl;

    cout<<"search(T const& e)"<<endl;

    int arr8[6] = {2, 4, 5, 7, 9, 10};
    Vector<int> arr9(arr8, 6);
    cout<<"arr9.search(0) = "<<arr9.search(0)<<endl;
    cout<<"arr9.search(2) = "<<arr9.search(2)<<endl;
    cout<<"arr9.search(8) = "<<arr9.search(8)<<endl;

    cout<<"arr9.search(9) = "<<arr9.search(9)<<endl;


    cout<<"Vector<T>& Vector<T>::operator=(Vector<T> const& vec)"<<endl;
    cout<<"before: ";
    for(int i = 0; i < arr9.size(); i++)
        cout<<arr9[i]<<" ";
    cout<<endl;
    arr9 = arr7;
    cout<<"after: ";
    for (int i = 0; i < arr9.size(); i++)
        cout<<arr9[i]<<" ";
    cout<<endl;


    cout<<"T remove(Rank r)"<<endl;
    cout<<"before: ";
    for(int i = 0; i < arr9.size(); i++)
        cout<<arr9[i]<<" ";
    cout<<endl;
    cout<<"remove(3) = "<< arr9.remove(3)<<endl;
    cout<<"after: ";
    for(int i = 0; i < arr9.size(); i++)
        cout<<arr9[i]<<" ";

    cout<<"int Vector<T>::remove(Rank lo, Rank hi)"<<endl;
    int arr10[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Vector<int> arr11(arr10, 10);
    for (int i = 0; i < arr11.size(); i++)
        cout<<arr11[i]<<endl;
    
    cout<<"capacity = "<<arr11.capacity()<<endl;
    cout<<"size = "<<arr11.size()<<endl;

    cout<<"remove(0) = "<<arr11.remove(0)<<endl;
    cout<<"capacity = "<<arr11.capacity()<<endl;
    cout<<"size = "<<arr11.size()<<endl;

    
    cout<<"arr11.remove(0, 5) "<<arr11.remove(0, 5)<<endl;
    cout<<"capacity = "<<arr11.capacity()<<endl;
    cout<<"size = "<<arr11.size()<<endl;

    int arr12[3] = {1, 2, 3};
    Vector<int> arr13(arr12, 3);
    cout<<"arr13 capacity = "<<arr13.capacity()<<endl;
    cout<<"arr13 size = "<<arr13.size()<<endl;
    arr13.insert(4);
    arr13.insert(5);
    arr13.insert(6);
    cout<<"arr13 capacity = "<<arr13.capacity()<<endl;
    cout<<"arr13 size = "<<arr13.size()<<endl;
    arr13.insert(7);  //插入元素7的时候，容量增加
    cout<<"arr13 capacity = "<<arr13.capacity()<<endl;
    cout<<"arr13 size = "<<arr13.size()<<endl;



    
    
    

}