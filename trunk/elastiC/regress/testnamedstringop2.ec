package testnamedstringop2;

//import basic;

from basic import print, sprintf, repr;

print( 0xA5, "\n" );
print( 070, "\n" );
print( 0b1010, "\n" );

private v = { #var1 : "ciao", #var2 : 6.2, "var3": "hello" };

private anarray = (1,);

print( v[#var2], "\n" );
print( v[#var1], "\n" );
print( anarray, "\n" );
print( repr(v), "\n" );

anarray = {1};
print( anarray, "\n" );

anarray = {1, 2, 3, "four"};
print( anarray, "\n" );

anarray = (1, 2, 3, "four");
print( anarray, "\n" );

// simple example
//print( "%d, %s, %f\n" % #[ 12, "a string", 5.5 ] );

print( "%(var1)s, %(var2)g\n" % { #var2 : 6.2,
								  #var1 : "another string" } );
