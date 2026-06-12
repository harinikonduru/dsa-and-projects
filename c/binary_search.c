#include<stdio.h>
int main(){
    int n; printf("Enter number of elements\n"); scanf("%d", &n);
    int arr[n]; printf("Enter %d elements\n", n);
    for(int i=0; i<n; i++)scanf("%d", &arr[i]);
    int left=0, right=n-1; int key; printf("enter element to be searched\n"); scanf("%d", &key);
    while(left<=right){
        int mid=(left+right)/2;
        if(arr[mid]==key){
            printf("Found at position %d\n", mid+1);
            return 0;
        }
        else if(arr[mid]>key)right--;
        else left++;
    }
    printf("Not found\n");
    return 0;
}