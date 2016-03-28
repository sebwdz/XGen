<
	?scope		2;
	?limit		4;

	[ TYPE ]
	?manual		0;
	?link			1;
	?attach		2;
	?comin		3;
	
	[ SCOPE ]
	?oth			0;
	?link			1;
	?son			2;
	?parent		3;
	?network	4;
>

Interaction|Construct<(
	[ ATTRIBUTS ]
	(
		cp (* (#this /_exec) 0)
		cp (* (#this /_clean) 0)
		cp (* (#this /_param) 0 (
				[ dst ] [ mindst ]
				[ scope ] [ type ]
				[ limit ]
		))
	)
)>