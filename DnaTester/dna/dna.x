
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

[{inline}]
range($min $max)<(
	gen ({_val /_range}{_valmin $min}{_valmax $max})
)>

synapse<(
	[ weight ] :range (-1000 1000)
	[ expert ] :range (0 14)
	[ buy / sell ] :range (0 1)
)>

neuron<(
	gen (
			{_val /_choice}
			{_choice (
					/accu /sigmoid
					/gauss /unit
			)}
			{_son (:range (-1000 1000) :range (0 100)
							:range (1 10) :range (1 10))}
			{_sonmin 1}{_sonmax 1}
	)
	[ synapses list ]
	gen (
			{_son :synapse}
			{_sonmin 1}
			{_sonmax 30}
	)
)>

indicator<(
	gen (
			{_val /_choice}
			{_choice (
				 	/rsi /roc /macd /tend
					/will /stoch /dir /res /sup
			)}
			{_son (:range (7 150) :range (1 400))} [period + ecart type (bb / sup /res) | analyse ]
			{_sonmin 2}
			{_sonmax 2}
	)
)>

expert<(:neuron :neuron)>

trader($choice)<(
	gen (
			{_val /_choice}
			$choice
	)
)>

layer<(
	gen (
			{_son :trader ({_choice ({_expert :expert}{_indicator :indicator})})}
			{_sonmin 5}
			{_sonmax 15}
	)
)>

layer_indicator<(
	gen (
			{_son :trader ({_choice ({_indicator :indicator})})}
			{_sonmin 5}
			{_sonmax 15}
	)
)>

moneyMagement<(
	(:range (0 5) :range (5 50) :range (2 20)) [ecart type period affinage]
	(:range (1 500) :range (1 500)) [take profit stop loose]
	(:range (1 1000)) [action rate]
	(:range (1 70) :range (1 70)) [(adjust limit) (buy limit)]
)>

dna<(
	(:expert :expert :expert) [(decision up * down) (ajust up * adjust down) (guard * reliability)]
	:layer_indicator
	gen (
			{_son :layer}
			{_sonmin 1}
			{_sonmax 5}
	)
	:moneyMagement
)>