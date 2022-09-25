#pragma once

#include "logger.hpp"

#define GET_FILE __FILE_NAME__
#define GET_FUNC __FUNCTION__
#define GET_LINE __LINE__

#define IF_LOG(severity) \
    if (logger::Logger::get() == nullptr || !logger::Logger::check_severity(severity)) {;} \
    else

#define LOG(severity) \
    IF_LOG(severity) *logger::Logger::get() \
        += logger::Record(severity, GET_FILE, GET_FUNC, GET_LINE)

#define LOGF LOG(logger::fatal)
#define LOGE LOG(logger::error)
#define LOGI LOG(logger::info)
#define LOGT LOG(logger::trace)
#define LOGD LOG(logger::debug)

#define LOG_FATAL LOGF
#define LOG_ERROR LOGE
#define LOG_INFO LOGI
#define LOG_TRACE LOGT
#define LOG_DEBUG LOGD
