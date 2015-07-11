CYTO_OFF<
0 {
	$SET { @I 0 }
	$SET { @BASE 10 }
	$SET { @SLP 0 }
	$SUP { @IMPULSE 0
		$ADD { @EXIT @IMPULSE }
		$SET { @IMPULSE 0 }
	}
	$SUP { @EXEC 0 $SET { @ACT 1 } }
}
>

CYTO_ON<
0 {
	$SET { @BASE 0 }
	$SET { @EXEC 0 }
	$SUP { @SLP 0 $SET { @TMP 1 } }
	$SUP { @TMP 0
		$ADD { @I 1 }
		$SUP { @I 10
			$SET { @TMP 0 }
			$SET { @ACT 0 }
		}
	}
}
>

ATR_IMPULSE_CYTOSOL<
$VAR {
	&ATR_AXON {
		%TYPE { %OTH %CHNG %ATR }
		%ACT { @CYTO_CHAN @ATR_IMPULSE_AX }
		%PW { 10 }
		%DST { 60 }
	}
}
>

CYTO<
0 {
	$INF { @IT 1 $ADD { @IT 1 }
		:SKL_CHAN
		:IMPULSE_CHAN
		:CYTO_CHAN
		:ATR_IMPULSE_CYTOSOL
	}
	$SET { @SKL_CHAN 10 }
	$SET { @CYTO_CHAN 10 }
	$INF { @ACT 1 :CYTO_OFF }
	$SUP { @ACT 0 :CYTO_ON }

	$SET { @ATR_AXON @ATR_IMPULSE_AX }
	$SET { @ATR_IMPULSE_AX 0 }
}
>
