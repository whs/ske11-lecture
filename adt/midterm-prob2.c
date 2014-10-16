#include <stdio.h>
#include <string.h>

void _compute_union(char *str_out, char *str, int hashtable[58], int *cnt){
	int i, j;
	for(i = 0, j = strlen(str); i < j; i++){
		int ascii = (int) str[i];
		ascii -= 65; // ascii of A
		if(hashtable[ascii] > 0){
			continue;
		}
		str_out[*cnt] = str[i];
		hashtable[ascii]++;
		*cnt = *cnt + 1;
	}
}

void str_union(char *str_out, char *str1, char *str2){
	int hashtable[58] = {};
	int cnt = 0;
	_compute_union(str_out, str1, hashtable, &cnt);
	_compute_union(str_out, str2, hashtable, &cnt);
	str_out[cnt] = 0;
}
void str_intersect(char *str_out, char *str1, char *str2){
	int hashtable[58] = {};
	int cnt = 0;
	int i, j;
	for(i = 0, j = strlen(str1); i < j; i++){
		int ascii = (int) str1[i];
		ascii -= 65; // ascii of A
		hashtable[ascii] = 1;
	}
	for(i = 0, j = strlen(str2); i < j; i++){
		int ascii = (int) str2[i];
		ascii -= 65; // ascii of A
		if(hashtable[ascii]){
			str_out[cnt] = str2[i];
			cnt++;
			// prevent double
			hashtable[ascii] = 0;
		}
	}
	str_out[cnt] = 0;
}

int main(){
	char str1[30] = "Hello";
	char str2[30] = "World";
	char str_out[30];
	str_union(str_out, str1, str2);
	printf("%s\n", str_out);
	str_intersect(str_out, str1, str2);
	printf("%s\n", str_out);
	return 0;
}
