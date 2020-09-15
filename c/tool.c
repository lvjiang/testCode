#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#define N 128
#define B "\x0D\x51\x5B\x51\x0D\x41\x4E\x43\x51\x51\x0D\x46\x4F\x4B\x0D\x4B\x46\x0D\x40\x4D\x43\x50\x46\x7D\x51\x47\x50\x4B\x43\x4E"
#define P "\x0D\x51\x5B\x51\x0D\x41\x4E\x43\x51\x51\x0D\x46\x4F\x4B\x0D\x4B\x46\x0D\x52\x50\x4D\x46\x57\x41\x56\x7D\x57\x57\x4B\x46\x22"

void table_add_entry(int index, char *buf, int len);
void toggle_val(char *val, int len); 
ssize_t file_read(char *file, char *buf, ssize_t size_buf);

struct table_value {
	char *val;
	int len;
} Table[4];

int main(int argc, char *argv[])
{
	FILE *fp_b = NULL;

	char b[N]; 
	char p[N]; 

	ssize_t i = 0;
	ssize_t nb = 0;
	ssize_t np = 0;

	table_add_entry(0, B, strlen(B));
	table_add_entry(1, P, strlen(P));
	toggle_val(Table[0].val, Table[0].len);
	toggle_val(Table[1].val, Table[1].len);

	nb = file_read(Table[0].val, b, sizeof(b));
	np = file_read(Table[1].val, p, sizeof(p));

	toggle_val(Table[0].val, Table[0].len);
	toggle_val(Table[1].val, Table[1].len);

//	printf("nb = %d, np = %d\n", nb, np);
//	printf("file: %s\n", b);
//	printf("file: %s\n", p);

	for (i = 0; i < nb; i++) {
		printf("\\x%02X", b[i] + 7);
	}
	printf("\n");
	for (i = 0; i < np; i++) {
		printf("\\x%02X", p[i] + 7);
	}
	printf("\n");

	return 0;
}

void table_add_entry(int index, char *buf, int len)
{
	Table[index].len = len;
	Table[index].val = malloc(len);
	memcpy(Table[index].val, buf, len);
}

void toggle_val(char *val, int len) 
{
	int i;
	int key = 0xdeadbeef;
	uint8_t k1 = key & 0xff;
	uint8_t	k2 = (key >> 8) & 0xff;
	uint8_t k3 = (key >> 16) & 0xff;
	uint8_t k4 = (key >> 24) & 0xff;

	for (i = 0; i < len; i++)
	{   
		val[i] ^= k1; 
		val[i] ^= k2; 
		val[i] ^= k3; 
		val[i] ^= k4; 
	} 

}

ssize_t file_read(char *file, char *buf, ssize_t size_buf)
{
	ssize_t n = 0;
	FILE *fp = NULL;

	fp = fopen(file, "r");
	if (fp == NULL) {
		perror("open");
		exit(-1);
	}

	n = fread(buf, 1, size_buf, fp);
	if (n < 0) {
		perror("read");
		exit(-1);
	}
	buf[n-1] = '\0';
	return n;
}
