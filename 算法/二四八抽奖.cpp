#include <algorithm>
#include <iostream>

using namespace std;

// bool cmp(const int *a, const int *b) {
//   if (a[3] != b[3])
//     return a[3] > b[3];
//   if (a[0] != b[0])
//     return a[0] > b[0];
//   return a[4] < b[4];
// }

// int main() {
//   int n;
//   cin >> n;
//   int arr[300][5];
//   for (int i = 0; i < n; i++) {
//     cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
//     arr[i][3] = arr[i][0] + arr[i][1] + arr[i][2];
//     arr[i][4] = i + 1;
//   }
//   sort(arr, arr + n, cmp);
//   for (int i = 0; i < 5; i++) {
//     cout << arr[i][4] << " " << arr[i][3] << endl;
//   }
//   return 0;
// }  sort的对必须是可交换可赋值的，二位数组不行，改为结构体

struct person {
  int a, b, c, sum, id;
};

bool cmp(const person x, person y) {
  if (x.sum != y.sum)
    return x.sum > y.sum;
  if (x.a != y.a)
    return x.a > y.a;
  return x.id < y.id;
}

int main() {
  int n;
  cin >> n;
  person arr[301];
  for (int i = 0; i < n; i++) {
    cin >> arr[i].a >> arr[i].b >> arr[i].c;
    arr[i].sum = arr[i].a + arr[i].b + arr[i].c;
    arr[i].id = i + 1;
  }
  sort(arr, arr + n, cmp);
  for (int i = 0; i < 5; i++) {
    cout << arr[i].id << " " << arr[i].sum << endl;
  }
  return 0;
}