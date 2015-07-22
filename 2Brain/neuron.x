Neuron<
0 (
	sup ( @ready 0
		:Create_Link
		inf ( @dtchCytNeu 6
			sup ( @waitNeuron 3
				detach ( :Cytosol_Neuron )
				add ( @dtchCytNeu 1 )
				set ( @waitNeuron 0 )
			)
		)
		add ( @waitNeuron 1 )
		sup ( @waitNeuron 30
			inf ( @nclNeu 1
				sup ( @ready 1
					detach ( :Nucleus_Neuron )
					add ( @nclNeu 1 )
				)
			)
		)
	)
)
>


Atr_Impulse<
0 (
	inf ( @itAtrImp 1
		:Atr_Impulse_Chan
		add ( @itAtrImp 1 )
	)
	inf ( @active 1 set ( @Base 10 ) )
	sup ( @Impulse 0
		add ( @impulseStk @Impulse )
		set ( @Impulse 0 )
	)
)
>

Cytosol_Neuron<
0 (
	inf ( @CytoChan 4
 		inf ( @itNeuron 1 add ( @itNeuron 1 )
			var (
				&AttachCytosol (
					type ( attach )
					act ( @CytoChan @NeuronCyto )
					dst ( 20 )
				)
			)
		)
	)
	sup ( @CytoChan 0
		inf ( @itCytoN 1
			:Cytosol_Neuron_Chan
			var ( &AttachCytosol ( type ( mv ) ) )
			set ( @itNeuron 0 )
			set ( @itCytoN 1 )
		)
		:Atr_Impulse
		sup ( @impulseStk 0
			add ( @ImpulseCyto @impulseStk )
			set ( @impulseStk 0 )
		)
		sup ( @ExecNcl 0
			set ( @Base 0 )
			sub ( @ExecNcl 2 )
			set ( @ImpulseCyto 0 )
		)
	)
	set ( @NeuronCyto 10 )
)
>

Create_Link<
0 (
	sup ( @LifeNeuron 80
		inf ( @nbDen 1
			add ( @nbDen 1 )
		)
		set ( @LifeNeuron 0 )
	)
	add ( @LifeNeuron 1 )
)
>

Nucleus_Neuron_DECR<
0 (
	inf ( @NclChan 1
		inf ( @itNclNeuron 1
			:Nucleus_Neuron_Attach
			set ( @itNclNeuron 1 )
			set ( @nclNeuronAtt 0 )
		)
	)
	sup ( @NclChan 0
		inf ( @nclNeuronAtt 1
			var ( &AttachNucleus ( type ( mv ) ) )
			set ( @nclNeuronAtt 1 )
			set ( @itNclNeuron 0 )
		)
	)
)
>

Nucleus_Cycle<
0 (
	set ( @ExecNcl 0 )
	sup ( @impulseStk @biais
		inf ( @inExec 1 add ( @inExec 1 ) )
	)
	sup ( @inExec 0
		var ( &AtrImpulse ( pw ( 0 ) ) )
		sup ( @inExec 3
			add ( @Impulse @debit )
			sub ( @impulseStk @debit )
		)
		add ( @inExec 1 )
		set ( @ExecNcl 10 )
	)
	inf ( @impulseStk @debit
		sup ( @inExec 1
			var ( &AtrImpulse ( pw ( 20 ) ) )
			set ( @inExec 0 )
		)
	)
)
>

Nucleus_Neuron<
0 (
	:Nucleus_Neuron_DECR
	sup ( @NclChan 0
		inf ( @itNclNeuronCrt 1
			:Atr_Imp_Ncl_Neuron
			set ( @NclNeuron 10 )
			add ( @itNclNeuronCrt 1 )
			set ( @biais 50 )
			set ( @debit 10 )
		)
		sup ( @ImpulseCyto 0
			add ( @impulseStk @ImpulseCyto )
			set ( @ImpulseCyto 0 )
		)
		sup ( @NclChan 0 :Nucleus_Cycle )
	)
	sup ( @inExec 0
		sup ( @ready 0
			inf ( @haveAxon 1 creat ( :Link ) add ( @haveAxon 1 ) )
		)
	)
)
>
