int Strnlen(const char *str, int count)
{
	const char *p;
	for (p = str; *p != '\0' && p < str + count; p++);
	return p - str;
}
