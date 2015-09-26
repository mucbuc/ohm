{
	'includes':[
		'lib/ohm/ohm.gypi',
	],#inclues
	'target_defaults': {
		'target_name': 'test',
		'type': 'executable',
		'sources': [
			'src/emitter.cpp',
			'src/emitter.h',
			'src/emitter_fwd.h',
		], #sources
		'include_dirs': [
			'.'
		], #include_dirs		
	}, #target_defaults
}