#include<stdio.h>
int main(){
    int n; printf("Enter number of elements\n"); scanf("%d", &n);
    int arr[n]; printf("Enter %d elements\n", n);
    for(int i=0; i<n; i++)scanf("%d", &arr[i]);
    printf("\nBefore Sorting:\n");
    for(int i=0; i<n; i++)printf("%d ", arr[i]);
    for(int i=1; i<n; i++){
        int key=arr[i];
        int j=i-1;
        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
    printf("\nAfter Sorting:\n");
    for(int i=0; i<n; i++)printf("%d ", arr[i]);
    return 0;
}