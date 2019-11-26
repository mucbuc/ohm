#ifndef EMITTER_IMPL_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj
#define EMITTER_IMPL_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj

#include <map>
#include <memory>
#include <set>

#include "emitter.h" 

namespace om636 {
namespace control {
    
    template<typename T, typename ... U> 
    Emitter<T, ...U> * make_emitter();
} //control
} // om636

#include "emitter.hxx"

#endif
