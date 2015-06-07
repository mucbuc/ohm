
var assert = require( 'assert' )
  , path = require( 'path' )
  , cp = require( 'child_process' )
  , copy = require( 'fs-extra' ).copy
  , fs = require( 'graceful-fs' );

assert( typeof copy === 'function' );

function Base(program) {

  this.generate = function( o, cb ) {

    var buildDir = program.output;

    makePathIfNone(buildDir, function() {

      var include = program.gcc ? 'plank/def/cpp11-gcc.gypi' : 'plank/def/cpp11.gypi';
      var args = [
          o.defFile,
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
          cwd: o.defDir
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

  this.traverse = function( o, cb ) {
    fs.readdir( o.testDir, function( err, files ) {
      files.forEach( function( file ) {
        if (path.extname(file) == '.gyp') {
          cb( file ); 
        }
      } );    
    } );
  };

  this.build = function( o, cb ) {
    
    readTargetName( o.defFile, program.path, function( targetName ) { 
      console.log( o.buildDir );
      var child; 
      if (program.gcc) {
        child = cp.spawn(
          'make',
          [ '-j'],
          {
            stdio: 'inherit',
            cwd: o.buildDir
          }); 
      }
      else {

        var args = [
          "-project",
          path.join( o.buildDir, targetName + '.xcodeproj' )
        ];

        console.log( args, o.buildDir ); 

        child = cp.spawn( 
          'xcodebuild', 
          args, {
            cwd: o.buildDir,
            stdio: 'inherit'
          } ); 
      }

      child.on( 'close', function( code ) {
        o['target'] = targetName;
        o['exitCode'] = code;
        cb( o ); 
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

  this.run = function( o, cb ) {
    console.log( '** run' );
    var execPath;
    if (program.gcc) {
      o.testDir = path.join( o.testDir, 'out' );
    }
    console.log( '*** run', o );
    execPath = path.join( o.buildDir, 'Default', o.target );
    console.log( execPath );
    

    console.log( '**** run' );
    cp.spawn( 
      execPath, 
      [ 'http://localhost:3000' ], {
      stdio: 'inherit'// pipe'
    })
    .on( 'error', function( error ) {
    })
    .on( 'close', function( code ) {
      cb( code );
      //server.kill();
    })
    // .stdout.on( 'data', function( data ) {
    //   cursor.blue();
    //   process.stdout.write( o.defFile + ': ' ); 
    //   cursor.reset();
    //   console.log( data.toString() );
    // });
  };
}

module.exports = Base;
