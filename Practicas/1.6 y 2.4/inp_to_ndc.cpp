#include <bits/stdc++.h>
using namespace std;
typedef float num;
#define ndh 500
#define ndv 500

#define xmin -1
#define xmax 1
#define ymin -1
#define ymax 1
// #define xmin 0
// #define xmax 100
// #define ymin 0
// #define ymax 100
void ino_to_ndc(num dcx,num dcy,num &ndcx,num &ndcy) {
  ndcx=dcx/(ndh-1);
  ndcy=dcy/(ndv-1);
}
void ndc_to_user(num ndcx,num ndcy,num &x,num &y) {
  x=ndcx*(xmax-xmin)/(-xmin);
  y=ndcy*(ymax-ymin)/(-ymin);
}
void user_to_ndc(num x,num y,num &ndcx,num &ndcy) {
  ndcx=(x-xmin)/(xmax-xmin);
  ndcy=(y-ymin)/(ymax-ymin);
}
void ndc_to_dc(num ndcx,num ndcy,num &dcx,num &dcy) {
  dcx=trunc(ndcx*(ndh-1));
  dcy=trunc(ndcy*(ndv-1));
}

int main(int argc, char const *argv[]) {

  return 0;
}
