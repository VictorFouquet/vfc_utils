#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_utils.h"

char* json_utils_escape(const char* str)
{
    if (!str) return str_utils_strdup("null");
    
    // Calculate required size (worst case: every char needs escaping)
    size_t len = strlen(str);
    size_t escaped_size = len * 2 + 1;
    
    char* escaped = malloc(escaped_size);
    if (!escaped) return NULL;
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++)
    {
        switch (str[i])
        {
            case '"':  escaped[j++] = '\\'; escaped[j++] = '"'; break;
            case '\\': escaped[j++] = '\\'; escaped[j++] = '\\'; break;
            case '\b': escaped[j++] = '\\'; escaped[j++] = 'b'; break;
            case '\f': escaped[j++] = '\\'; escaped[j++] = 'f'; break;
            case '\n': escaped[j++] = '\\'; escaped[j++] = 'n'; break;
            case '\r': escaped[j++] = '\\'; escaped[j++] = 'r'; break;
            case '\t': escaped[j++] = '\\'; escaped[j++] = 't'; break;
            default:
                if ((unsigned char)str[i] < 0x20)
                {
                    // Control characters: \uXXXX
                    j += snprintf(escaped + j, escaped_size - j, "\\u%04x", (unsigned char)str[i]);
                }
                else
                {
                    escaped[j++] = str[i];
                }
                break;
        }
    }
    escaped[j] = '\0';
    
    return escaped;
}
