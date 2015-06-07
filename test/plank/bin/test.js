#!/usr/bin/env node

var assert = require( 'assert' )
  , events = require( 'events' )
  , path = require( 'path' )
  , fs = require( 'graceful-fs' )
  , emitter = new events.EventEmitter
  , program = require( 'commander' )
  , Base = require( './base' )
  , Printer = require( './printer' )
  , Logic = require( './logic' )
  , base
  , logic;

assert( typeof Logic !== 'undefined' );

program
	.version( '0.0.0' )
	.option( '-p, --path [path]', 'test path' )
	.option( '-o, --output [path]', 'build output' )
	.option( '-g, --gcc', 'use gcc compiler' )
	.parse( process.argv );

if (!program.path) {
	program.path = path.join( __dirname, '../..' );
}
else {
	program.path = path.join( __dirname, '../..', program.path );
}

if (!program.output) {
	program.output = path.join( __dirname, '../..', 'build' );
}
else {
	program.output = path.join( __dirname, '../..', program.output );
}

attachLogic( emitter );

base = new Base(program);
logic = new Logic( base );

emitter.emit( 'traverse', program.path );

function attachLogic(emitter) {

	emitter.on( 'run', function( o ) {
		console.log( 'run attachLogic', o ); 
		logic.run( o );
	}); 

	emitter.on( 'build', function( defFile, testDir ) {
		logic
		.build( defFile, testDir )
		.then( function(exitCode, targetName, buildDir) {
			console.log( 'build complete' );
			emitter.emit( 'run', { 
				defFile: defFile, 
				buildDir: buildDir, 
				targetName: targetName
			} );
		})
		.catch( function() {
			console.log( 'build failed' );
		});
	});

	emitter.on( 'generate', function( defFile, testDir ) {
		logic
		.generate(defFile, testDir)
		.then( function(buildDir) {
			emitter.emit( 'build', defFile, buildDir );
		});
	});

	emitter.on( 'traverse', function(testDir) {
		logic
		.traverse( testDir )
		.then( function( testDir ) {
			base.traverse( testDir, function(gypFile) {
				emitter.emit( 'generate', gypFile, testDir );
			});
		});
	});
}
