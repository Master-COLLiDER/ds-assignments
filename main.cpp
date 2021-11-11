#include <cstdio>


int numToBits(float num){
    int bits;
    bits = * (int *) (& num);
    printf("\nBit representation %f:", num);
    for (int i = 31; i >=0 ; i--) {
        if ((i+1)%4==0)
            printf(" ");
        printf("%d",(bits>>i) & 1);
    }
    printf("\nBit representation of %f in Hex: %x\n\n", num, bits);

    return bits;
}

int main() {
    float input;
    printf("Enter a Real Number: ");scanf("%f",&input);

    int bits = numToBits(input);
    printf("\nReturned Value:",input);

    printf("\nIn Decimal: %d", bits);
    printf("\nIn Hexadecimal: %x", bits);
    printf("\nIn Octal: %o", bits);


    return 0;
}
