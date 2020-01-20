#ifndef EMITTER_IMPL_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj
#define EMITTER_IMPL_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj

#include <map>
#include <memory>
#include <set>

#include "interface.h"
#include <lib/dynamo/src/impl/batch.h> 


namespace om636 {
namespace control {
    template <typename T, typename... U>
    class EmitterImpl : Emitter<T, U...> {
    public:
        typedef T event_type;
	typedef Emitter<event_type, U...> base_type; 
	using typename base_type::callback_type;
        using typename base_type::listener_type;

        listener_type on(event_type, callback_type) override;
        listener_type once(event_type, callback_type) override;
        void interupt(event_type, U...) override;

    private:
        typedef BatchImpl<U...> batch_type;
        typedef std::map<event_type, batch_type> map_type;

        map_type m_repeat;
    };
} //control
} // om636

#include "emitter_impl.hxx"

#endif
