namespace om636
{
    namespace control 
    {
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T, typename U>
        void Quemitter<T, U>::emit( event_type e)
        {
            std::function<void()> p = [&]() {
                base_type::emit( e );
            }; 

            push_event( p );
        }
       
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T, typename U>
        template<class V> 
        void Quemitter<T, U>::emit( event_type, V v )
        {
            std::function<void()> p = [&]() {
                base_type::emit( e, v );
            }; 

            push_event( p );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T, typename U>
        template<typename V, typename W> 
        void Quemitter<T, U>::emit( event_type e, V v, W w )
        {
            std::function<void()> p = [&]() {
                base_type::emit( e, v, w );
            }; 

            push_event( p );
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, template<class> class V>
        void Quemitter<T, U, V>::push_event( std::function<void()> f )
        {
            std::unique_lock<mutex_type> lock( m_mutex, std::try_to_lock );
            if (lock.owns_lock())
                do
                    f();
                while (m_queue.try_pop(f));
            else
                m_queue.push( f );
        }

    }   //control
}   // om636