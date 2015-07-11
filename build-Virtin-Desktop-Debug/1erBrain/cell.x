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
	$SUP { @CRT 15 $KILL { 0 } }
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
	$SET { @CELL_CHAN 20 }
	$UNUSE { @SKL_CHAN @SKL_CNT }
	$UNUSE { @EXIT @EXEC @SLP }
}
>
