# Mute all `make` specific output. Comment this out to get some debug information.
.SILENT:

# .DEFAULT: If the command does not exist in this makefile
.DEFAULT: help

help:
	@echo "Usage:"
	@echo "     make [command]"
	@echo
	@echo "Available commands:"
	@grep '^[^#[:space:]].*:' Makefile | grep -v '^default' | grep -v '^\.' | grep -v '=' | grep -v '^_' | sed 's/://' | xargs -n 1 echo ' -'

########################################################################################################################
compile:
	cd $$pwd
	cmake --build build
	# notify-send "Tech demo compiled"
configure:
	cd $$pwd
	# cmake --configure build
	notify-send "Tech demo configured"
install:
	cd $$pwd
	cmake --install build
	# notify-send "Tech demo installed"
rebuild:
	cd $$pwd
	# cmake --configure build
	cmake --build build
	cmake --install build
run:
	cd $$pwd
	cmake --build build
	cmake --install build
	# notify-send "Tech demo installed"
	/home/calisto/Games/tech2/bin/game
test:
	cd /home/calisto/.local/usr/src/tech
	make compile && cd ./build && ctest -VV
test-game:
	cd /home/calisto/.local/usr/src/tech
	make compile && ./build/tests/game/GameUnitTests 
test-engine:
	cd /home/calisto/.local/usr/src/tech
	make compile && ./build/tests/engine/EngineUnitTests 
