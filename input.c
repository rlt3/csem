int g[5];

int
foo (int x, int y)
{
    g[x] = y;
    return x;
}

int
main (int x) {
    if (x > 4)
        return 0;
    foo(x, x - 4);
    printf("%d", -g[x]);
    return 0;
}
