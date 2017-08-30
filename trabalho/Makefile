# Makefile básico, sugestões são bem-vindas...
# Carlos Maziero @UFPR, nov 2015

MAIN=main

main: $(MAIN).tex
	@pdflatex $(MAIN)
	@bibtex   $(MAIN)
	@pdflatex $(MAIN)
	@pdflatex $(MAIN)
	@mv $(MAIN).pdf $(MAIN)_$(USER).pdf # a pedido da coordenação

bib:
	@bibtex $(MAIN)

# dessa forma somente os arquivos removidos são listados na saída
clean:
	@find . -xdev -iname \*~        -print -delete
	@find . -xdev -iname \*.aux     -print -delete
	@find . -xdev -name texput.log  -print -delete
	@find . -xdev -name $(MAIN).log -print -delete
	@find . -xdev -name $(MAIN).lot -print -delete
	@find . -xdev -name $(MAIN).lof -print -delete
	@find . -xdev -name $(MAIN).toc -print -delete
	@find . -xdev -name $(MAIN).bbl -print -delete
	@find . -xdev -name $(MAIN).blg -print -delete

purge: clean
	@rm -f $(MAIN)_$(USER).pdf

