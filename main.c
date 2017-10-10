
#include <stdio.h>
#include <stdlib.h>

char* cstr_find_if(char*, char*);
char* cstr_replace_if(char*, char*, char*);

int main()
{
	char* init_cstr = "it is this what it is!";
	char* substr1 = "is";
	char* substr2 = "doesn't";

	char* first_occ = cstr_find_if(init_cstr, substr1);

	printf("%s\n", first_occ);

	return 0;
}

char* cstr_find_if(char* str, char* substr)
{
	size_t sub_len = 0;
	for (char* c = substr; *c != '\0'; ++c)
		++sub_len;

	for (char* c = str; *c != '\0'; ++c)
	{
		if (*c == *substr)
		{
			char* start = c;
			size_t counter = 0;
			for (char* j = substr; *j != '\0'; ++j)
			{
				if (*c++ != *j)
				{
					c = start;
					break;
				}
				++counter;
			}

			if (counter == sub_len)
				return start;
		}
	}

	return NULL;
}

char* cstr_replace_if(char* init_cstr, char* substr1, char* substr2)
{
	;
}
