#ifndef FILE_WRITER_H_
#define FILE_WRITER_H_ 

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

typedef enum {
    ENCODING_UTF16,
    ENCODING_UTF32,
} EncodingType;

typedef enum {
    WRITE_TEXT,          // Open for writing in text mode
    WRITE_BINARY,        // Open for writing in binary mode
    WRITE_UNICODE,       // Open for writing Unicode text (may involve encoding conversions)
    WRITE_BUFFERED,      // Open for buffered writing (optimizes write operations)
    WRITE_UNBUFFERED,    // Open for unbuffered writing (direct write operations)
    WRITE_LINE,          // Open for line-by-line writing (useful for text files)
    WRITE_APPEND, 
} WriteMode;

typedef struct {
    FILE* file_writer;
    WriteMode mode;
    bool is_open;
    EncodingType encoding;
    char* file_path;
} FileWriter;


FileWriter* file_writer_open(const char* filename, const WriteMode mode);
FileWriter* file_writer_append(const char* filename, const WriteMode mode);

size_t file_writer_get_position(FileWriter* writer);
size_t file_writer_write(void* buffer, size_t size, size_t count, FileWriter* writer);
size_t file_writer_write_fmt(FileWriter* writer, const char* format, ...);
size_t file_writer_get_size(FileWriter* writer);

bool file_writer_write_line(char* buffer, size_t size, FileWriter* writer);
bool file_writer_close(FileWriter* writer);
bool file_writer_is_open(FileWriter* writer);
bool file_writer_flush(FileWriter* writer);
bool file_writer_set_encoding(FileWriter* writer, const EncodingType encoding);
bool file_writer_copy(FileWriter* src_writer, FileWriter* dest_writer);
bool file_writer_lock(FileWriter* writer);
bool file_writer_unlock(FileWriter* writer);

const char* file_writer_get_file_name(FileWriter* writer);
const char* file_writer_get_encoding(FileWriter* writer);

#endif 