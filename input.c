int
main (int x) {
    int y;
    y = x;
    if (!(x = x - 2) && x == 0)
        return y;
    return 0;
}
