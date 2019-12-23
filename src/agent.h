#ifndef AGENT_H__0OiXEmL5tPcgUywQFDMW6Gv1J8Hdzo
#define AGENT_H__0OiXEmL5tPcgUywQFDMW6Gv1J8Hdzo

namespace om636 {
namespace control {

    template <typename... T>
    struct Agent {
        virtual ~Agent() = default;
        virtual void invoke(T...) = 0;
        virtual void kill_invoke(T...) = 0;
        virtual void kill() = 0;
        virtual bool is_dead() = 0;
    };

} //control
} // om636

#endif // AGENT_H__0OiXEmL5tPcgUywQFDMW6Gv1J8Hdzo
