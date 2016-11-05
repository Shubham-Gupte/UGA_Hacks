import json
import urllib
import pyowm
# Make sure pyowm is installed "sudo pip install pyowm"
open_Weather_API_Key = "cca945c3436ba1c78f0698dc21f0a3f7"
googleGeoCoding_API = "AIzaSyDgofZudgOugUxuNK1oexgyVaeCOZ_H1tk"
f = open('base.txt')
lines = f.readlines()
address = lines[0]
address = address.replace(" ", "+")
coordinateTranslator = "https://maps.googleapis.com/maps/api/geocode/json?address=1600+Amphitheatre+Parkway,+Mountain+View,+CA&key=YOUR_API_KEY"
coordinateTranslator = coordinateTranslator.replace("1600+Amphitheatre+Parkway,+Mountain+View,+CA", address)
coordinateTranslator = coordinateTranslator.replace("YOUR_API_KEY", googleGeoCoding_API)
response = urllib.urlopen(coordinateTranslator)
coordinateData = json.loads(response.read())

lat = coordinateData['results'][0]['geometry']['location']['lat']
lng = coordinateData['results'][0]['geometry']['location']['lng']
lines[1] = str(lat) + '\n'
lines[2] = str(lng) + '\n'


### Weather and file editing

weather_API_URL = "api.openweathermap.org/data/2.5/weather?lat=35&lon=139&APPID=1111111111"
weather_API_URL = weather_API_URL.replace("35", str(lat))
weather_API_URL = weather_API_URL.replace("139", str(lng))
weather_API_URL = weather_API_URL.replace("1111111111", open_Weather_API_Key)

owm = pyowm.OWM(open_Weather_API_Key)
observation = owm.weather_at_coords(float(lat), float(lng))
w = observation.get_weather()
temp = w.get_temperature('fahrenheit')
temp = temp["temp"]
status = w.get_status()

address = lines[6]
address = address.replace(" ", "+")
coordinateTranslator = "https://maps.googleapis.com/maps/api/geocode/json?address=1600+Amphitheatre+Parkway,+Mountain+View,+CA&key=YOUR_API_KEY"
coordinateTranslator = coordinateTranslator.replace("1600+Amphitheatre+Parkway,+Mountain+View,+CA", address)
coordinateTranslator = coordinateTranslator.replace("YOUR_API_KEY", googleGeoCoding_API)
response = urllib.urlopen(coordinateTranslator)
coordinateData = json.loads(response.read())

dlat = coordinateData['results'][0]['geometry']['location']['lat']
dlng = coordinateData['results'][0]['geometry']['location']['lng']
lines[7] = str(dlat) + '\n'
lines[8] = str(dlng) + '\n'


lines[3] = str(temp) + '\n'
lines[4] = str(status) + '\n'


trafficData = "https://maps.googleapis.com/maps/api/distancematrix/json?units=imperial&origins=Washington,DC&destinations=New+York+City,NY&key=K1E2Y3"
trafficData = trafficData.replace("K1E2Y3", googleGeoCoding_API)
origin = lines[0]
origin = origin.replace(" ", "+")
dest = lines[6]
dest = dest.replace(" ", "+")
trafficData = trafficData.replace("Washington,DC", origin)
trafficData = trafficData.replace("New+York+City,NY", dest)

response = urllib.urlopen(trafficData)
trafficReceiver = json.loads(response.read())


print trafficReceiver["rows"][0]["elements"][0]["duration"]["value"]
totalTime = int(trafficReceiver["rows"][0]["elements"][0]["duration"]["value"]) + int(timeToGetReady)


with open('base.txt', 'w') as file:
    file.writelines(lines)
