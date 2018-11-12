int
main (int argc, int argv)
{
    int x;
    x = 2 * argc;
    if (x == 8) {
        goto exit;
    } else {
        while (x < 50)
            x = x + 1;
        if (x == 50)
            x = 0;
    }
exit:
    return x;
}
