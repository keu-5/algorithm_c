#include <stdio.h>

int main(void) {
    double height, weight, BMI;

    printf("身長と体重を入力して下さい。:");
    scanf("%lf %lf", &height, &weight);
    
    BMI = weight / (height * height);
    printf("BMI = %lf\n", BMI);
    
    return 0;
}