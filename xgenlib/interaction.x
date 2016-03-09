<
	?scope		1;
	?limit		4;

	[ TYPE ]
	?manual		0;
	?link			1;
	?attach		2;
	?comin		3;
	
	[ SCOPE ]
	?link			0;
	?oth			1;
	?son			2;
	?parent		3;
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