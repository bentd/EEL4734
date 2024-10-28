#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEVICE "/dev/testchar"
#define IOCTL_SET_LOWER 1
#define IOCTL_SET_UPPER 2
#define IOCTL_SET_CAPS 3

void set_format(int fd, int format)
{
    ioctl(fd, format);
}

int main()
{
    int fd = open(DEVICE, O_RDWR);
    if (fd < 0)
    {
        perror("Failed to open the device");
        return 1;
    }

    char input[256];
    char output[256];
    int format_choice;

    while (1)
    {
        printf("Enter a string (or 'exit' to quit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0)
            break;

        printf("Choose format - 1: Lower, 2: Upper, 3: Caps: ");
        scanf("%d", &format_choice);
        getchar(); // clear newline

        set_format(fd, format_choice == 1 ? IOCTL_SET_LOWER : format_choice == 2 ? IOCTL_SET_UPPER
                                                                                 : IOCTL_SET_CAPS);

        write(fd, input, strlen(input));
        read(fd, output, sizeof(output));

        printf("Processed string: %s\n", output);
    }

    close(fd);
    return 0;
}
