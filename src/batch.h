#ifndef BATCH_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj
#define BATCH_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

#include "agent.h"

namespace om636 {
namespace control {
    template <typename T>
    class Batch {
    public:
        typedef T callback_type;
        typedef Agent<callback_type> agent_type;
        typedef std::weak_ptr<agent_type> pointer_type;
        typedef std::vector<pointer_type> batch_type;

        Batch() = default;
        virtual ~Batch() = default;
        Batch(const Batch&) = delete;
        Batch& operator=(const Batch&) = delete;

	template<class U>
        std::shared_ptr<U> hook(callback_type);

        void unhook();

        template <class ... V>
        void traverse(V ...);

        template <class ... V>
        void traverse_destructive(V ...);

        batch_type& elements();
        const batch_type& elements() const;

        void merge_added_elements();

    private:
        batch_type m_elements;
        batch_type m_elements_add;
    };

    namespace utils {

        template <typename T, typename ... V>
        void process_and_kill(T&, V...);

        template <typename T, typename ... V>
        void process(T&, V...);

        template <typename T>
        void kill_all(T&);
    }

} //control
} // om636

#include "batch.hxx"

#endif
