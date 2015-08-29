Test< /* => 0X000 */
0 (
	£Ptr2	/* boucle inf */
	£Ptr 	/* Attention Recurcivité */
)
>

Function<
0 (
	ref ( £Ptr @Var ) /* £Ptr Pointe sur @Var */
	ref ( £Ptr2 £Ptr ) /* £Ptr2 Pointe sur @Var */

	?labelx		/* ?labelx Pointe sur le add */
	add ( £Ptr 10 ) /* set @Var à 10 */
	/* multi line
		comment */
	ref ( £Ptr $Test )	/* Ptr pointe sur Test ( 0x000 ) */
	ref ( £Ptr2 %labelx )
	£Ptr			/* Appel le code de Test ( 0x000 ) */
)
>

/*
Premiere etape
	Pointeur sur variable

Bien plus tard

Deuxieme etape
	Pointeur sur Code
Troisieme etape
	Label
*/

Function<
0 (
	/* ref permet de referencer une variable */
	ref ( £Ptr @Var1 )
	set ( @Var1 10 )
	set ( £Ptr 5 )
)
>
