#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  size_t nrows;
  size_t ncols;
  double *entries;
} matrix;

matrix *m_create(size_t nrows, size_t ncols) {
  matrix *m = (matrix *)malloc(sizeof(matrix));
  if (m == NULL) {
    perror("m_create");
    exit(1);
  }
  m->nrows = nrows;
  m->ncols = ncols;
  m->entries = (double *)calloc(nrows * ncols, sizeof(double));
  if (m->entries == NULL) {
    perror("m_create");
    exit(1);
  }
  return m;
}

void m_clean(matrix *m) {
  free(m->entries);
  free(m);
}

void m_init(matrix *m) {
  for (int i = 0; i < m->nrows * m->ncols; i++)
    m->entries[i] = (double)i + 1;
}

void print(matrix *m) {
  for (int i = 0; i < m->nrows * m->ncols; i++) {
    printf("%7.2f", m->entries[i]);
    if (i % m->ncols == m->ncols - 1)
      putchar('\n');
  }
}

void diag(matrix *t, matrix *s) {
  if ((t->nrows != s->nrows) || (t->ncols != s->ncols)) {
    fprintf(stderr, "diag: Matrices of different sizes\n");
    exit(1);
  }
  int j;
  for (int i = 0; i < s->nrows; i++) {
    for (j = 0; j < s->ncols; j++) {
      if (i == j)
        (t->entries)[i * s->ncols + j] = (s->entries)[i * s->ncols + j];
      else
        (t->entries)[i * s->ncols + j] = 0;
    }
  }
}

void ldiag(matrix *t, matrix *s) {
  if ((t->nrows != s->nrows) || (t->ncols != s->ncols)) {
    fprintf(stderr, "ldiag: Matrices of different sizes\n");
    exit(1);
  }
  int j;
  for (int i = 0; i < s->nrows; i++) {
    for (j = 0; j < s->ncols; j++) {
      if (i > j)
        (t->entries)[i * s->ncols + j] = (s->entries)[i * s->ncols + j];
      else
        (t->entries)[i * s->ncols + j] = 0;
    }
  }
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf("Usage: %s <nrows> <ncols>\n", argv[0]);
    return 1;
  }

  int nrows = atoi(argv[1]);
  int ncols = atoi(argv[2]);

  matrix *m = m_create(nrows, ncols);
  m_init(m);

  matrix *md = m_create(nrows, ncols);
  diag(md, m);

  matrix *mld = m_create(nrows, ncols);
  ldiag(mld, m);

  printf("\nm:\n");
  print(m);
  printf("\ndiag(m):\n");
  print(md);
  printf("\nldiag(m):\n");
  print(mld);
  printf("\n");

  m_clean(m);
  m_clean(md);
  m_clean(mld);
  m = md = mld = NULL;

  return 0;
}
