EXEC := go
DIROUT := out

.PHONY: all slicer transformer exec clean cleanSlicer cleanTransformer cleanExec

all: slicer transformer exec

slicer:
	@cd Slicer/src && $(MAKE)

transformer:
	@cd Transformer/src && $(MAKE)

exec:
	@echo "cat folha8.OUT.txt | ./Transformer/src/transformer | ./Slicer/src/slicer $(DIROUT)" > $(EXEC)
	@chmod +x $(EXEC)


clean: cleanSlicer cleanTransformer cleanExec

cleanSlicer:
	@cd Slicer/src && $(MAKE) clean

cleanTransformer:
	@cd Transformer/src && $(MAKE) clean

cleanExec:
	@rm -rf $(EXEC) $(DIROUT)

