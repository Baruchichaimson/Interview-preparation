#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

/* ---- thread arguments ---- */
typedef struct
{
    char **array;
    size_t low;
    size_t high;
} thread_arg_t;

/* ---- compare strings ---- */
int cmp_str(const void *a, const void *b)
{
    const char *sa = *(const char **)a;
    const char *sb = *(const char **)b;
    return strcmp(sa, sb);
}

/* ---- thread worker ---- */
void *thread_sort(void *arg)
{
    thread_arg_t *targ = (thread_arg_t *)arg;
    size_t n = targ->high - targ->low + 1;
    qsort(targ->array + targ->low, n, sizeof(char *), cmp_str);
    return NULL;
}

/* ---- merge two sorted subarrays ---- */
static void merge(char **arr, size_t left, size_t mid, size_t right)
{
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    char **L = malloc(n1 * sizeof(char *));
    char **R = malloc(n2 * sizeof(char *));
    memcpy(L, arr + left, n1 * sizeof(char *));
    memcpy(R, arr + mid + 1, n2 * sizeof(char *));

    size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (strcmp(L[i], R[j]) <= 0)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

/* ---- merge K sorted chunks ---- */
static void merge_chunks(char **arr, size_t total, int num_chunks)
{
    size_t chunk = total / num_chunks;
    for (int step = 1; step < num_chunks; step *= 2)
    {
        for (int i = 0; i < num_chunks; i += 2 * step)
        {
            if (i + step < num_chunks)
            {
                size_t left = i * chunk;
                size_t mid  = (i + step) * chunk - 1;
                size_t right = (i + 2 * step == num_chunks) ? (total - 1)
                                                            : ((i + 2 * step) * chunk - 1);
                merge(arr, left, mid, right);
            }
        }
    }
}

/* ---- elapsed time ---- */
double elapsed(struct timespec start, struct timespec end)
{
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

/* ---- main ---- */
int main()
{
    srand(time(NULL));

    /* load dictionary */
    FILE *fp = fopen("/usr/share/dict/words", "r");
    if (!fp)
    {
        perror("dict open");
        return 1;
    }

    char **words = NULL;
    size_t count = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\n")] = '\0';
        words = realloc(words, (count + 1) * sizeof(char *));
        words[count] = strdup(line);
        count++;
    }
    fclose(fp);

    printf("Loaded %zu words\n", count);

    /* duplicate to get larger dataset (shallow copy OK) */
    int factor = 10;
    size_t total = count * factor;
    char **all_words = malloc(total * sizeof(char *));
    for (int i = 0; i < factor; i++)
    {
        memcpy(all_words + i * count, words, count * sizeof(char *));
    }

    /* shuffle */
    for (size_t i = total - 1; i > 0; --i)
    {
        size_t j = rand() % (i + 1);
        char *tmp = all_words[i];
        all_words[i] = all_words[j];
        all_words[j] = tmp;
    }

    /* threading */
    int num_threads = 4;
    pthread_t threads[num_threads];
    thread_arg_t args[num_threads];

    size_t chunk = total / num_threads;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < num_threads; i++)
    {
        args[i].array = all_words;
        args[i].low = i * chunk;
        args[i].high = (i == num_threads - 1) ? (total - 1) : ((i + 1) * chunk - 1);
        pthread_create(&threads[i], NULL, thread_sort, &args[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    /* merge sorted chunks */
    merge_chunks(all_words, total, num_threads);

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Sorted %zu words with %d threads (parallel sort+merge) in %.3f sec\n",
           total, num_threads, elapsed(start, end));

    printf("First 5 words:\n");
    for (int i = 0; i < 5; i++)
        printf("%s\n", all_words[i]);

    printf("Last 5 words:\n");
    for (size_t i = total - 5; i < total; i++)
        printf("%s\n", all_words[i]);

    /* cleanup */
    for (size_t i = 0; i < count; i++)
        free(words[i]);
    free(words);
    free(all_words);

    return 0;
}
