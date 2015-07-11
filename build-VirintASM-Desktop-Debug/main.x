NODE1<
0 { 0 {
	:NODE2
	$USE	{ %8 %1 }
	$INF	{ %8 10 $ADD	{ %8 10 } }
	$INF	{ %1 8
		0 {
			$CREAT	{ 0 :NODE3 :NODE2 }
			$ADD	{ %1 1 }
		  }
		}
}
}
>
NODE2<
0
{
	$USE	{ %2 }
	$ADD	{ %2 5 }
	0	{
			$SUP	{ %2 10
				0	{
						$USE	{ %4 }
						$ADD	{ %4 10 }
					}
				}
			$SUP 	{ %2 30 $ADD { %4 12 }
				0	{

					}
				}
		}
	:NODE3
}
>
