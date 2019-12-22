namespace om636 {
namespace control {
    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    template <typename U>
    auto Batch<T>::hook(callback_type c) -> std::shared_ptr<U>
    {
        auto agent(std::make_shared<shared_agent<U>>(c));
        m_elements_add.push_back(agent);
        return agent;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    void Batch<T>::unhook()
    {
        utils::kill_all(elements());
        utils::kill_all(m_elements_add);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    template <class ... V>
    void Batch<T>::traverse(V ... arg)
    {
        merge_added_elements();

        utils::process(elements(), arg ... );
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    template <class ... V>
    void Batch<T>::traverse_destructive(V ... arg)
    {
        merge_added_elements();

        utils::process_and_kill(elements(), arg ...);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    auto Batch<T>::elements() -> batch_type&
    {
        return m_elements;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    auto Batch<T>::elements() const -> const batch_type&
    {
        return m_elements;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    void Batch<T>::merge_added_elements()
    {
        elements().insert(elements().end(), m_elements_add.begin(), m_elements_add.end());
        m_elements_add.clear();
    }

    namespace utils {
        /////////////////////////////////////////////////////////////////////////////////////
        template <typename T, typename ... V>
        void process(T& elements, V ... v)
        {
            T copy(elements);
            for_each(copy.begin(), copy.end(), [&](typename T::value_type p) {
                auto s(p.lock());
		if (s && !s->is_dead())
                    s->invoke(v ...);
                //else
                    //elements.erase(p);
            });
        }

        /////////////////////////////////////////////////////////////////////////////////////
        template <typename T, typename ... V>
        void process_and_kill(T& elements, V ... v)
        {
            T copy(elements);
            for_each(copy.begin(), copy.end(), [&](typename T::value_type p) {
                auto s(p.lock());
		if (s && !s->is_dead())
                    s->kill_invoke(v ...);
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
