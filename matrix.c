#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int nrows;
  unsigned int ncols;
  double *entries;
} matrix;

matrix *m_create(unsigned int nrows, unsigned int ncols) {
  matrix *m = (matrix *)malloc(sizeof(matrix));
  if (m == NULL) {
    perror(__FUNCTION__);
    exit(1);
  }
  m->entries = (double *)calloc(nrows * ncols, sizeof(double));
  if (m->entries == NULL) {
    perror(__FUNCTION__);
    exit(1);
  }
  m->nrows = nrows;
  m->ncols = ncols;
  return m;
}

void m_destroy(matrix *m) {
  free(m->entries);
  free(m);
}

void m_init(matrix *m) {
  unsigned int max = m->nrows * m->ncols;
  for (unsigned int i = 0; i < max; i++)
    m->entries[i] = (double)i + 1;
}

void m_print(matrix *m) {
  unsigned int nrows = m->nrows;
  unsigned int ncols = m->ncols;
  for (unsigned int i = 0; i < nrows * ncols; i++) {
    printf("%7.2f", m->entries[i]);
    if (i % ncols == ncols - 1)
      putchar('\n');
  }
}

void diag(matrix *t, matrix *s) {
  if ((t->nrows != s->nrows) || (t->ncols != s->ncols)) {
    fprintf(stderr, "%s: Matrices of different sizes\n", __FUNCTION__);
    exit(1);
  }
  unsigned int nrows = s->nrows;
  unsigned int ncols = s->ncols;
  unsigned int j;
  for (unsigned int i = 0; i < nrows; i++) {
    for (j = 0; j < ncols; j++) {
      if (i == j)
        (t->entries)[i * ncols + j] = (s->entries)[i * ncols + j];
      else
        (t->entries)[i * ncols + j] = 0;
    }
  }
}

void ldiag(matrix *t, matrix *s) {
  if ((t->nrows != s->nrows) || (t->ncols != s->ncols)) {
    fprintf(stderr, "%s: Matrices of different sizes\n", __FUNCTION__);
    exit(1);
  }
  unsigned int ncols = s->ncols;
  unsigned int nrows = s->nrows;
  unsigned int j;
  for (unsigned int i = 0; i < nrows; i++) {
    for (j = 0; j < ncols; j++) {
      if (i > j)
        (t->entries)[i * ncols + j] = (s->entries)[i * ncols + j];
      else
        (t->entries)[i * ncols + j] = 0;
    }
  }
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf("Usage: %s <nrows> <ncols>\n", argv[0]);
    return 1;
  }

  unsigned int nrows = atoi(argv[1]);
  unsigned int ncols = atoi(argv[2]);

  matrix *m = m_create(nrows, ncols);
  m_init(m);

  matrix *md = m_create(nrows, ncols);
  diag(md, m);

  matrix *mld = m_create(nrows, ncols);
  ldiag(mld, m);

  printf("\nm:\n");
  m_print(m);
  printf("\ndiag(m):\n");
  m_print(md);
  printf("\nldiag(m):\n");
  m_print(mld);
  printf("\n");

  m_destroy(m);
  m_destroy(md);
  m_destroy(mld);
  m = md = mld = NULL;

  return 0;
}
