#include "print.hpp"
#include <algorithm>
#include <utility>
#include <tuple>


template <typename T>
void insert_sort(T &s, int nel)
{
    int i, j;

    for (i = 1; i < nel; i++) {
        j = i - 1;
        auto key = s[i];

        for(; j >= 0 && s[j] > key; j--) {
            s[j+1] = s[j];
        }

        s[j+1] = key;
    }
}


template <typename T>
int find_min(T s[], int start, int last, T value)
{
    int mid;

    while(start < last) {
        mid = (last - start) / 2 + start;
        printf("mid is %d\n" , mid);
        if (value > s[mid]) {
            start = mid + 1;
        } else if (value < s[mid]) {
            last = mid;
        } else {
            return mid;
        }
    }

    return start;
}


template <typename T>
void optimize_insert_sort(T s[], int nel)
{
    int i, j, index;

    for (i = 1; i < nel; i++) {
        j = i - 1;
        auto key = s[i];

        index = find_min(s, 0, i, key);
        printf("index is %d\n", index);
        for(; j >= index; j--) {
            s[j+1] = s[j];
        }

        s[index] = key;
    }
}


template <typename T>
void merge(T s[], int p, int q, int r)
{
    int i, j, k, k1;
    int len = r - p + 1;
    T d[len];

    for (i = p, j = q + 1, k = 0; k < len; k++) {

        if (i > q) {
            for (k1 = j; k1 <= r; k1++, k++) {
                d[k] = s[k1];
            }
            break;
        }

        if (j > r) {
            for (k1 = i; k1 <= q; k1++, k++) {
                d[k] = s[k1];
            }
            break;
        }

        if (s[i] <= s[j]) {
            d[k]= s[i];
            i++;
        } else {
            d[k]= s[j];
            j++;
        }
    }

    for (i = 0; i < len; i++) {
        s[p + i] = d[i];
    }
}


template <typename T>
void merge_sort(T s[], int p, int r)
{
    int q;

    if (p < r) {
        q = (p+r) / 2;
        merge_sort(s, p, q);
        merge_sort(s, q+1, r);
        merge(s, p, q, r);
    }
}

template <typename T>
int find(T s[], int start, int last, const T& value)
{
    int mid;

    while(start < last) {
        mid = (start + last) / 2;
        if (value > s[mid]) {
            start = mid + 1;
        } else if (value < s[mid]) {
            last = mid - 1;
        } else {
            return mid;
        }
    }

    return -1;
}


template <typename T>
std::tuple<T, T> sub_find(T s[], int nelt, T result)
{
    int i, sub, index;

    for(i = 0; i < nelt; i++) {
        sub = result - s[i];
        index = find(s,i, nelt, sub);
        if (index == -1) {
            continue;
        }

        return std::make_tuple(s[i], s[index]);
    }
}


template <typename T>
void inversion(T s[], int p, int q, int r)
{
    int i, j, k, k1;
    int len = r - p + 1;
    T d[len];

    for (i = p, j = q + 1, k = 0; k < len; k++) {

        if (i > q) {
            for (k1 = j; k1 <= r; k1++, k++) {
                d[k] = s[k1];
            }
            break;
        }

        if (j > r) {
            for (k1 = i; k1 <= q; k1++, k++) {
                d[k] = s[k1];
                printf("s[%d]\n", s[k1]);
                for (j = q + 1; j <= r; j++) {
                    printf("s3[%d]\n", s[j]);
                }
            }
            break;
        }

        if (s[i] <= s[j]) {
            d[k]= s[i];
            i++;
        } else {
            d[k]= s[j];
            printf("[%d, %d]\n", s[i], s[j]);
            j++;
        }
    }

    for (i = 0; i < len; i++) {
        s[p + i] = d[i];
    }
}


template <typename T>
void find_inversion(T s[], int p, int r)
{
    int q;

    if (p < r) {
        q = (p+r) / 2;
        find_inversion(s, p, q);
        find_inversion(s, q+1, r);
        inversion(s, p, q, r);
    }
}


int main()
{
    int s[8] = {1, 5, 6, 8, 2, 3, 111, 14};
    double d[7] = {1.0, 5.0, 6.0, 8.0, 111.2, 102.1, 14.1};

    insert_sort(s, 8);

    print_elements(s);

    int s2[10] = {1, 3, 5, 7, 9, 4, 6, 8, 10};
    merge(s2, 0, 4, 8);
    print_elements(s2);

    int s3[9] = {1, 88, 5, 6, 8, 2, 3, 111, 14};
    merge_sort(s3, 0, 8);
    print_elements(s3);
    merge_sort(d, 0, 6);
    print_elements(d);
    int index = find(s3, 0, 9, 88);
    std::cout << index;
    std::cout << std::endl;

    int s4[9] = {1, 88, 5, 6, 8, 2, 3, 111, 14};
    optimize_insert_sort(s4, 9);
    print_elements(s4);

    auto r = sub_find(s4, 9, 11);
    std::cout<<std::get<0>(r) << ' ';
    std::cout<<std::get<1>(r);
    std::cout << std::endl;

    int s5[6] = {2, 3, 8, 6 ,1, 0};
    // merge_sort(s5, 0, 5);
    // print_elements(s5);
    find_inversion(s5, 0, 5);
}
