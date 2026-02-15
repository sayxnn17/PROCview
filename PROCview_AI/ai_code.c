#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 1000
#define OUTPUT_LIMIT 15

/* Structure for ps aux data */
typedef struct {
char user[50];
int pid;
float cpu;
float mem;
int vsz;
int rss;
char tty[20];
char stat[10];
char start[20];
char time[20];
char command[200];
} ps_aux_struct;

/* Structure for ps -eLf data */
typedef struct {
char uid[20];
int pid;
int ppid;
int lwp;
int c;
int nlwp;
} ps_elf_struct;

/* Function to execute system commands */
void generate_snapshots()
{
system("ps aux > x1.txt");
system("ps -eLf > x2.txt");
}

/* Function to load ps aux data */
int load_aux_data(FILE *fp, ps_aux_struct data[])
{
char buffer[1024];
int count = 0;


fgets(buffer, sizeof(buffer), fp); // skip header

while (count < MAX_PROCESSES &&
       fscanf(fp,
              "%s %d %f %f %d %d %s %s %s %s %[^\n]",
              data[count].user,
              &data[count].pid,
              &data[count].cpu,
              &data[count].mem,
              &data[count].vsz,
              &data[count].rss,
              data[count].tty,
              data[count].stat,
              data[count].start,
              data[count].time,
              data[count].command) != EOF)
{
    count++;
}

return count;


}

/* Function to merge elf + aux data */
void merge_data(FILE *f_elf, FILE *f_out,
ps_aux_struct aux_data[], int total_aux)
{
char buffer[1024];
ps_elf_struct elf_row;
int printed = 0;


fgets(buffer, sizeof(buffer), f_elf); // skip header

fprintf(f_out,
    "UID\tPID\tPPID\tLWP\tC\tNLWP\t%%CPU\t%%MEM\tVSZ\tRSS\tTTY\tSTAT\tSTART\tTIME\tCOMMAND\n");

while (fscanf(f_elf,
              "%*s %*s %s %d %d %d %d %d %*s %*s %*s %*s %*s %*s %*s %*s %[^\n]",
              elf_row.uid,
              &elf_row.pid,
              &elf_row.ppid,
              &elf_row.lwp,
              &elf_row.c,
              &elf_row.nlwp,
              buffer) != EOF)
{
    for (int i = 0; i < total_aux; i++)
    {
        if (aux_data[i].pid == elf_row.pid)
        {
            fprintf(f_out,
                    "%s\t%d\t%d\t%d\t%d\t%d\t%.1f\t%.1f\t%d\t%d\t%s\t%s\t%s\t%s\t%s\n",
                    elf_row.uid,
                    elf_row.pid,
                    elf_row.ppid,
                    elf_row.lwp,
                    elf_row.c,
                    elf_row.nlwp,
                    aux_data[i].cpu,
                    aux_data[i].mem,
                    aux_data[i].vsz,
                    aux_data[i].rss,
                    aux_data[i].tty,
                    aux_data[i].stat,
                    aux_data[i].start,
                    aux_data[i].time,
                    aux_data[i].command);

            printed++;
            break;
        }
    }

    if (OUTPUT_LIMIT > 0 && printed >= OUTPUT_LIMIT)
        break;
}


}

int main()
{
FILE *f_aux, *f_elf, *f_out;

```
ps_aux_struct aux_data[MAX_PROCESSES];

/* Step 1 : Generate command outputs */
generate_snapshots();

/* Step 2 : Open files */
f_aux = fopen("x1.txt", "r");
f_elf = fopen("x2.txt", "r");
f_out = fopen("merged.txt", "w");

if (!f_aux || !f_elf || !f_out)
{
    perror("File error");
    return 1;
}

/* Step 3 : Load aux data */
int total_aux = load_aux_data(f_aux, aux_data);

/* Step 4 : Merge datasets */
merge_data(f_elf, f_out, aux_data, total_aux);

fclose(f_aux);
fclose(f_elf);
fclose(f_out);

printf("\nAI Generated my_ps Output:\n\n");
system("cat merged.txt");

return 0;

}
