package TestMod;

import basic;

local a, b, c;

function mod(a, b)
{
   /* q*b + r = a */
   local q;
   q = (a / b);
   return a - q*b;
} // mod

/* Test the modulo operator %
*/
for (local i = 0; i < 17; i++)
{
   for (local j = 1; j < 18; j ++)
      if (mod(i, j) != (i % j))
         basic.print("i = ", i, "  j = ", j, "  i % j = ", (i % j), " mod(i, j) = ", mod(i, j),"\n");
}
basic.print("\n");
