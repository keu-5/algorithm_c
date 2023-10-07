/* Page 201 */

/* List 13.2  ‘}“üƒ\[ƒg */

void insertion_sort(int a[], int n)
{
    int i, j, t;

    for (i = 1; i < n; i++) {
	j = i;
	while (j >= 1 && a[j-1] > a[j]) {
	    t = a[j]; a[j] = a[j-1]; a[j-1] = t;
	    j--;
	}
    }
}
