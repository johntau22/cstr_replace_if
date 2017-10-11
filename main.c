#include <stdio.h>
#include <stdlib.h>

size_t cstr_len(char*);
char* cstr_find_if(char*, char*);
char* cstr_replace_if(char*, char*, char*);

int main()
{
	char* str = "it is this what it is";
	char* substr1 = "is";
	char* substr2 = "where";
	char* result = cstr_replace_if(str, substr1, substr2);

	if (result == NULL)
	{
		printf("No matches found");
		printf("%c", '\n');
		return 1;
	}
	else
	{
		printf(result);
		printf("%c", '\n');
	}

	return 0;
}

/* replace all ocurrences of substr1 in cstr_init to substr2 */
char* cstr_replace_if(char* cstr_init, char* substr1, char* substr2)
{
	size_t cstr_init_len = cstr_len(cstr_init);
	size_t substr1_len = cstr_len(substr1);
	size_t substr2_len = cstr_len(substr2);

	/* register substr1 ocurrence positions */
	char** occ_pos = malloc(cstr_init_len * sizeof(char*)); /* max case is every single char in cstr_init matches with substr1*/

	size_t occ_count = 0;
	char* c = cstr_init;
	char* s = substr1;

	if (cstr_find_if(c, s) == NULL)
		return cstr_init; /* exit, no matches found */

	char* occ;
	while (occ = cstr_find_if(c, s))
	{
		*occ_pos++ = occ;
		++occ_count;
		c = occ + substr1_len;
	}
	occ_pos -= occ_count;

	/* DEBUG */
	/*for (int i = 0; i < occ_count; ++i)
	{
		printf(occ_pos[i]);
		printf("%c", '\n');
	}*/

	
	if (occ_count < cstr_init_len)
	{
		occ_pos = realloc(occ_pos, occ_count * sizeof(char*));	// free unused memory
	}

	/* calculate new c_string size */
	size_t new_cstr_len = cstr_init_len;
	if (substr2_len > substr1_len)
	{
		new_cstr_len = cstr_init_len + (substr2_len - substr1_len) * occ_count + 1;
	}

	char* new_cstr = malloc(new_cstr_len * sizeof(char));

	int i = 0, j = 0;	// indices for init_cstr and new_cstr
	while (cstr_init[i] != '\0')
	{
		if (&cstr_init[i] == *occ_pos)
		{
			int m = 0;
			while (m < (int)substr2_len)
			{
				new_cstr[j+m] = substr2[m];
				++m;
			}
			++occ_pos;
			i += substr1_len;
			j += substr2_len;
		}
		else
		{
			new_cstr[j++] = cstr_init[i++];
		}
	}

	occ_pos -= occ_count;
	free(occ_pos);

	new_cstr[new_cstr_len - 1] = '\0';
	
	return new_cstr;
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
			while (substr[j] != '\0')
			{
				if (str[i] != substr[j])
				{
					i -= j; /* rollback to initial position on first char match */
					break;
				}
				++i, ++j;
			}

			if (j == sub_len)
				return &str[i-j];
		}
		++i;
	}

	return NULL;
}
