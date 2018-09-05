# Chengine
Beginner's UCI chess engine for linux

	Features:

		- 0x88 board representation;
		- move generation via calculations
		- copy-make make move approach
		- material and piece placement evaluation;
		- nega max brute force search algorithm;
		- UCI protocol with fixed depth search only;
		
	After for about a three years of researching how
	does particularly a chess engine works and numerous
	unsuccessful attempts to write my own I've finally
	managed to complete one.
	
	Chengine is very slow and weak engine due to the lack of
	piece lists, king square and material tracking. The brute
	force nega max search doesn't cut any garbage branches, so
	it takes ages to get the best move even at depth 6, but
	nevertheless it is already a complete engine to play chess.
	
	I appriciate any feedbacks at freesoft.for.people@gmail.com

# Intents and purposes

	Chengine is intended to be a source of inspiration for the
	beginner and hobby programmers dreaming to write their own
	bug free chess program. The very first chess engine I've
	copy-pasted renaming the variables to get the idea how it
	works was Bluefever's VICE which is absolutely great piece
	of software, but still quite complicated, so I tried to write
	something even more simple.
	
# Next steps
	
	I've finally realized the path to follow in chess engine
	development. The idea is very simple - try to do the same
	thing you've done before, but in less code and also try to
	get the best performance out of a given algorithms.

# Compile

	- compile it with GCC;
	- cd into src folder
	- type "make" and that's it
	
	the output file would be "chengine"
	with no extension
	
# GUI

	Tested with Arena for linux
	
# Credits

	I want to thank the great chess engine development community
	for providing reasonable resources, espacially to:
		
		-   Bluefever Software's VICE video tutorial series
			https://www.youtube.com/playlist?list=PLZ1QII7yudbc-Ky058TEaOstZHVbT-2hg
		
		-   Bruce Moreland for his 0x88 board representaion explanations
			https://web.archive.org/web/20071026130204/http://www.seanet.com/~brucemo/topics/0x88.htm
			
		-   Chess Programming Wiki
			https://www.chessprogramming.org/Main_Page 
		
