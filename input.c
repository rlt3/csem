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
    }
exit:
    return x;
}
