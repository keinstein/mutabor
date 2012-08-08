# This file is a modified file from the midge examples.
# You can install midge and translate it into a midi file

@head {
	$tempo 1200
	$time_sig 4/4
}

@body {
	@channel 1 {
		$patch ocarina
		$length 4

		+/a127/c5   # note on c5 (w/ attack 127)
		r           # c5 plays for 1/4 note before other notes start
        /a31/e5 
		/a63/g 
		/a127/e4      # play e4, g4, e4 over the c5
        r           # c5 plays for 1/4 note after other notes
		-/d127/c5    # note off c5 (w/ decay 127)
	}
}
