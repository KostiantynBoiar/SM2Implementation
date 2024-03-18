#include "Math.h"

int Math::modulo(int m, int n)
{
    return m >= 0 ? m % n : (n - abs(m % n)) % n;
}

int Math::inverse(int x, int n)
{
    int t; // a temp value
    for (int i = 0; i < n; i++) {
        t = modulo(x * i, n);
        if (t == 1) {
            return i;
        };
    }
}
