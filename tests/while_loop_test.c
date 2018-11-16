int
main () {
    int num;
    int sum;
    int i;
    int j;
    num = 4;
    sum = 0;
    i = 0;
    while (i < num*num) {
        j = 0;
        while (j < num) {
            sum += 1;
            j += 1;
        }
        i += 1;
    }
    return sum;
}

