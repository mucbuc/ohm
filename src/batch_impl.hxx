namespace om636 {
namespace control {
    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    auto BatchImpl<T...>::hook(std::function<void(T...)> callback) -> std::shared_ptr<agent_type>
    {
        auto agent(std::make_shared<shared_agent<T...>>(callback));
        m_elements_add.push_back(agent);
        return agent;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    void BatchImpl<T...>::unhook()
    {
        utils::kill_all(elements());
        utils::kill_all(m_elements_add);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    void BatchImpl<T...>::traverse(T... arg)
    {
        merge_added_elements();

        utils::process(elements(), arg...);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    void BatchImpl<T...>::traverse_destructive(T... arg)
    {
        merge_added_elements();

        utils::process_and_kill(elements(), arg...);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    auto BatchImpl<T...>::elements() -> batch_type&
    {
        return m_elements;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    auto BatchImpl<T...>::elements() const -> const batch_type&
    {
        return m_elements;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    void BatchImpl<T...>::merge_added_elements()
    {
        elements().insert(elements().end(), m_elements_add.begin(), m_elements_add.end());
        m_elements_add.clear();
    }

    namespace utils {

        /////////////////////////////////////////////////////////////////////////////////////
        template <typename T, typename... V>
        void process(T& elements, V... v)
        {
            T copy(elements);
            for_each(copy.begin(), copy.end(), [&](typename T::value_type p) {
                auto s(p.lock());
                if (s && !s->is_dead())
                    s->invoke(v...);
                //else
                //elements.erase(p);
            });
        }

        /////////////////////////////////////////////////////////////////////////////////////
        template <typename T, typename... V>
        void process_and_kill(T& elements, V... v)
        {
            T copy(elements);
            for_each(copy.begin(), copy.end(), [&](typename T::value_type p) {
                auto s(p.lock());
                if (s && !s->is_dead())
                    s->kill_invoke(v...);
            });
            elements.clear();
        }

        /////////////////////////////////////////////////////////////////////////////////////
        template <typename T>
        void kill_all(T& elements)
        {
            for_each(elements.begin(), elements.end(), [](typename T::value_type p) {
                auto s(p.lock());
                if (s) {
                    s->kill();
                }
            });
            elements.clear();
        }
    } // utils
} // control
} // om636
