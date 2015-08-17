{
	'includes':[
		'lib/ohm/ohm.gypi',
		'plank/def/plank.gypi',
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
			'plank/src/',
			'.'
		], #include_dirs		
	}, #target_defaults
}