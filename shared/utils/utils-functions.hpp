#ifndef UTILS_FUNCTIONS_H
#define UTILS_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "typedefs.h"
#include <string>
#include <string_view>

#ifndef __cplusplus
bool = uchar8_t;
#endif /* __cplusplus */

// Returns a string_view of the given Il2CppString*
std::u16string_view csstrtostr(Il2CppString* in);
// Sets the given cs_string using the given string/char16 array
void setcsstr(Il2CppString* in, std::u16string_view str);
// Converts a UTF16 string to a UTF8 string
std::string to_utf8(std::u16string_view view);
// Converts a UTF8 string to a UTF16 string
std::u16string to_utf16(std::string_view view);
// Dumps the 'before' bytes before and 'after' bytes after the given pointer to log
void dump(int before, int after, void* ptr);
// Reads all of the text of a file at the given filename. If the file does not exist, returns NULL
char* readfile(const char* filename);
// Writes all of the text to a file at the given filename. Returns either 0 or WriteError code
int writefile(const char* filename, const char* text);
// Returns if a file exists and can be written to / read from
bool fileexists(const char* filename);
// Returns if a directory exists and can be written to / read from
bool direxists(const char* dirname);

#endif /* UTILS_FUNCTIONS_H */
