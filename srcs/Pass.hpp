#ifndef PASS_HPP
# define PASS_HPP

#include <string>

class Pass {
    private:
        std::string _password;
    public:
        Pass();
        Pass(std::string password);
        ~Pass();
        void setPassword(std::string password);
        const std::string& getPassword() const;
};

#endif