#ifndef BATCH_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj
#define BATCH_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj

#include <memory>

#include "agent.h"

namespace om636 {
namespace control {
    template <typename... T>
    class Batch {
    public:
        typedef Agent<T...> agent_type;

        virtual ~Batch() = default;
        virtual std::shared_ptr<agent_type> hook(std::function<void(T...)>) = 0;
        virtual void unhook() = 0;
        virtual void traverse(T...) = 0;
        virtual void traverse_destructive(T...) = 0;
    };

} //control
} // om636

#endif
