package bug;

// Import the `basic' package
import basic;

// A function creating other functions !
function create( a )
{
	local func;

	// create a function bound to current lexical environment
	func = function( ) {
		// note that `a' is a parameter passed to create()
		return a * 5;
	};

	return func;
}

/*
 *  Here we start to execute package code
 */

local func1, func2;
local r1,    r2;

func1 = create( 2 );
func2 = create( 3 );

basic.print( "func1( 2 ) = ", func1(), "\n" );
basic.print( "func2( 3 ) = ", func2(), "\n" );
