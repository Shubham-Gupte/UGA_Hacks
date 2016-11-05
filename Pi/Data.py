import json
import urllib

open_Weather_API_Key = "cca945c3436ba1c78f0698dc21f0a3f7"
googleGeoCoding_API = "AIzaSyDgofZudgOugUxuNK1oexgyVaeCOZ_H1tk"
f = open('base.txt')
lines = f.readlines()
address = lines[0]
address = address.replace(" ", "+")
print address
coordinateTranslator = "https://maps.googleapis.com/maps/api/geocode/json?address=1600+Amphitheatre+Parkway,+Mountain+View,+CA&key=YOUR_API_KEY"
coordinateTranslator = coordinateTranslator.replace("1600+Amphitheatre+Parkway,+Mountain+View,+CA", address)
coordinateTranslator = coordinateTranslator.replace("YOUR_API_KEY", googleGeoCoding_API)
response = urllib.urlopen(coordinateTranslator)
coordinateData = json.loads(response.read())

lat = coordinateData['results'][0]['geometry']['location']['lat']
lng = coordinateData['results'][0]['geometry']['location']['lng']

print lng
