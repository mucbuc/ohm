namespace om636 {
namespace control {
    /////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T, template <typename> class P, typename ... U>
    void QuemitterImpl<T, P, U ...>::emit(event_type e, U ... v)
    {
        function_type p([e, v ..., this]() {
            base_type::interupt(e, v ...);
        });

        push_event(p);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, template <typename> class P, typename ... U>
    void QuemitterImpl<T, P, U ...>::push_event(function_type f)
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
