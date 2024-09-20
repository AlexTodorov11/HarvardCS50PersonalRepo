int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0);

    for (int i = 0; i < height; i++)
    {
        // Print spaces for right alignment
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }

        // Print hashes for the pyramid
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        // **Removed the trailing space**

        // Print a new line
        printf("\n");
    }
}
