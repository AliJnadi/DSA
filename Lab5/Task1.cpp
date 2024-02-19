// Ali Jnadi
#include <iostream>

using namespace std;

int main()
{
    
    int c = 8; // Maximum capacity
    int n = 4; // numer of items
    
    int p[] = {0, 1, 2, 5, 6}; // Adding zero to match the algor.
    int w_t[] = {0, 2, 3, 4, 5}; // Adding zero to match the algor.
    
    int k[n + 1][c + 1];
    
    for(int i = 0; i < n + 1; i++)
        for(int w = 0; w < c + 1; w++)
        {
            if(i == 0 || w == 0)
                k[i][w] = 0;
            else if(w_t[i] <= w)
                k[i][w] = max(k[i - 1][w], p[i] + k[i - 1][w - w_t[i]]);
            else
                k[i][w] = k[i-1][w];    
        }
        
    for(int i = 0; i < n + 1; i++)
    {
        for(int w = 0; w < c + 1; w++)
        {
            cout << k[i][w] << " ";
        }
        cout << endl;
    }
    
    int i = n;
    int j = c;
    
    while(i > 0 && j > 0)
    {
        if (k[i][j] == k[i-1][j])
            cout << "Do not take item " << i << endl;
        else
        {
            cout << "Do take item " << i << endl;
            j = j - w_t[i];
        }
        i--;
    }
    
    while(i > 0)
        cout << "Do not take item " << i-- << endl;
    return 0;
}