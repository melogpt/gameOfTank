#include <stdio.h>
#include <stdlib.h>

// Soldiers struct
struct Soldier {
    int health;
    int strength;
};

// Stack struct
struct Stack {
    struct Soldier data[100]; 
    int top;
};

// Pushing soldiers
void push(struct Stack* stack, struct Soldier soldier) {
    if (stack->top < 100) {
        stack->data[stack->top++] = soldier;
    } else {
        printf("Stack full failed to add new soldiers\n");
    }
}


struct Soldier pop(struct Stack* stack) {
    if (stack->top > 0) {
        return stack->data[--stack->top];
    } else {
        struct Soldier emptySoldier = {0, 0};
        return emptySoldier;
    }
}

// Fight function
void fight(struct Stack* side1, struct Stack* side2, int* damageSide1, int* damageSide2) {
    struct Soldier soldier1 = pop(side1);
    struct Soldier soldier2 = pop(side2);
    
    int damage = (soldier1.strength - soldier2.strength) * 0.05 + 50;
    
    soldier2.health -= damage;
    
    if (soldier2.health <= 0) {
        printf("One soldier is dead.\n");
    } else {
        push(side2, soldier2);
    }


    if (side1->top > 0) {
        *damageSide1 += damage;
    }
    if (side2->top > 0) {
        *damageSide2 += damage;
    }
}



int main() {
    struct Stack side1 = {0};
    struct Stack side2 = {0};
    int damageSide1 = 0;
    int damageSide2 = 0;
    char command;
    
    while (1) {
        printf("Enter a Command (A: Add Soldiers, F: Fight, Q: Quit): ");
        scanf(" %c", &command);
        
        if (command == 'A' || command == 'a') {
            int side, health, strength;
            printf("Choose a Side (1 veya 2): ");
            scanf("%d", &side);
            printf("Enter Health and Strength Values (exp: 100,50): ");
            scanf("%d,%d", &health, &strength);
            struct Soldier newSoldier = {health, strength};
            if (side == 1) {
                push(&side1, newSoldier);
            } else if (side == 2) {
                push(&side2, newSoldier);
            }
        } else if (command == 'F' || command == 'f') {
            fight(&side1, &side2, &damageSide1, &damageSide2);
            printf("Side 1 Total Damage: %d\n", damageSide1);
            printf("Side 2 Total Damage: %d\n", damageSide2);
        } else if (command == 'Q' || command == 'q') {
            printf("Game is Over.\n");
            
            // Determine the winner and print the damage
            if (damageSide1 > damageSide2) {
                printf("Side 1 has Won! Total Damage: %d\n", damageSide1);
            } else if (damageSide2 > damageSide1) {
                printf("Side 2 has Won! Total Damage: %d\n", damageSide2);
            } else {
                printf("Tie Up! Total Damages are equal: %d\n", damageSide1);
            }
            
            break;
        } else {
            printf("Invalid Command. Try Again.\n");
        }
    }
    
    return 0;
}