.PHONY: clean All

All:
	@echo "----------Building project:[ First - Release ]----------"
	@"$(MAKE)" -f  "First.mk"
clean:
	@echo "----------Cleaning project:[ First - Release ]----------"
	@"$(MAKE)" -f  "First.mk" clean
