#ifndef COMPONENT_UTILS_LOGGER_H
#define COMPONENT_UTILS_LOGGER_H
#include <stdio.h>

#ifdef ENABLE_LOG
#define LOG_DEBUG(format, args...) printf("[DEBUG] "format, ##args);
#define LOG_INFO(format, args...)  printf("[INFO ] "format, ##args);
#define LOG_WARN(format, args...)  printf("[WARN ] "format, ##args);
#define LOG_ERROR(format, args...) printf("[ERROR] "format, ##args);
#else
#define LOG_DEBUG(format, args...)
#define LOG_INFO(format, args...)
#define LOG_WARN(format, args...)
#define LOG_ERROR(format, args...)
#endif

#endif // COMPONENT_UTILS_LOGGER_H
