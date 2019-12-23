#ifndef SHARED_AGENT_H_OWKJEKJKWKW3929293
#define SHARED_AGENT_H_OWKJEKJKWKW3929293

#include <functional>

#include "agent.h"

namespace om636 {
namespace control {

    template <typename... T>
    struct shared_agent : Agent<T...> {
        template <class V>
        shared_agent(V&& cb);

        ~shared_agent() = default; //override = default;

        void invoke(T...) override;
        void kill_invoke(T...) override;
        void kill() override;
        bool is_dead() override;

    private:
        typedef std::function<void(T...)> callback_type;
        callback_type m_callback;
    };

} // control
} // om636

#include "shared_agent.hxx"

#endif // SHARED_AGENT_H_OWKJEKJKWKW3929293
