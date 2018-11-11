int
main (int argc, int argv)
{
    int x;
    double y;
    y = argc;
    x = 2 * y;
    if (x == 8)
        goto exit;
    else
        while (x < 50)
            x = x + 1;
exit:
    return x;
}

int
foo (int bar, double baz)
{
    if (bar == 2)
        goto exit;
    bar = baz;
exit:
    return bar;
}
