#ifndef EMITTER_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj
#define EMITTER_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj

#include <functional>
#include <map>
#include <memory>
#include <set>

#include <lib/dynamo/src/batch.h>

namespace om636 {
namespace control {

    template <typename T, typename... U>
    class Emitter {
    public:
        typedef T event_type;
        typedef std::function<void(U...)> callback_type;
        typedef Batch<callback_type> batch_type;
        typedef typename batch_type::listener_type listener_type;

        virtual ~Emitter() = default;

        virtual listener_type on(event_type, callback_type) = 0;
        virtual listener_type once(event_type, callback_type) = 0;

        virtual void removeListeners(event_type) = 0;
        virtual void removeAllListeners() = 0;

        virtual void interupt(event_type, U...) = 0;
    };

    template <typename T, typename... U>
    class Quemitter : public Emitter<T, U...> {

    public:
        typedef Emitter<T, U...> base_type;
        using typename base_type::batch_type;
        using typename base_type::callback_type;
        using typename base_type::event_type;
        using typename base_type::listener_type;

        virtual ~Quemitter() = default;
        virtual void emit(event_type, U...) = 0;
    };

} //control
} // om636

#endif
