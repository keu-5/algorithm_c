/* Page 110 */

/* List 8.1  •¶š—ñ‚Ì‚½‚ß‚ÌƒnƒbƒVƒ…ŠÖ” */

int hash(char *s)
{
    int i = 0;

    while (*s)
	i += *s++;
    return i % 100;
}
