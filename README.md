# chengine
Minimalist UCI chess engine

	Features:

		- 0x88 board representation;
		- material only evaluation;
		- nega max search;
		- UCI protocol with fixed depth search only;
		
	After for about a three years of researching how
	does particularly a chess engine works and numerous
	unsuccessful attempts to write one own I've finally
	managed to complete one.
	
	Chengine is very slow and weak engine due to the lack of
	piece lists, king square and material tracking. the brute
	force nega max search doesn't cut any garbage branches, so
	it takes ages to get the best move even at depth 6, but
	nevertheless it is already a complete engine to play chess.
	
	For now I have no idea how to proceed with the development.
	There are several directions to follow such as minimize the
	code size like in Toledo nanochess or MicroMax or try to
	improve playing strength at least a bit or clean up the code.
	I was even thinking about making a video tutorial series on
	YouTube being inpired by Bluefever's VICE.
	
	I appriciate any feedbacks at freesoft.for.people@gmail.com
		
