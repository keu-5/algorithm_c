/* Page 188 */

/* List 12.2  選択ソート */


void selection_sort(int a[], int n)
{
    int i, j, t, lowest, lowkey;

    for (i = 0; i < n - 1; i++) {
	lowest = i;
	lowkey = a[i];
	for (j = i + 1; j < n; j++)
	    if (a[j] < lowkey) {
		lowest = j; lowkey = a[j];
	    }
	t = a[i]; a[i] = a[lowest]; a[lowest] = t;
    }
}
