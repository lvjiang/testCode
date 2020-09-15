int Strlen(char *str)
{
	int length = 0;
	while(*str++) {
		length++;
	}
	return length;
}
