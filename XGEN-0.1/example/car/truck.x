
Truck<(
	?class
		?inhb :Vehicle ?inhc /__vehicle__ ?_ * (!this) ?_

		?m /start		?l :Truck|start ?le
		?m /accelerate	?l :Truck|accelerate ?le
	?eclass
)>

Truck|start<( ?this
	echo ("Truck " * (!prv /rnumber) " started\n")
)>

Truck|accelerate<( ?this
	echo ("Truck " * (!prv /rnumber) " accelerate\n")
)>