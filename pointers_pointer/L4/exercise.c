void swap_ints(int *a, int *b) {
  int intermediate = *b;
  *b = *a;
  *a = intermediate;
}