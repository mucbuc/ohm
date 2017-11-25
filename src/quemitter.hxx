namespace om636 {
namespace control {
    /////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename U, template <typename> class P>
    void Quemitter<T, U, P>::emit(event_type e)
    {
        function_type p([e, this]() {
            base_type::emit(e);
        });

        push_event(p);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename U, template <typename> class P>
    template <class V>
    void Quemitter<T, U, P>::emit(event_type e, V v)
    {
        function_type p([e, v, this]() {
            base_type::emit(e, v);
        });

        push_event(p);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T, typename U, template <typename> class P>
    template <typename V, typename W>
    void Quemitter<T, U, P>::emit(event_type e, V v, W w)
    {
        function_type p([e, v, w, this]() {
            base_type::emit(e, v, w);
        });

        push_event(p);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U, template <typename> class P>
    void Quemitter<T, U, P>::push_event(function_type f)
    {
        m_queue.push(f);
        fbp::pushed_event(*this);

        std::unique_lock<mutex_type> lock(m_mutex, std::defer_lock);
        while (lock.try_lock()
            && fbp::locked_mutex(*this)
            && m_queue.try_pop(f)) {
            f();

            lock.unlock();
            fbp::unlocked_mutex(*this);
        }
    }

} //control
} // om636
