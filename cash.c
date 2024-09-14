#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int cents;

    // Prompt the user for change owed, in cents
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    int quarters = cents / 25; // Calculate how many quarters you should give customer
    cents %= 25;               // Subtract the value of those quarters from cents

    int dimes = cents / 10; // Calculate how many dimes you should give customer
    cents %= 10;            // Subtract the value of those dimes from remaining cents

    int nickels = cents / 5; // Calculate how many nickels you should give customer
    cents %= 5;              // Subtract the value of those nickels from remaining cents

    int pennies = cents; // Calculate how many pennies you should give customer

    int total_coins = quarters + dimes + nickels +
                      pennies;   // Sum the number of quarters, dimes, nickels, and pennies used
    printf("%d\n", total_coins); // Print that sum

    return 0;
}
