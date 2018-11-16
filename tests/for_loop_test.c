int
main () {
    int num;
    int sum;
    int i;
    int j;
    num = 4;
    sum = 0;
    for (i = 0; i < num * num; i += 1)
        for (j = 0; j < num; j += 1)
            sum += 1;
    return sum;
}
