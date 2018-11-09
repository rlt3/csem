int
main (int argc, int argv)
{
    int x;
    double y;
    y = argc;
    x = 2 * y;
    if (x == 8)
        x = 20;
    if (x == 20)
        x = 1;
    return x;
}

int
foo (int bar, double baz)
{
    return 58;
}
