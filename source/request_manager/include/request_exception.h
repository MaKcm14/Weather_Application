#ifndef REQUEST_EXCEPTION_HEADER

#    include <exception>
#    include <string>

namespace NRequest {

    /// @brief Exceptions specially for request actions (including cache's actions)
    /// ~ error's id classification:
    /// - 400 - client's errors:
    ///       - 401: (invalid data)
    ///       - 402: (data can't be read from the source)
    ///       - 403: (can't set the connection with the server)
    ///       - 404: (the request wasn't processed correctly)
    ///       - 405: (data are suspicious)
    ///
    /// - 500 - server-side's errors:
    ///       - 501: (boost::asio exceptions)
    ///       - 502: (nlohmann::json exceptions)
    ///       - 503: (STL exceptions)
    ///       - 504: (PostgreSQL exceptions)
    
    class TRequestException : public std::exception {
    public:
        TRequestException(const std::string& description, int32_t errorId = 500)
            : What(description)
            , ErrorId(errorId)
        {
        }


        int32_t GetErrorId() const noexcept {
            return ErrorId;
        }

        const char* what() const noexcept override {
            return What.c_str();
        }


    private:
        std::string What;
        int32_t ErrorId;

    };

}


#endif


#define REQUEST_EXCEPTION_HEADER
