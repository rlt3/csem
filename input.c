main (int x) {
    int i;
    double m[6];
    if (x < 0)
        return 0;
    if (x > 5)
        return 0;
    for (i = 0; i < 6; i += 1)
        m[i] = x;
    return m[x];
}
