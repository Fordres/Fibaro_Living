.PHONY: clean All

All:
	@echo "----------Building project:[ Fibaro_Living2 - Release ]----------"
	@"$(MAKE)" -f  "Fibaro_Living2.mk"
clean:
	@echo "----------Cleaning project:[ Fibaro_Living2 - Release ]----------"
	@"$(MAKE)" -f  "Fibaro_Living2.mk" clean
