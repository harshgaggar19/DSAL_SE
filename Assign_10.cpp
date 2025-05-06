#include<iostream> 
#include <vector> 
using namespace std; 
 
class heap{ 
   public: 
   void heapify(vector<int> &h , int i , int n){ 
       int small = i; 
       int l = 2 * i + 1; 
       int r = 2 * i + 2; 
       if(l<n && h[l] < h[small]){ 
           small = l; 
       } 
       if(r<n && h[r] < h[small]){ 
           small = r; 
       } 
       if(small != i){ 
           swap(h[small] , h[i]); 
           heapify( h, small , n); 
       } 
   } 
 
   void heapSort(vector<int> &h){ 
       int n = h.size(); 
       for(int i=n/2-1; i>=0; i--){ 
           heapify(h , i , n); 
       } 
 
       vector<int> sort; 
       int pass = 1; 
       while(!h.empty()) { 
           sort.push_back(h[0]); 
           h[0] = h.back(); 
           h.pop_back(); 
           
           if(!h.empty()) { 
               heapify(h, 0, h.size()); 
           } 
           cout << "Pass " << pass << ": "; 
           for(int i = 0; i < h.size(); i++) { 
               cout << h[i] << " "; 
           } 
           cout << endl; 
 
           pass++;  
       } 
 
       h = sort; 
   } 
}; 
 
int main(){ 
   heap h; 
   
   vector<int> arr; 
   int n, value; 
   cout << "Enter the number of elements: "; 
   cin >> n; 
   
   cout << "Enter " << n << " elements:\n"; 
   for(int i = 0; i < n; i++) { 
       cin >> value; 
       arr.push_back(value); 
   } 
 
   cout << "\nOriginal array: "; 
   for(int i = 0; i < arr.size(); i++) { 
       cout << arr[i] << " "; 
   } 
   cout << endl; 
 
   for(int i = arr.size()/2 - 1; i >= 0; i--) { 
       h.heapify(arr, i, arr.size()); 
   } 
 
   cout << "Min-Heap after heapify operation: "; 
   for(int i = 0; i < arr.size(); i++) { 
       cout << arr[i] << " "; 
   } 
   cout << endl; 
cout << "After sorting: " << endl; 
h.heapSort(arr); 
cout << "Final sorted array: "; 
for(int i = 0; i < arr.size(); i++) { 
cout << arr[i] << " "; 
} 
cout << endl; 
return 0; 
} 
