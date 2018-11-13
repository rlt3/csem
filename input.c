int
main (int argc, int argv)
{
    int x;
    int y;
    y = 0;
    for (x = 0; x < 25; x = x + 1) {
        for (y = y + 1; y < 25; y = y + 1) {
            if (y == 15)
                break;
        }
        if (y >= 25) {
            break;
        }
    }
    return x;
}
