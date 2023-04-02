CC=gcc

all:
	@echo "Making all..."
	@make -s weather
	@make -s bus

weather:
	@echo "Making weather..."
	@$(CC) -O -o weather.out weather.c ./lib/get_key.c ./lib/curl_url.c ./lib/termux_output.c -lcurl

bus:
	@echo "Making bus..."
	@$(CC) -O -o bus.out bus.c ./lib/termux_output.c ./lib/curl_url.c -lcurl

clean:
	@echo "Deleting output files..."
	@rm -f weather.out
	@rm -f bus.out