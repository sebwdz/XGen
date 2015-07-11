CENTER<
0 {
	$UNSHARED { @ACTIVE_ACT }
	$INF { @IT 1 $ADD { @IT 5 }
		$INF { @CRT 8
			$SHARED { @ACTIVE_ACT }
			$INF { @TYPE 1 $SET { @ACTIVE_ACT 1 } }
			$SUP { @TYPE 0 $SET { @ACTIVE_ACT 5 } }
			$ADD { @TYPE 1 }
			$SUP { @TYPE 1
				$SET { @TYPE 0 }
			}
		}
		$ADD { @CRT 1 }
		$CREAT { :CELL }
	}
	$SUP { @CRT 18 $KILL { 0 } }
	$SUB { @IT 1 }
}
>

CELL<
0 {
	$INF { @CRT 5
		$INF { @CRT 1
			:NCL_KILL_CHAN
			$SHARED { @ACTIVE_ACT }
			$NEW_HEAD { :NUCLEUS }
		}
		$SUP { @CRT 0 
			$UNSHARED { @ACTIVE_ACT }
			$NEW_HEAD { :CYTO }
		}
		$ADD { @CRT 1 }
	}
	$SUP { @NCL_KILL 0 $KILL { 0 } }
	$SET { @CELL_CHAN 10 }
	$UNUSE { @SKL_CHAN @SKL_CNT }
	$UNUSE { @EXIT @EXEC @SLP }
}
>

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


CYTO<
0 {
	$INF { @IT 1 $ADD { @IT 1 }
		:SKL_CHAN
		:IMPULSE_CHAN
		:CYTO_CHAN
	}
	$SET { @SKL_CHAN 10 }
	$SET { @CYTO_CHAN 10 }
	$INF { @ACT 1 :CYTO_OFF }
	$SUP { @ACT 0 :CYTO_ON }
}
>
