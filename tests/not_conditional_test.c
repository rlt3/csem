int
main (int x) {
    int y;
    y = x;
    if (!(x = x - 1) && x == x)
        return y;
    return 0;
}
