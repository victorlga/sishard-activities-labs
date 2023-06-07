#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *nome_arquivo = argv[1];
    if (argc != 3) {
        return 1;
    }
    char *nome_arquivo_final = argv[2];

    int file = open(nome_arquivo, O_RDONLY);
    if (file == -1) {
        perror("open");
        return 1;
    }
    int final_file = open(nome_arquivo_final, O_WRONLY | O_CREAT, 0700);
    if (final_file == -1) {
        perror("open");
        return 1;
    }

    int status_read;
    int status_write;
    char buf[1];
    int estado = 1;

    while (1) {
        status_read = read(file, buf, 1);
        if (status_read == -1)
            perror("read");

        if (status_read == 0)
            break;

        switch (estado) {
            case 1:
                if (buf[0] == '/') {
                    estado = 2;
                } else {
                    status_write = write(final_file, buf, 1);
                    if (status_write == -1)
                        perror("write");
                }
                break;
            case 2:
                if (buf[0] == '/') {
                    estado = 3;
                } else if (buf[0] == '*') {
                    estado = 4;
                } else {
                    status_write = write(final_file, "/", 1);
                    if (status_write == -1)
                        perror("write");
                    status_write = write(final_file, buf, 1);
                    if (status_write == -1)
                        perror("write");
                    estado = 1;
                }
                break;
            case 3:
                if (buf[0] == '\n') {
                    status_write = write(final_file, buf, 1);
                    if (status_write == -1)
                        perror("write");
                    estado = 1;
                }
                break;
            case 4:
                if (buf[0] == '*') {
                    estado = 5;
                }
                break;
            case 5:
                if (buf[0] == '/') {
                    estado = 1;
                } else {
                    estado = 4;
                }
                break;
            default:
                break;
        }
    }
    close(file);
    close(final_file);

    return 0;
}
