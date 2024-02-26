// Ali Jnadi
// Implementation of count sort

#include <iostream>

using namespace std;

int main()
{
    int n = 8; // Number of array elements
    int A[] = {2, 5, 3, 2, 3, 0, 0, 1};
    int k = 5; // Maximum number in the array
    
    int redu[k + 1];
    
    for(int i = 0; i < n; i++)
        redu[A[i]]++;
    
    int acc[k + 1];
    acc[0] = redu[0];
    
    for(int i = 1; i < k + 1; i++)
        acc[i] = acc[i-1] + redu[i];
    
    int B[n]; // Sorted array
    int i = n;
    while(i > 0)
    {
        i--;
        int temp = A[i];
        int idx = --acc[temp];
        B[idx] = temp;
    }
    
    for(int v : B)
        cout << v << " ";
    
    return 0;
}
