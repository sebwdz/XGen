
Car<(
	?class
		?inhb :Vehicle ?inhc /__vehicle__ ?_ * (!this) ?_

		?m /start		?l :Car|start ?le
		?m /accelerate	?l :Car|accelerate ?le
	?eclass
)>

Car|start<( ?this
	echo ("Car " * (!prv /rnumber) " started\n")
)>

Car|accelerate<( ?this
	echo ("Car " * (!prv /rnumber) " accelerate\n")
)>