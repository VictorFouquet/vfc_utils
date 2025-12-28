#ifndef LOG_UTILS_H
#define LOG_UTILS_H

typedef int t_log_utils_level;

// Public constants for log levels
extern const t_log_utils_level LOG_UTILS_DEBUG;
extern const t_log_utils_level LOG_UTILS_INFO;
extern const t_log_utils_level LOG_UTILS_WARN;
extern const t_log_utils_level LOG_UTILS_ERROR;

void log_utils_set_min_level(t_log_utils_level level);
void log_utils_debug(const char* context, const char* format, ...);
void log_utils_info(const char* context, const char* format, ...);
void log_utils_warn(const char* context, const char* format, ...);
void log_utils_error(const char* context, const char* format, ...);

#endif /* LOG_UTILS_H */
