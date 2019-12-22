namespace om636 {
namespace control {

    /////////////////////////////////////////////////////////////////////////////////////
    // shared_agent
    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename U...>
    shared_agent<T, U...>::Agent(callback_type callback)
        : m_callback(callback)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename U...>
    void shared_agent<T, U...>::invoke(U ... args)
    {
        ASSERT(!is_dead());
        m_callback(... args);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename U...>
    void shared_agent<T, U...>::kill_invoke(U ... args)
    {
        ASSERT(!is_dead());
        callback_type temp(m_callback);
        kill();
        temp(...args);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename U...>
    void shared_agent<T, U...>::kill()
    {
        m_callback = callback_type();
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename U...>
    bool shared_agent<T, U...>::is_dead()
    {
        return !m_callback;
    }

} //control
} // om636amespace om636 {

