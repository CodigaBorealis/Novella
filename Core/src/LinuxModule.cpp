#include "../Novella/Scripting/API/LinuxModule.hpp"
#include <cstdlib>
#include <pwd.h>
#include <stdexcept>
#include <unistd.h>
#include <sys/types.h>
#include <vector>
namespace Novella::NScript::Modules::Linux{

    std::string getUserEnv(Runtime::Context &context){

        long n = sysconf(_SC_GETPW_R_SIZE_MAX);

        if(n == -1) n = 16384;

        std::vector<char> buf(static_cast<size_t>(n));

        struct passwd pw,*res = nullptr;

        if(getpwuid_r(getuid(), &pw, buf.data(), buf.size(), &res) == 0 && res && pw.pw_name) return pw.pw_name;

        const char* username = getenv("USER");

        if(username) return std::string(username);

        throw std::runtime_error("NovellaScript Runtime Error: Could not determine current username");
    }

}