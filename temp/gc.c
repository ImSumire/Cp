#include <stdio.h>


void startup() {
    printf("Init the Garbage Collector\n");
}
void __attribute__((constructor)) startup();

void quit() {
    printf("Garbage Collectorizinationing\n");
}
void __attribute__((destructor)) quit();


int main() {
    printf("Running Main\n");
}
