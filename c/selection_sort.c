#include<stdio.h>
int main(){
    int n; printf("Enter number of elements\n"); scanf("%d", &n);
    int arr[n]; printf("enter %d elements\n", n);
    for(int i=0; i<n; i++)scanf("%d", &arr[i]);
    printf("\nBefore sorting:\n");
    for(int i=0; i<n; i++)printf("%d ", arr[i]);
    for(int i=0; i<n-1; i++){
        int min=arr[i];
        for(int j=i+1; j<n; j++){
            if(arr[j]<arr[min])min=j;
        }
        int temp=arr[i];
        arr[i]=arr[min];
        arr[min]=temp;
    }
    printf("\nAfter Sorting:\n");
    for(int i=0; i<n; i++)printf("%d ", arr[i]);
    return 0;
}