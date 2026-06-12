#include <stdio.h>
int main()
{
    int n; printf("Enter n\n"); scanf("%d", &n);
    int arr[n];
    printf("Enter n elements\n");
    for(int i=0; i<n; i++)scanf("%d", &arr[i]);
    int key; printf("Enter element to be searched\n"); scanf("%d", &key);
    for(int i=0; i<n; i++){
        if(key==arr[i]){
            printf("Found at %d", i+1);
            return 0;
        }
    }
    printf("Not found\n");
    return 0;
}