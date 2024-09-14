# Function to get a valid integer between 1 and 8 inclusive
def get_int():
    while True:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                return height
        except ValueError:
            pass
        print("Please enter a valid integer between 1 and 8.")


# Get the height of the pyramid
height = get_int()

# Generate the half-pyramids
for i in range(1, height + 1):
    # Left pyramid
    print(" " * (height - i), end="")  # Print spaces for alignment
    print("#" * i, end="")  # Print left hashes

    # Gap of two spaces
    print("  ", end="")

    # Right pyramid
    print("#" * i)
