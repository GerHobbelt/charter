#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


#include "parser.h"
#include "renderer.h"

static off_t fsize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1;
}

#if defined(MONOLITHIC)
int charter_tex_main(int argc, const char* argv[])
#else
int main(int argc, const char* argv[])
#endif
{
    if (argc < 2)
    {
        fprintf(stderr, "usage: charter file\n");
        return -1;
    }
    FILE *fp;
    fp = fopen(argv[1], "r");
    long size = fsize(argv[1]);
    char * fcontent = malloc(size);
    fread(fcontent, 1, size, fp);
    fclose(fp);

    chart * c = parse_chart(fcontent);
    char * tex =chart_to_latex(c);
    printf("%s\n", tex);
    chart_free(c);
    free(tex);
    free(fcontent);

    return 0;
}
