#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_ps.h"

#define MAX 1000
#define LIMIT 15   // change to 0 if full output needed

int main()
{
FILE *f1, *f2, *out;


ps_aux aux[MAX];
ps_elf elf;

char buffer[1024];
int i = 0, printed = 0;

// running commands and saving outputs
system("ps aux > x1.txt");
system("ps -eLf > x2.txt");

// opening files
f1 = fopen("x1.txt", "r");
f2 = fopen("x2.txt", "r");
out = fopen("merged.txt", "w");

if (!f1 || !f2 || !out)
{
    printf("error opening files\n");
    return 1;
}

// skipping header of aux file
fgets(buffer, sizeof(buffer), f1);

// reading aux data
while (i < MAX &&
       fscanf(f1,
              "%s %d %f %f %d %d %s %s %s %s %[^\n]",
              aux[i].user,
              &aux[i].pid,
              &aux[i].cpu,
              &aux[i].mem,
              &aux[i].vsz,
              &aux[i].rss,
              aux[i].tty,
              aux[i].stat,
              aux[i].start,
              aux[i].time,
              aux[i].command) != EOF)
{
    i++;
}

// writing header
fprintf(out,
    "UID\tPID\tPPID\tLWP\tC\tNLWP\t%%CPU\t%%MEM\tVSZ\tRSS\tTTY\tSTAT\tSTART\tTIME\tCOMMAND\n");

// skipping elf header
fgets(buffer, sizeof(buffer), f2);

// reading elf and merging
while (fscanf(f2,
              "%*s %*s %s %d %d %d %d %d %*s %*s %*s %*s %*s %*s %*s %*s %[^\n]",
              elf.uid,
              &elf.pid,
              &elf.ppid,
              &elf.lwp,
              &elf.c,
              &elf.nlwp,
              buffer) != EOF)
{
    for (int j = 0; j < i; j++)
    {
        if (aux[j].pid == elf.pid)
        {
            fprintf(out,
                    "%s\t%d\t%d\t%d\t%d\t%d\t%.1f\t%.1f\t%d\t%d\t%s\t%s\t%s\t%s\t%s\n",
                    elf.uid,
                    elf.pid,
                    elf.ppid,
                    elf.lwp,
                    elf.c,
                    elf.nlwp,
                    aux[j].cpu,
                    aux[j].mem,
                    aux[j].vsz,
                    aux[j].rss,
                    aux[j].tty,
                    aux[j].stat,
                    aux[j].start,
                    aux[j].time,
                    aux[j].command);

            printed++;
            break;
        }
    }

    if (LIMIT > 0 && printed >= LIMIT)
        break;
}

fclose(f1);
fclose(f2);
fclose(out);

// displaying result
printf("\nDisplaying first 15 merged processes:\n\n");
system("cat merged.txt");




}

