#pragma once

#include <cstring>

#include "logger/logger.hpp"
#include "logger/record.hpp"

#define GET_FILE (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define GET_FUNC __FUNCTION__
#define GET_LINE __LINE__

#define LOG_(severity) \
    if (logger::Logger::get() == nullptr) {;} \
    else

#define LOG(severity) \
    LOG_(severity) *logger::Logger::get() \
        += logger::Record(severity, GET_FILE, GET_FUNC, GET_LINE)

#define LOG_FATAL   LOG(logger::fatal)
#define LOG_ERROR   LOG(logger::error)
#define LOG_WARN    LOG(logger::warn)
#define LOG_INFO    LOG(logger::info)
#define LOG_DEBUG   LOG(logger::debug)
#define LOG_TRACE   LOG(logger::trace)

#define LOGF LOG_FATAL
#define LOGE LOG_ERROR
#define LOGW LOG(logger::warn)
#define LOGI LOG_INFO
#define LOGD LOG_DEBUG
#define LOGT LOG_TRACE

#define LOG_IF(condition, severity) \
    if (!(condition)) {;} \
    else LOG(severity)

#define LOG_FATAL_IF(condition)   LOG_IF(condition, logger::fatal)
#define LOG_ERROR_IF(condition)   LOG_IF(condition, logger::error)
#define LOG_WARN_IF(condition)    LOG_IF(condition, logger::warn)
#define LOG_INFO_IF(condition)    LOG_IF(condition, logger::info)
#define LOG_DEBUG_IF(condition)   LOG_IF(condition, logger::debug)
#define LOG_TRACE_IF(condition)   LOG_IF(condition, logger::trace)

#define LOGF_IF(condition) LOG_FATAL_IF(condition)
#define LOGE_IF(condition) LOG_ERROR_IF(condition)
#define LOGW_IF(condition) LOG_WARN_IF(condition)
#define LOGI_IF(condition) LOG_INFO_IF(condition)
#define LOGD_IF(condition) LOG_DEBUG_IF(condition)
#define LOGT_IF(condition) LOG_TRACE_IF(condition)
