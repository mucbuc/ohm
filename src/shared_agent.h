#ifndef SHARED_AGENT_H_OWKJEKJKWKW3929293
#define SHARED_AGENT_H_OWKJEKJKWKW3929293

#include <functional>

#include <lib/dynamo/src/agent.h>

namespace om636 {
namespace control {

template<typename T, typename U...>
struct shared_agent : T, Agent<U...>
{
  template<class V> 
  shared_agent(V && cb);

  ~shared_agent() override = default;

  void invoke(...U) override;
  void kill_invoke(...U) override;
  void kill() override;
  bool is_dead() override; 

private: 
  typedef std::function<void(U...)> callback_type;
  callback_type m_callback;
};

} // control
} // om636

#include "shared_agent.hxx"

#endif // SHARED_AGENT_H_OWKJEKJKWKW3929293
