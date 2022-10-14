int modExp(int a, int b, int c){
    if(a==0) return 0;
    if(b==0) return 1;
    long ans;
    if(b%2==0){
        long smallAns=modExp(a,b/2,c);
        ans=(smallAns*smallAns)%c;
    }
    else{
        // Using property (a*b)%c = ((a%c)*(b%c))%c
        long smallAns=modExp(a,b-1,c);
        ans=a%c;
        ans=(ans*smallAns)%c;
    }
    return int((ans+c)%c);
}
