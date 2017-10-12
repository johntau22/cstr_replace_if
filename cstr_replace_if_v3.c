#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

size_t cstr_len(char*);
char* cstr_find_if(char*, char*);
void paste_str(char*, char*, int);
bool cstr_replace_if(char*, char*, char*, char*, short*);

int main()
{
	char* initCstr = "it is this what it is";
	char* subStr1 = "is";
	char* subStr2 = "where";
	short outSize = 10;
	char* outStr = malloc(outSize * sizeof(char));

	if (cstr_replace_if(initCstr, subStr1, subStr2, outStr, &outSize))
	{
		puts(outStr);
		puts("SYSTEM: Buffer was long enough.");
		//printf("%c", '\n');
	}
	else
	{
		puts(outStr);
		puts("SYSTEM: Buffer was too short, reallocation have been done.");
	}

	return 0;
}

/* replace all ocurrences of substr1 in cstr_init to substr2.
true if outCstr long enough to contain changes or no changes made, false otherwise */
bool cstr_replace_if(char* cstr_init, char* substr1, char* substr2, char* io_buff, short* outSize)
{
	bool result;
	size_t cstr_init_len = cstr_len(cstr_init);
	size_t substr1_len = cstr_len(substr1);
	size_t substr2_len = cstr_len(substr2);

	/* register substr1 ocurrence positions */
	char** occ_pos = malloc(cstr_init_len * sizeof(char*)); /* max case is every single char in cstr_init matches with substr1 */

	size_t occ_count = 0;
	char* c = cstr_init;
	char* s = substr1;

	if (cstr_find_if(c, s) == NULL)
	{
		paste_str(io_buff, cstr_init, cstr_init_len);
		io_buff[cstr_init_len] = '\0';
		result = false;
		return result;	//	exit, no matches found
	}

	char* occ;
	char** pos = occ_pos;
	while (occ = cstr_find_if(c, s))
	{
		*pos++ = occ;
		++occ_count;
		c = occ + substr1_len;
	}

	/* calculate new c_string size */
	size_t new_cstr_len = cstr_init_len;
	if (substr2_len != substr1_len)
		new_cstr_len = cstr_init_len + (substr2_len - substr1_len) * occ_count + 1;

	if (new_cstr_len > (unsigned)*outSize)
	{
		io_buff = realloc(io_buff, new_cstr_len * sizeof(char));
		result = false;	// too short buffer, realloc used
	}
	else
	{
		result = true;	// long enough buffer
	}

	pos = occ_pos;
	int i = 0, j = 0;	// indices for init_cstr and new_cstr
	while (cstr_init[i] != '\0')
	{
		if (&cstr_init[i] == *pos)
		{
			paste_str(&io_buff[j], substr2, substr2_len);
			++pos;
			i += substr1_len;
			j += substr2_len;
		}
		else
		{
			io_buff[j++] = cstr_init[i++];
		}
	}
	io_buff[new_cstr_len - 1] = '\0';

	free(occ_pos);

	return result;
}

/* paste substr with n legth into string starting from paste_start */
void paste_str(char* paste_start, char* substr, int n)
{
	for (int j = 0; j < n; ++j)
	{
		paste_start[j] = substr[j];
	}
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
		if (str[i] == substr[0])
		{
			int j = 0;
			while (str[i] == substr[j] && substr[j] != '\0')
			{
				++i, ++j;
			}

			if (j == sub_len)
				return &str[i - j];
		}
		++i;
	}

	return NULL;
}
