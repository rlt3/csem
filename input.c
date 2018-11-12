int
foo (int y)
{
    int x;
    x = 2 * y;
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

int
main (int argc, int argv)
{
    int x;
    int y;
    for (x = 0; x < 25; x = x + 1) {
        for (y = 0; y < 25; y = y + 1) {
            if (y == 15)
                break;
        }
        if (y > 0)
            break;
    }
    return x;
}
