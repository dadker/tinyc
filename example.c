int main(void) {
    int x = 7;
    int running = 1;
    while (running) {
        x = x + 1;
        if (x == 10) {
            running = 0;
        }
    }
    return x;
}