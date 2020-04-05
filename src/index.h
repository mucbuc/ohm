#pragma once
#include <memory>

#include "emitter_impl.h"
#include "quemitter_impl.h"

namespace om636 {
namespace control {

    template <typename T, typename... U>
    std::shared_ptr<Emitter<T, U...>> make_Emitter()
    {
        return std::make_shared<EmitterImpl<T, U...>>();
    }

    template <typename T, typename... U>
    std::shared_ptr<Emitter<T, U...>> make_Quemitter()
    {
        return std::make_shared<QuemitterImpl<T, default_policy, U...>>();
    }

} // control
} // om636
