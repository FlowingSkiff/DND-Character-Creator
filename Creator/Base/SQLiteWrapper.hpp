#pragma once
#include "sqlite3.h"
#include <string>
#include <memory>
#include <sstream>
#include <optional>
#include <iostream>
#include <vector>
#include "StringTools.hpp"


#ifdef SQWRAPPERDEBUG
    #define private public
#endif

namespace Creator
{
    namespace Entity{ 
        struct SQObject; 
        SQObject* CreateNewObjectByType(int typearg, int argc, char** argv, char** col);
    };
    void CallbackPrint(void* unused, int argc, char** argv, char** col);
    void CallbackAssignToVector(void* container, int argc, char** argv, char** col);
    enum class SQLiteError
    {
        OK = 0, BADQUERY
    };
    class SQLiteWrapper
    {
        public:
            SQLiteWrapper();
            SQLiteWrapper(const std::string& filename);
            SQLiteWrapper(sqlite3* db);
        public: 
            template<typename... Args>
            SQLiteError Query(std::string temp, Args... args);
        private:
            template<typename T>
            std::optional<std::string> Prepare(const std::string& input, const T& arg);
            template<typename First, typename... Args>
            std::optional<std::string> Prepare(const std::string& input, const First& first, const Args&... args);
        private:
            std::unique_ptr<sqlite3*> m_instance;
            SQLiteError m_status;
            mutable char* m_error;
    };

    template<typename... Args>
    SQLiteError SQLiteWrapper::Query(std::string temp, Args... args)
    {
        std::optional<std::string> cmd = Prepare(temp, args...);
        if (cmd.has_value)
        {
            temp = cmd.value;
            sqlite3_exec(m_instance.get(), cmd, 0, 0, &m_error);
        }
        return m_status;
    }
    
    template<typename T>
    std::optional<std::string> SQLiteWrapper::Prepare(const std::string& input, const T& rhs)
    {
        size_t ins = input.find_first_of('?');
        if (ins == std::string::npos)
        {
            m_status = SQLiteError::BADQUERY;
            return {};
        }
        std::ostringstream stream; 
        stream << input.substr(0, ins);
        stream << rhs << input.substr(ins + 1);
        return stream.str();
    }
    template<typename First, typename... Args>
    std::optional<std::string> SQLiteWrapper::Prepare(const std::string& input, const First& first, const Args&... args)
    {
        size_t ins = input.find_first_of('?');
        if (ins == std::string::npos)
        {
            m_status = SQLiteError::BADQUERY;
            return {};
        }
        std::ostringstream stream; 
        stream << input.substr(0, ins);
        stream << first << input.substr(ins + 1);
        return Prepare(stream.str(), args...);
    }


    
    void CallbackPrint(void* unused, int argc, char** argv, char** col)
    {
        for (int i = 0; i < argc; ++i)
        {
            std::cout << col[i] << ": " << (argv[i] ? argv[i] : "NULL") << '\n';
        }
    }
    void CallbackAssignToVector(void* container, int argc, char** argv, char** col)
    {
        std::vector<Entity::SQObject*>* vec = static_cast<std::vector<Entity::SQObject*>*>(container);
        int type = -1;
        for (int i = 0; i < argc && type == -1; ++i)
        {
            if (SafeCompareString(argv[i], "type"))
                type = i;
        }
        if (type != -1)
        {
            vec->push_back(Entity::CreateNewObjectByType(type, argc, argv, col));
        }
    }
};



#ifdef SQWRAPPERDEBUG
    #undef private
#endif