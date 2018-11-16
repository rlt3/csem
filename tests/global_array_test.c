int g[6];

int
main () {
    int sum;
    int i;
    sum = 0;
    for (i = 0; i < 6; i += 1)
        g[i] = i;
    for (i = 0; i < 6; i += 1)
        sum += g[i];
    return sum;
}
