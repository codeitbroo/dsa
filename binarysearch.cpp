int bianrysearch(vector<int> &arr, int val){
  int s=0, e=arr.size()-1;
  while(s<=e){
    int mid=(s+e)/2;
    if(arr[mid]==val) return mid;
    else if(arr[mid] > val) e=mid-1;
    else s=mid+1;
  }
  return -1;
}
