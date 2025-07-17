
#include <stdio.h>
#include <math.h>

void displayMenu() {
    printf("Scientific Calculator\n");
    printf("1. Basic Operations\n");
    printf("2. Trigonometric Operations\n");
    printf("3. Exponential Operations\n");
    printf("4. Logarithmic Operations\n");
    printf("5. Root Operations\n");
    printf("6. Exit\n");
}

void basicOperations() {
    int choice;
    double num1, num2;
    printf("Basic Operations\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);
    printf("Enter first number: ");
    scanf("%lf", &num1);
    printf("Enter second number: ");
    scanf("%lf", &num2);
    
    switch (choice) {
        case 1:
            printf("%.2lf + %.2lf = %.2lf\n", num1, num2, num1 + num2);
            break;
        case 2:
            printf("%.2lf - %.2lf = %.2lf\n", num1, num2, num1 - num2);
            break;
        case 3:
            printf("%.2lf * %.2lf = %.2lf\n", num1, num2, num1 * num2);
            break;
        case 4:
            if (num2 != 0)
                printf("%.2lf / %.2lf = %.2lf\n", num1, num2, num1 / num2);
            else
                printf("Error! Division by zero is not allowed.\n");
            break;
        default:
            printf("Invalid choice\n");
    }
}

void trigonometricOperations() {
    int choice;
    double num;
    printf("Trigonometric Operations\n");
    printf("1. Sine\n");
    printf("2. Cosine\n");
    printf("3. Tangent\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);
    printf("Enter a number (in radians): ");
    scanf("%lf", &num);
    
    switch (choice) {
        case 1:
            printf("sin(%.2lf) = %.2lf\n", num, sin(num));
            break;
        case 2:
            printf("cos(%.2lf) = %.2lf\n", num, cos(num));
            break;
        case 3:
            if (num != M_PI / 2)
                printf("tan(%.2lf) = %.2lf\n", num, tan(num));
            else
                printf("Error! Tangent is not defined at %.2lf radians.\n", num);
            break;
        default:
            printf("Invalid choice\n");
    }
}

void exponentialOperations() {
    int choice;
    double num, base;
    printf("Exponential Operations\n");
    printf("1. Power (x^y)\n");
    printf("2. Exponential (e^x)\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            printf("Enter base: ");
            scanf("%lf", &base);
            printf("Enter exponent: ");
            scanf("%lf", &num);
            printf("%.2lf ^ %.2lf = %.2lf\n", base, num, pow(base, num));
            break;
        case 2:
            printf("Enter a number: ");
            scanf("%lf", &num);
            printf("e ^ %.2lf = %.2lf\n", num, exp(num));
            break;
        default:
            printf("Invalid choice\n");
    }
}

void logarithmicOperations() {
    int choice;
    double num, base;
    printf("Logarithmic Operations\n");
    printf("1. Natural Logarithm (ln)\n");
    printf("2. Logarithm (log)\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            printf("Enter a number: ");
            scanf("%lf", &num);
            if (num > 0)
                printf("ln(%.2lf) = %.2lf\n", num, log(num));
            else
                printf("Error! Natural logarithm is not defined for non-positive numbers.\n");
            break;
        case 2:
            printf("Enter base: ");
            scanf("%lf", &base);
            printf("Enter a number: ");
            scanf("%lf", &num);
            if (base > 0 && base != 1 && num > 0)
                printf("log%.2lf(%.2lf) = %.2lf\n", base, num, log(num) / log(base));
            else
                printf("Error! Logarithm is not defined for the given base and/or number.\n");
            break;
        default:
            printf("Invalid choice\n");
    }
}

void rootOperations() {
    int choice;
    double num;
    printf("Root Operations\n");
    printf("1. Square Root\n");
    printf("2. Cube Root\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &choice);
    printf("Enter a number: ");
    scanf("%lf", &num);
    
    switch (choice) {
        case 1:
            if (num >= 0)
                printf("sqrt(%.2lf) = %.2lf\n", num, sqrt(num));
            else
                printf("Error! Square root is not defined for negative numbers.\n");
            break;
        case 2:
            printf("cbrt(%.2lf) = %.2lf\n", num, cbrt(num));
            break;
        default:
            printf("Invalid choice\n");
    }
}

int main() {
    int choice;
    do {
        displayMenu();
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                basicOperations();
                break;
            case 2:
                trigonometricOperations();
                break;
            case 3:
                exponentialOperations();
                break;
            case 4:
                logarithmicOperations();
                break;
            case 5:
                rootOperations();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please choose a valid option.\n");
        }
        
        printf("\n");
    } while (choice != 6);
    
    return 0;
}
