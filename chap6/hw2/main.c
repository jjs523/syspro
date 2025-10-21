#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*);

typedef struct {
    char name[NAME_MAX + 1]; 
    char path[PATH_MAX];
    struct stat st;
} Entry;

int cmp_time_desc(const void *a, const void *b) {
    const Entry *ea = (const Entry*)a;
    const Entry *eb = (const Entry*)b;
    if (ea->st.st_mtime == eb->st.st_mtime) return 0;
    return (eb->st.st_mtime > ea->st.st_mtime) - (eb->st.st_mtime < ea->st.st_mtime);
}
int cmp_time_asc(const void *a, const void *b) { return -cmp_time_desc(a,b); }
int cmp_name_asc(const void *a, const void *b) {
    const Entry *ea = (const Entry*)a, *eb = (const Entry*)b;
    return strcmp(ea->name, eb->name);
}
int cmp_name_desc(const void *a, const void *b) { return -cmp_name_asc(a,b); }

int main(int argc, char **argv)
{ 
    int opt_a = 0; 
    int opt_l = 0;
    int opt_t = 0;
    int opt_r = 0;
    int opt_i = 0;
    char *dir = ".";

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strchr(argv[i], 'a')) opt_a = 1;
            if (strchr(argv[i], 'l')) opt_l = 1;
            if (strchr(argv[i], 't')) opt_t = 1;
            if (strchr(argv[i], 'r')) opt_r = 1;
            if (strchr(argv[i], 'i')) opt_i = 1;
        } else {
            dir = argv[i];
        }
    }

    DIR *dp;
    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        return 1;
    }
 
    Entry *list = NULL;
    size_t cap = 0, n = 0;
    struct dirent *d;
    while ((d = readdir(dp)) != NULL) {
        if (!opt_a && d->d_name[0] == '.') continue; // 숨김 제외

        if (n == cap) {
            cap = cap ? cap * 2 : 256;
            Entry *tmp = realloc(list, cap * sizeof(Entry));
            if (!tmp) { perror("realloc"); closedir(dp); free(list); return 1; }
            list = tmp;
        }
        snprintf(list[n].path, sizeof(list[n].path), "%s/%s", dir, d->d_name);
        strncpy(list[n].name, d->d_name, sizeof(list[n].name)-1);
        list[n].name[sizeof(list[n].name)-1] = '\0';

        if (lstat(list[n].path, &list[n].st) < 0) {
            perror(list[n].path);
 
        } else {
            n++;
        }
    }
    closedir(dp);
 
    if (opt_t) {
        qsort(list, n, sizeof(Entry), opt_r ? cmp_time_asc : cmp_time_desc);
    } else {
        qsort(list, n, sizeof(Entry), opt_r ? cmp_name_desc : cmp_name_asc);
    }
 
    for (size_t i = 0; i < n; i++) {
        if (opt_l) {
            if (opt_i) printf("%9lu ", (unsigned long)list[i].st.st_ino);
            printStat(list[i].path, list[i].name, &list[i].st);
        } else {
            if (opt_i) printf("%9lu ", (unsigned long)list[i].st.st_ino);
            printf("%s\n", list[i].name);
        }
    }

    free(list);
    return 0;
}

void printStat(char *pathname, char *file, struct stat *st)
{
 
    printf("%5ld ", (long)st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", (long)st->st_nlink);
    printf("%s %s ",
           getpwuid(st->st_uid)->pw_name,
           getgrgid(st->st_gid)->gr_name);
    printf("%9lld ", (long long)st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);
    printf("%s\n", file);
}

char type(mode_t mode)
{
    if (S_ISREG(mode)) return('-');
    if (S_ISDIR(mode)) return('d');
    if (S_ISCHR(mode)) return('c');
    if (S_ISBLK(mode)) return('b');
    if (S_ISLNK(mode)) return('l');
    if (S_ISFIFO(mode)) return('p');
    if (S_ISSOCK(mode)) return('s');
    return('?');
}

char *perm(mode_t mode)
{
    static char perms[10];
    strcpy(perms, "---------");
    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> (i * 3))) perms[i * 3]     = 'r';
        if (mode & (S_IWUSR >> (i * 3))) perms[i * 3 + 1] = 'w';
        if (mode & (S_IXUSR >> (i * 3))) perms[i * 3 + 2] = 'x';
    }
    return perms;
}

