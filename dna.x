
[ key
	_val  < /_range /_choice
	_valmin
	_valmax
	_choice

	_son < $code
	_sonmin
	_sonmax
	_soninf
	_somsup
]

[{inline}]range($min $max)<(
	gen (({_val /_range}{_valmin $min}{_valmax $max}))
)>

synapse<(
	[ weight ] :range (-1000 1000)
	[ expert ] :range (0 9)
	[ buy / sell ] :range (0 1)
)>

neuron<(
	[ biais ] :range (-1000 1000)
	[ synapses list ]
	gen ((
			{_son :synapse}
			{_sonmin 1}
			{_sonmax 15}
	))
)>

indicator<(
	[ type ] gen ((
			{_val /_choice}
			{_choice 0 (
					{bb[ period + ecartype ] (:range (10 200) :range (1 4))}
					{rsi 0} {roc 0} {macd 0} {tend 0}
					{will 0} {stoch 0} {direction 0}
			)}
			{_son [ period ]:range (10 200)}
			{_sonmin 1}
			{_sonmax 1}
			{_soninf 1}
	))
)>

expert<(:neuron :neuron)>

trader<(
	gen ((
			{_val /_choice}
			{_choice 0 (
				{_expert :expert}
				{_indicator :indicator}
			)}
	))
)>

layer<(
	gen ((
			{_son :trader}
			{_sonmin 2}
			{_sonmax 8}
	))
)>

dna<(
	:expert
	gen ((
			{_son :layer}
			{_sonmin 2}
			{_sonmax 10}
	))
)>

example<( [ OBSOLETE ]
	((-5 0 ((2 7 1)(1 -7 0)))(4 0 (3 2 0)(2 8 1)))
	0 (
		(
			({_indicator ({bb (20 2)})})
			({_expert (
					(3 0 ((0 4 1)(1 -8 0)))
					(9 0 (2 2 0)(1 8 1))
				)
			})
			({_expert (
					(7 0 ((0 3 1)(1 9 0)))
					(-2 0 (1 2 0)(3 8 1))
				)
			})
		)
		(
			({_indicator ({rsi (21)})})
			({_indicator ({macd (0)})})
			({_indicator ({stoch (35)})})
		)
	)
)>

current<(
	(
		()
		()
	)
	0 (
		(
				({_indicator})
				({_indicator})
				({_indicator})
				({_indicator})
				({_indicator})
				({_indicator})
				({_indicator})
				({_indicator})
				({_indicator})
		)
	)
)>