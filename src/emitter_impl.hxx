namespace om636 {
namespace control {

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename ... U>
    auto EmitterImpl<T, U ...>::on(event_type e, callback_type c) -> listener_type
    {
        return m_repeat[e].hook(c);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename ... U>
    auto EmitterImpl<T, U ...>::once(event_type e, callback_type c) -> listener_type
    {
        return m_once[e].hook(c);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename ... U>
    void EmitterImpl<T, U ...>::removeListeners(event_type e)
    {
        m_once[e].unhook();
        m_repeat[e].unhook();
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename ... U>
    void EmitterImpl<T, U ...>::removeAllListeners()
    {
        kill_all(m_once);
        kill_all(m_repeat);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename ... U>
    void EmitterImpl<T, U ...>::interupt(event_type e, U ... arg)
    {
        m_once[e].merge_added_elements();
        m_repeat[e].merge_added_elements();

        utils::process_and_kill(m_once[e].elements(), arg ... );
        utils::process(m_repeat[e].elements(), arg ... );
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename ... U>
    void EmitterImpl<T, U ...>::kill_all(map_type& map)
    {
        for_each(map.begin(), map.end(), [](typename map_type::value_type& p) {
            p.second.unhook();
        });
        map.clear();
    }

} // control
} // om636