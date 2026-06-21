#include<iostream>
using namespace std;

void quick_sort(int a[],int left,int right){
    if(left < right){
        int i = left, j = right,key = a[left];
        while(i < j && a[j] >= key) left++;
        
    }
}