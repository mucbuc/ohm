#ifndef EMITTER_IMPL_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj
#define EMITTER_IMPL_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj

#include <map>
#include <memory>
#include <set>

#include "interface.h" 

namespace om636 {
namespace control {
    template <typename T, typename ... U>
    class EmitterImpl : Emitter<T, U ...> 
    {
    public:
        typedef T event_type;
        typedef std::function<void(U...)> callback_type;
        typedef Batch<callback_type> batch_type;
        typedef typename batch_type::listener_type listener_type;

        listener_type on(event_type, callback_type);
        listener_type once(event_type, callback_type);

        void removeListeners(event_type);
        void removeAllListeners();

        void interupt(event_type, U ...);
   private:
        typedef std::map<event_type, batch_type> map_type;
        void kill_all(map_type&);

        map_type m_repeat;
        map_type m_once;
    };
} //control
} // om636

#include "emitter_impl.hxx"

#endif
