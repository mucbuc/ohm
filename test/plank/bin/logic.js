var assert = require( 'assert' )
  , Promise = require( 'promise' ) 
  , Printer = require( './printer' )
  , fs = require( 'graceful-fs' );

function Logic(base) {

	this.traverse = function(testDir) {
		return new Promise(function(resolve, reject) {
				console.log( 'got traverse' );
				fs.exists(testDir, function(exists) {
					console.log( 'got exists' );
					if (exists) { 
						resolve( testDir ); 
					}
					else {
						Printer.cursor.red();
						process.stdout.write( 'invalid test definition path: ');
						Printer.cursor.reset();
						console.log( testDir ); 
						reject();
					}
				});
			});

	};

	this.generate = function(defFile, testDir) {
		return new Promise(function(resolve, reject) {
				Printer.begin( defFile, 'generate' );
				base.generate( defFile, testDir, function( exitCode, buildDir ){
					if (!exitCode) {
						Printer.finishGreen( defFile, 'generate' );
						resolve(buildDir)
					}
					else {
						Printer.finishRed( defFile ) ; 
						reject(buildDir); 
					}
				});
			});
	};

	this.run = function(o) {
		console.log( "outside logic run" );
		return new Promise(function(resolve, reject) {
				console.log( "logic run" );
				Printer.begin( defFile, 'run' );
				base.run( o, function(exitCode) {
					if (!exitCode) {
						Printer.finishGreen( o.defFile );
						console.log( '=> ' + o.targetName + ' passed' );
						resolve(exitCode);
					}
					else {
						Printer.finishRed( o.defFile ) ; 
						console.log( '=> ' + o.targetName + ' failed with exit code:', exitCode );
						reject(exitCode);
					}
				});
			});
	}; 

	this.build = function(defFile, testDir) {
		return new Promise( function(resolve, reject) {
				Printer.begin( defFile, 'build' );
				base.build( defFile, testDir, function( exitCode, targetName, buildDir ) { 
					if (!exitCode) {
						Printer.finishGreen( defFile );
						resolve( { defFile: defFile, buildDir: buildDir, targetName: targetName } );
					}
					else {
						Printer.finishRed( defFile );
						reject(defFile); 
					}
				});
			});
	};
};

module.exports = Logic;