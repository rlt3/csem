int
foobar (int x)
{
    int ret;
    if (x < 15) {
        if (x == 1)
            ret = 5;
        else
            ret = 0;
    } else {
        ret = 10;
    }
    return ret;
}

int
main (int argc)
{
    return foobar(argc);
}
