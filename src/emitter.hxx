namespace om636
{
	namespace control
	{
		
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		auto Emitter<T, U>::on( event_type e, callback_type c ) -> listener_type
		{
        	return m_repeat[e].hook( c );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		auto Emitter<T, U>::once( event_type e, callback_type c ) -> listener_type
		{
        	return m_once[e].hook( c );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		void Emitter<T, U>::removeListeners( event_type e )
		{
            m_once[e].unhook();
            m_repeat[e].unhook();
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		void Emitter<T, U>::removeAllListeners()
		{
            kill_all( m_once );
            kill_all( m_repeat );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		void Emitter<T, U>::emit( event_type e)
		{ 
            m_once[e].traverse_destructive();
            m_repeat[e].traverse();
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		template<class V>
		void Emitter<T, U>::emit( event_type e, V arg)
		{ 
            m_once[e].traverse_destructive(arg);
            m_repeat[e].traverse(arg);
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		template<typename V, typename W>
		void Emitter<T, U>::emit( event_type e, V first_arg, W second_arg )
		{ 
            m_once[e].traverse_destructive(first_arg, second_arg);
            m_repeat[e].traverse(first_arg, second_arg);
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T, typename U>
        void Emitter<T, U>::kill_all(map_type & map)
        {
            for_each(map.begin(), map.end(), [](typename map_type::value_type & p) {
                p.second.unhook();
            } );
            map.clear();
        }
        
    } 	// control 
}	// om636