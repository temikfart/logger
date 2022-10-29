#pragma once

#include "init.hpp"

#define GET_FILE __FILE_NAME__
#define GET_FUNC __FUNCTION__
#define GET_LINE __LINE__

#define IF_LOG(severity) \
    if (logger::Logger::get() == nullptr) {;} \
    else

#define LOG(severity) \
    IF_LOG(severity) *logger::Logger::get() \
        += logger::Record(severity, GET_FILE, GET_FUNC, GET_LINE)

#define LOG_FATAL   LOG(logger::fatal)
#define LOG_ERROR   LOG(logger::error)
#define LOG_INFO    LOG(logger::info)
#define LOG_TRACE   LOG(logger::trace)
#define LOG_DEBUG   LOG(logger::debug)

#define LOGF LOG_FATAL
#define LOGE LOG_ERROR
#define LOGI LOG_INFO
#define LOGT LOG_TRACE
#define LOGD LOG_DEBUG
