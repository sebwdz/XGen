
TO_EXTERN<
0 {
	$INF { @IT_ACT 1 $ADD { @IT_ACT 1 }
		$SET { @TO_ACT 20 }
		:TO_EXTERN_CHAN
	}
	$SUP { @IS_OK 0
		$INF { @IS_OK_IT 1 $SET { @IS_OK_IT 1 }
			$VAR { &MV_NCL { %PW { 5 } %DST { 60 } } }
		}
	}
	$INF { @IS_OK 1
		$SUP { @STK_ACT 3
			$ADD { @NCL_CJAN 4 }
			$ADD { @IS_OK 1 }
			$SET { @STK_ACT 0 }
			:BLK_EXTERN_CHAN
		}
		$SUP { @LIFE 50
			$ADD { @NCL_KILL 10 }
		
		}
	}
}
>

TO_SENS<
0 {
	$SUP { @IS_SENS 1
		$ADD { @STK_ACT @IS_SENS }
		$SET { @IS_SENS 0 }
	}
	$INF { @IT_SENS 1 $ADD { @IT_SENS 1 }
		$VAR {
			&MV_ACT { %ACT { @TO_ACT @IS_SENS } }
			&GET_ACT { %ACT { @TO_ACT @IS_SENS } }
		}
	}
}
>

TO_ACT<
0 {
	$SUP { @IS_ACT 1
		$ADD { @STK_ACT @IS_ACT }
		$SET { @IS_ACT 0 }
	}
	$INF { @IT_SENS 1 $ADD { @IT_SENS 1 }
		$VAR {
			&MV_ACT { %ACT { @TO_ACT @IS_ACT } }
			&GET_ACT { %ACT { @TO_ACT @IS_ACT } }
		}
	}
}
>
