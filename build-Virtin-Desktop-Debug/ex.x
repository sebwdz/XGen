39 {
	$DUPLIC { %1 { $DUPLIC  { %1 } } }
	%6 { %8 %25
		$ADD { %1 { 1 } 41 }
	}
	%0 { 4 {
		$SET { %39 27 }
		%47 { %3 40 $SET 0 $ADD }
		20 { $SET %24 8 
		   $SET { %44 1 }
		   $SET { %5 }
	} }
	$NEW_HEAD {
		$SET { %39 17 }
		%24 {
			$SET { %28 60 }
			39 {5 0 $ADD $UNLINK }
		}
		$SET { %44 1 }
		$SET { %45 43 }
		$SET {%45 47 }
	}
}

TRUE<
0 {
	$DUPLIC { %1 }
	$DUPLIC { %1 }
	$ADD { %1 41 }
	0 {
		$SET { %39 17 }
		0 {
			$SET { %28 60 }
		}
		$SET { %44 1 }
		$SET { %45 43 }
		$SET { %45 47 }
	}
}
>
