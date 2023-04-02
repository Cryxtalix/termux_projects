# termux_projects
Some small applications on Termux and Termux:API platform for use in Singapore.
Uses OpenWeatherMap and ArriveLah APIs to get local weather and public transport information.

* https://openweathermap.org/api
* https://github.com/cheeaun/arrivelah

To setup:
1) Install [Termux](https://f-droid.org/en/packages/com.termux/) and [Termux:API](https://f-droid.org/en/packages/com.termux.api/) apps from fdroid. 
2) Open Termux, enter `pkg update && pkg upgrade`.
3) Press Y to install packages.
4) `apt install termux-api`, press Y if prompted.
5) `apt install clang`, press Y if prompted.
6) `pkg install git`.
7) `git clone https://github.com/Cryxtalix/termux_projects`
8) `touch .env`
9) `nano .env`, and enter `OWM_APIKEY=` followed by your OWM API key without any spaces. See link above to get a free OWM key.
10) `cd termux_projects && make all`
11) To run, `./weather.out` or `./bus.out`. 
12) Alternatively, move both binary files into .shortcuts folder. You can now add a termux widget to your homescreen and execute both apps without launching termux.
