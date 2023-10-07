/* Page 201 */

/* List 13.1  シェルソート */

void shell_sort(int a[], int n)
{
    int h, i, j, t;

    for (h = 1; h < n/9; h = h * 3 + 1)
	;

    for (; h > 0; h /= 3) {
	for (i = h; i < n; i ++) {
	    j = i;
	    while (j >= h && a[j-h] > a[j]) {
		t = a[j]; a[j] = a[j-h]; a[j-h] = t;
		j -= h;
	    }
	}
    }
}
