namespace om636 {
namespace control {

    template <typename T, typename ... U>
    class EmitterImpl : Emitter<T, ...U> 
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
    };

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
    void EmitterImpl<T, U ...>::interrupt(event_type e, U ... arg)
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
