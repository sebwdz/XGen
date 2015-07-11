CENTER<
0 {
	$EGAL { %5 3
		$INF { %7 1
			$SET { %7 30 }
		}
	}
	$ADD { %3 1 }
	$INF { %1 1 $SET { %1 31 } }
	$SUP { %3 20
		$SUP { %7 1
			$SUB { %7 1 }
		}
		$INF { %7 2
			$ADD { %5 1 }
			$CREAT { :PARENT }
			$SET { %3 0 }
		}
	}
	$SUP { %5 4
		$INF { %5 8
			
			$SET { %52 20 }
			$SET { %53 0 }
		}
		$SUP { %5 7
			$SET { %52 0 }
		}
	}
	$INF { %1 2 
		$ADD { %2 1 }
		$SUP { %2 10 $KILL { 0 } }
		$SET { %48 5 }
		$SET { %49 0 }
	}
}
>

PARENT<
0 {
	$ADD { %3 1 }
	$INF { %1 1 $SET { %1 6 } }
	$NEW_HEAD { :USE }
	$SUP { %3 3 
		$UNUSE { %53 %52 %46 %47 }
	}
}
>

USE<
0 {
	$ADD { %3 1 }
	$SUP { %3 4
		$ADD { %6 1 }
		$INF { %1 1 $SET { %1 26 } }
		$SUP { %6 10 
			$INF { %6 14
				$NEW_HEAD { :USESON }
			}
		}
		$INF { %6 2
			$NEW_HEAD { :NUCLEUS }
		}
		
	}
	$SET { %53 0 }
	$INF { %3 3
		$SET{ %53 20 }
		$SUP { %52 0
			$ADD { %8 2 }
			$SET { %52 0 }
		}
	}
	$SUP { %8 1
		$SET { %46 20 }
		$SET { %47 0 }
		$SET { %8 0 }
	}
	$UNUSE { %35 %34 }
}
>

USESON<
0 {
	$SET { %35 10 }
	$SET { %49 10 }
	$SUP { %48 0
		$ADD { %48 1 }
	}
}
>

NUCLEUS<
0 {
	$SET { %30 10 }
	$SET { %19 2 }
	$SET { %34 30 }
	$SET { %47 10 }
	$SUP { %46 0
		$SET { %36 %8 }
	}
	$INF { %46 1
		$SET { %37 %8 }
	}
	$SUB { %4 1 }
	$INF { %4 1 
		$INF { %8 12
			$ADD { %8 1 }
		}
		$SUB { %19 1 }
	}
	$SUP { %45 2 
		$ADD { %19 1 }
		$SET { %45 0 }
		$SUB { %8 2 }
		$SET { %4 5 }
	}
	$SET { %44 5 }
}
>
