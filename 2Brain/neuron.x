Neuron<
0 (
	sup ( @ready 0
		inf ( @dtchCytNeu 7
			sup ( @waitNeuron 2)
				detach ( :Cytosol_Neuron )
				add ( @dtchCytNeu 1 )
				set ( @waitNeuron 0 )
			)
			add ( @waitNeuron 1 )
		)
	)
)
>


Cytosol_Neuron<
0 (
	inf ( @CytoChan 4
 		inf ( @itNeuron 1
			var (
				&AtrCytosol (
					type ( to mv atr )
					act ( @AttachCyto  @CytoChan )
					pw ( 10 )
					dst ( 40 )
				)
				&AttachCytosol (
					type ( attach )
					act ( @CytoChan @NeuroCtyo )
					dst ( 40 )
				)
			)
			shared ( @AttachCyto 10 )
			set ( @AttachCyto 10 )
		) )
		set ( @itNeuron 1 )
		)
	)
	set ( @IMPULSE 10 )
	sup ( @CytoChan 0
		set ( @NeuronCyto 10 )
		&AttachCytosol ( type ( mv ) )
		&AtrCytosol ( pw ( 0 ) )
	)
)
>
