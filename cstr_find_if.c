#include <stdio.h>
#include <stdlib.h>

size_t cstr_len(char*);
char* cstr_find_if(char*, char*);

int main()
{
	char* initCstr = "it is iiiiisss this what it is";
	char* subStr1 = "is";
	char* result = cstr_find_if(initCstr, subStr1);

	if (result)
		puts(result);

	return 0;
}


/* return cstr length */
size_t cstr_len(char* cstr)
{
	size_t len = 0;
	while (cstr[len])
		++len;

	return len;
}

/* return pointer to first occurence of substr in str or NULL if no matches found */
char* cstr_find_if(char* str, char* substr)
{
	size_t sub_len = cstr_len(substr);

	int i = 0;
	while (str[i] != '\0')
	{
		int j = 0;
		while (str[i] == substr[j] && substr[j] != '\0')
		{
			++i, ++j;
		}

		if (j == sub_len)
			return &str[i - j];
		else
			i -= j;

		++i;
	}

	return NULL;
}
