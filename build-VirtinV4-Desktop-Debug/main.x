<:NODE1:
0
{
	$USE	{ %8 %1 }
	$ADD	{ %8 50 }
	$ADD	{ %8 %8 }
	$INF	{ %1 1
		0 {
			$CREAT	{ 0 X:NODE2 }
			$ADD	{ %1 1 }
		  }
		}
}
:>

<:NODE2
0
{
	$USE	{ %2 }
	$ADD	{ %2 5 }
	0	{
			$SUP {%2 10
			     0	{
					$USE { %8 }
					$ADD { %8 10 }
			  	}
			$SUP {%2 30
			     0 {
					$UNUSE { %8 }
					$SET { %8 0 }
			  	}			  
		}
}
:>
