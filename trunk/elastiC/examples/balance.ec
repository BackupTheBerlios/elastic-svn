package balance;

import basic;

public function new_account( amount )
	"This function creates a new bank account."
    "It uses anonymous function creation."
{
    return function( operation, args ... )
		"An anonymous function acting as a balance."
    {
        if (operation == #deposit)
		{
			amount += args[0];
			return amount;
		} else if (operation == #withdraw)
		{
			amount -= args[0];
			return amount;
		} else if (operation == #balance)
		{
			return amount;
		}
    };
}

local accountA = new_account( 100 );
local accountB = new_account( 20 );

basic.print( "Balance A: ", accountA(#balance), "\n" );
basic.print( "Balance B: ", accountB(#balance), "\n" );

basic.print( "Deposit 20 in A: ", accountA(#deposit, 20), "\n" );
basic.print( "Withdraw 5 from B: ", accountB(#withdraw, 5), "\n" );
