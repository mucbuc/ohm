
var assert = require( 'assert' )
  , path = require( 'path' )
  , cp = require( 'child_process' )
  , copy = require( 'fs-extra' ).copy
  , fs = require( 'graceful-fs' );

assert( typeof copy === 'function' );

function Base(program) {

    this.generate = function( defFile, defDir, cb ) {

        var buildDir = program.output;

        makePathIfNone(buildDir, function() {

            var include = program.gcc ? 'plank/def/cpp11-gcc.gypi' : 'plank/def/cpp11.gypi';
            var args = [
                    defFile,
                    '--depth=' + (program.gcc ? './' : '.'),
                    '--generator-output=' + buildDir,
                    '--include=' + include  
                ];

            if (program.gcc) {
                args.push( '--format=make' );
            }

            console.log( args );

            cp.spawn( 
                'gyp', 
                args, {
                    stdio: 'inherit',
                    cwd: defDir
                })
            .on( 'close', function( code ) {
                cb( code, buildDir );
            });
        });

        function makePathIfNone( path, cb ) {
            fs.exists(path, function(exists) {
                if (exists) 
                    cb();
                else 
                    fs.mkdir( path, [], cb ); 
            });
        }
    };

    this.traverse = function( testDir, cb ) {
        fs.readdir( testDir, function( err, files ) {
                files.forEach( function( file ) {
                    if (path.extname(file) == '.gyp') {
                        cb( file ); 
                    }
                } );    
            } );
    };

    this.build = function( defFile, buildDir, cb ) {
        readTargetName( defFile, program.path, function( targetName ) { 
            console.log( buildDir );
            var child; 
            if (program.gcc) {
                child = cp.spawn(
                    'make',
                    [ '-j'],
                    {
                        stdio: 'inherit',
                        cwd: buildDir
                    }); 
            }
            else {

                var args = [
                    "-project",
                    path.join( buildDir, targetName + '.xcodeproj' )
                ];

                console.log( args, buildDir ); 

                child = cp.spawn( 
                    'xcodebuild', 
                    args, {
                        cwd: buildDir,
                        stdio: 'inherit'
                    } ); 
            }

            child.on( 'close', function( code ) {
                cb( code, targetName, buildDir ); 
            } );
        } );

        function readTargetName(defFile, testDir, cb) {
            var defPath = path.join( testDir, defFile );
            fs.readFile( defPath, function( err, data ) {
                if (err) {
                    cursor.red();
                    process.stdout.write( defFile + ': ' );
                    cursor.reset();
                    console.log( err );
                }
                else {
                    var matches = data.toString().match( /'target_name'\s*:\s*'(.*)'/ )
                    if (matches) {
                        cb( matches[1] );
                    }
                }
            } ); 
        }
    };

    this.run = function( defFile, testDir, target, cb ) {
    
        var execPath;
        if (program.gcc) {
            testDir = path.join( testDir, 'out' );
        }
        execPath = path.join( testDir, 'Default', target );
        console.log( execPath );
        
        cp.spawn( 
            execPath, 
            [ 'http://localhost:3000' ], {
            stdio: 'pipe'
        })
        .on( 'close', function( code ) {
            cb( code );
            server.kill();
        })
        .stdout.on( 'data', function( data ) {
            cursor.blue();
            process.stdout.write( defFile + ': ' ); 
            cursor.reset();
            console.log( data.toString() );
        });
    };
}

module.exports = Base;
