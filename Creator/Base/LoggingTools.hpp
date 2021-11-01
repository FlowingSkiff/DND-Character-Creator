#pragma once
#include <fstream>
#ifndef DOLOG
    #define DOLOG 0
#elif DOLOG
    #include "spdlog/spdlog.h"
    #include "spdlog/sinks/basic_file_sink.h"
#endif

/**
 * @brief Logging static class which holds the logging options. 
 *        Logs warnings and worse for log.log
 *        Logs warnings and worse to the console
 *        Logs all messages to debug.log
 * 
 */
class Logfile
{
    public:
        static std::shared_ptr<spdlog::logger> GetInstance()
        {
            #if DOLOG
            if (m_instance == nullptr)
            {
                std::vector<spdlog::sink_ptr> sinks;
                sinks.push_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());
                sinks.back()->set_level(spdlog::level::warn);
                sinks.back()->set_pattern("[%^%l%$] %v");
                sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.log"));
                sinks.back()->set_pattern("[%^%l%$] %v");
                sinks.back()->set_level(spdlog::level::warn);
                sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/debug.log"));
                sinks.back()->set_pattern("[%^%l%$] DEBUG: %v");
                sinks.back()->set_level(spdlog::level::trace);
                m_instance = std::make_shared<spdlog::logger>("multi_sink", std::begin(sinks), std::end(sinks));
                m_instance->set_level(spdlog::level::trace);
            }
            #endif
            return m_instance;
        }
    private:
        static std::shared_ptr<spdlog::logger> m_instance;
};

/**
 * @brief Basic logging function which writes information to the log tools.
 * 
 * @tparam First String to use with fmt with supplied args
 * @tparam Args On or more items to format First with
 * @param first Input fmt string
 * @param args fmt arguments
 */
template<typename First, typename... Args>
void Log(const First& first, const Args&... args)
{
    #if DOLOG
        //LOGGING_OUTPUT << first << ' ';
        //Log(args...);
        Logfile::GetInstance()->info(first, args...);
    #endif
}


/**
 * @brief Specialized logging function for writing information
 * 
 * @tparam First String to use with fmt with supplied args
 * @tparam Args On or more items to format First with
 * @param first Input fmt string
 * @param args fmt arguments
 */
template<typename First, typename... Args>
void LogInfo(const First& first, const Args&... args)
{
    #if DOLOG
        //LOGGING_OUTPUT << first << ' ';
        //Log(args...);
        Logfile::GetInstance()->info(first, args...);
    #endif
}

/**
 * @brief Specialized logging function for writing critical information
 * 
 * @tparam First String to use with fmt with supplied args
 * @tparam Args On or more items to format First with
 * @param first Input fmt string
 * @param args fmt arguments
 */
template<typename First, typename... Args>
void LogCritical(const First& first, const Args&... args)
{
    #if DOLOG
        //LOGGING_OUTPUT << first << ' ';
        //Log(args...);
        Logfile::GetInstance()->critical(first, args...);
    #endif
}

/**
 * @brief Specialized logging function for writing warnings
 * 
 * @tparam First String to use with fmt with supplied args
 * @tparam Args On or more items to format First with
 * @param first Input fmt string
 * @param args fmt arguments
 */
template<typename First, typename... Args>
void LogWarn(const First& first, const Args&... args)
{
    #if DOLOG
        //LOGGING_OUTPUT << first << ' ';
        //Log(args...);
        Logfile::GetInstance()->warn(first, args...);
    #endif
}

/**
 * @brief Specialized logging function for writing debug information
 * 
 * @tparam First String to use with fmt with supplied args
 * @tparam Args On or more items to format First with
 * @param first Input fmt string
 * @param args fmt arguments
 */
template<typename First, typename... Args>
void LogDebug(const First& first, const Args&... args)
{
    #if DOLOG
        //LOGGING_OUTPUT << first << ' ';
        //Log(args...);
        Logfile::GetInstance()->debug(first, args...);
    #endif
}

/**
 * @brief Specialized logging function for writing error information
 * 
 * @tparam First String to use with fmt with supplied args
 * @tparam Args On or more items to format First with
 * @param first Input fmt string
 * @param args fmt arguments
 */
template<typename First, typename... Args>
void LogError(const First& first, const Args&... args)
{
    #if DOLOG
        //LOGGING_OUTPUT << first << ' ';
        //Log(args...);
        Logfile::GetInstance()->error(first, args...);
    #endif
}