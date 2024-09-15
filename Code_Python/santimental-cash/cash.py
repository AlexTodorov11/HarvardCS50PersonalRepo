from cs50 import get_float


def main():
    # Continuously prompt the user for a valid positive amount of change
    while True:
        change_dollars = get_float("Change owed: ")
        if change_dollars >= 0:
            break

    # Convert dollars to cents
    change_cents = round(change_dollars * 100)

    # Initialize coin counter
    coins = 0

    # Define the coin values in cents
    quarters = 25
    dimes = 10
    nickels = 5
    pennies = 1

    # Calculate the minimum number of coins
    coins += change_cents // quarters
    change_cents %= quarters

    coins += change_cents // dimes
    change_cents %= dimes

    coins += change_cents // nickels
    change_cents %= nickels

    coins += change_cents // pennies
    change_cents %= pennies

    # Output the minimum number of coins
    print(coins)


if __name__ == "__main__":
    main()
