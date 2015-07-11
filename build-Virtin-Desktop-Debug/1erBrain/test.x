MAIN<
0 {
	$INF { @WHO 10 :SENSOR }
	$SUP { @WHO 9 :ACT }
}
>

SENSOR<
0 {
	$SET{ @IMPULSE @RES }
	$SET { @RES 0 }
	$SET { @BASE 0 }
	$INF { @IT 1 $ADD { @IT 1 }
		$SET { @IS_SENS 10 }
	}
	$INF { @IS_SENS 6
		$SET { @IS_SENS 0 }
		$SET { @ATACH 10 }
	}
}
>

ACT<
0 {
	$SUP { @GOOD 0
		$ADD { @ATR_IMPULSE_AX @GOOD }
		$SET { @GOOD 0 }
	}
	$SUP { @IMPULSE 0
		$SET { @RES @IMPULSE }
		$SET { @IMPULSE 0 }
	}
	$SET { @BASE 10 }
	$INF { @IT 1
		:IMPULSE_CHAN
		$SET { @IS_ACT 10 }
		$ADD { @IT 1 }
	}
	$INF { @IS_ACT 6
		$SET { @IS_ACT 0 }
		$SET { @ATACH 10 }
	}
}
>
