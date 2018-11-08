int
main (int argc, int argv)
{
    int y[10];
    int x;
    x = 2 * argc;
    x = x / 2;
    x = x + 4;
    x = x - 4;
    x = x % 3;
    return x;
}

int
foo (int bar, double baz)
{
    return 58;
}
