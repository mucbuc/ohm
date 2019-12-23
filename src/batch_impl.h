#ifndef BATCHIMPL_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj
#define BATCHIMPL_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj

#include <algorithm>
#include <memory>
#include <vector>

#include "batch.h"
#include "shared_agent.h"

namespace om636 {
namespace control {
    template <typename... T>
    class BatchImpl : public Batch<T...> {
    public:
        typedef Batch<T...> base_type;
        using typename base_type::agent_type;

        BatchImpl() = default;
        ~BatchImpl() override = default;

        std::shared_ptr<agent_type> hook(std::function<void(T...)>) override;
        void unhook() override;
        void traverse(T...) override;
        void traverse_destructive(T...) override;

        template <typename U, typename V>
        std::shared_ptr<U> hook(V);

    private:
        typedef std::weak_ptr<agent_type> pointer_type;
        typedef std::vector<pointer_type> batch_type;
        batch_type& elements();
        const batch_type& elements() const;

        void merge_added_elements();

        batch_type m_elements;
        batch_type m_elements_add;
    };

    namespace utils {

        template <typename T, typename... V>
        void process_and_kill(T&, V...);

        template <typename T, typename... V>
        void process(T&, V...);

        template <typename T>
        void kill_all(T&);

        struct empty_base {
            virtual ~empty_base() = default;
        };
    }

} //control
} // om636

#include "batch_impl.hxx"

#endif
