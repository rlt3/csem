int
main () {
    int num;
    int sum;
    int i;
    int j;
    num = 4;
    sum = 0;
    i = 0;
    do {
        j = 0;
        do {
            sum += 1;
            j += 1;
        } while (j < num);
        i += 1;
    } while (i < num*num);
    return sum;
}
