/* Page 186 */

/* List 12.1  バブルソート */


void bubble_sort(int a[], int n)
{
    int i, j, t;

    for (i = 0; i < n - 1; i++)
	for (j = n - 1; j > i; j --)
	    if (a[j-1] > a[j]) {
		t = a[j]; a[j] = a[j-1]; a[j-1] = t;
	    }
}
