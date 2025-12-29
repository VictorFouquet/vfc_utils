#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "log_utils.h"
#include "json_utils.h"

typedef struct t_log_utils_event
{
    char* datetime;
    char* level;
    char* context;
    char* content;
} t_log_utils_event;

const t_log_utils_level LOG_UTILS_DEBUG = 0;
const t_log_utils_level LOG_UTILS_INFO  = 1;
const t_log_utils_level LOG_UTILS_WARN  = 2;
const t_log_utils_level LOG_UTILS_ERROR = 3;


static t_log_utils_level s_min_level = LOG_UTILS_DEBUG;

static const char* log_utils_level_string(t_log_utils_level level)
{
    if (level == LOG_UTILS_DEBUG) return "DEBUG";
    if (level == LOG_UTILS_INFO)  return "INFO";
    if (level == LOG_UTILS_WARN)  return "WARN";
    if (level == LOG_UTILS_ERROR) return "ERROR";
    return "UNKNOWN";
}

static void log_utils_timestamp(char* buffer, size_t size)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    
    struct tm* tm_info = localtime(&tv.tv_sec);
    
    // Format: YYYY/MM/DD HH:MM:SS:MSS
    snprintf(buffer, size, "%04d/%02d/%02d %02d:%02d:%02d:%03ld",
             tm_info->tm_year + 1900,
             tm_info->tm_mon + 1,
             tm_info->tm_mday,
             tm_info->tm_hour,
             tm_info->tm_min,
             tm_info->tm_sec,
             tv.tv_usec / 1000);
}

static void log_utils_log(t_log_utils_level level, const char* context, const char* format, va_list args)
{
    char timestamp[32];
    log_utils_timestamp(timestamp, sizeof(timestamp));
    
    // First pass: determine required size
    va_list args_copy;
    va_copy(args_copy, args);
    int content_size = vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);
    
    if (content_size < 0)
    {
        fprintf(stderr, "Error formatting log message\n");
        return;
    }
    
    // Allocate buffer for content
    char* content = malloc(content_size + 1);
    if (!content)
    {
        fprintf(stderr, "Failed to allocate memory for log content\n");
        return;
    }
    
    // Second pass: actually format the content
    vsnprintf(content, content_size + 1, format, args);
    
    // Escape strings for JSON
    char* escaped_context = json_utils_escape(context);
    char* escaped_content = json_utils_escape(content);
    
    if (!escaped_context || !escaped_content)
    {
        fprintf(stderr, "Failed to escape JSON strings\n");
        free(content);
        free(escaped_context);
        free(escaped_content);
        return;
    }
    
    // Build and print JSON
    printf("{ \"timestamp\": \"%s\", \"level\": \"%s\", \"context\": \"%s\", \"content\": \"%s\" }\n",
           timestamp,
           log_utils_level_string(level),
           escaped_context,
           escaped_content);
    
    // Cleanup
    free(content);
    free(escaped_context);
    free(escaped_content);
}

void log_utils_set_min_level(t_log_utils_level level)
{
    s_min_level = level;
}

void log_utils_debug(const char* context, const char* format, ...)
{
    if (s_min_level > LOG_UTILS_DEBUG)
    {
        return;
    }

    va_list args;
    va_start(args, format);
    log_utils_log(LOG_UTILS_DEBUG, context, format, args);
    va_end(args);
}

void log_utils_info(const char* context, const char* format, ...)
{
    if (s_min_level > LOG_UTILS_INFO)
    {
        return;
    }

    va_list args;
    va_start(args, format);
    log_utils_log(LOG_UTILS_INFO, context, format, args);
    va_end(args);
}

void log_utils_warn(const char* context, const char* format, ...)
{
    if (s_min_level > LOG_UTILS_WARN)
    {
        return;
    }

    va_list args;
    va_start(args, format);
    log_utils_log(LOG_UTILS_WARN, context, format, args);
    va_end(args);
}

void log_utils_error(const char* context, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    log_utils_log(LOG_UTILS_ERROR, context, format, args);
    va_end(args);
}
