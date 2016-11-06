import json
import urllib
import pyowm
import time
import serial
import math
import requests
ser = serial.Serial('/dev/ttyACM0', 9600)
ser.close()
ser.open()
    # Make sure pyowm is installed "sudo pip install pyowm"

while True:
    open_Weather_API_Key = "cca945c3436ba1c78f0698dc21f0a3f7"
    googleGeoCoding_API = "AIzaSyDgofZudgOugUxuNK1oexgyVaeCOZ_H1tk"
    mainDictionary = {}
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

    ###Coordinates of initial position aka person's home
    lines[1] = str(lat) + '\n'
    mainDictionary["lat"] = str(lat)
    lines[2] = str(lng) + '\n'
    mainDictionary["lng"] = str(lng)
    mainDictionary["temperature"] = float(lines[3])
    mainDictionary["weather"] = lines[4].strip()
    mainDictionary["prepTime"] = int(lines[5])

    ### Weather and file editing

    weather_API_URL = "api.openweathermap.org/data/2.5/weather?lat=35&lon=139&APPID=1111111111"
    weather_API_URL = weather_API_URL.replace("35", str(lat))
    weather_API_URL = weather_API_URL.replace("139", str(lng))
    weather_API_URL = weather_API_URL.replace("1111111111", open_Weather_API_Key)

    owm = pyowm.OWM(open_Weather_API_Key)
    observation = owm.weather_at_coords(float(lat), float(lng))
    w = observation.get_weather()
    print w
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

    ### Coordinates of destination
    dlat = coordinateData['results'][0]['geometry']['location']['lat']
    dlng = coordinateData['results'][0]['geometry']['location']['lng']
    lines[7] = str(dlat) + '\n'
    mainDictionary["dlat"] = str(dlat)
    lines[8] = str(dlng) + '\n'
    mainDictionary["dlng"] = str(dlng)


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

    mainDictionary["idealTravelTime"] = int(lines[9])
    mainDictionary["normalWakeUpTimeHours"] = int(lines[10])
    mainDictionary["normalWakeUpTimeMinutes"] = int(lines[11])
    mainDictionary["timeToArriveHours"] = int(lines[12])
    mainDictionary["timeToArriveMinutes"] = int(lines[13])

    # print trafficReceiver["rows"][0]["elements"][0]["duration"]["value"] #traffic time
    trafficTime = int(trafficReceiver["rows"][0]["elements"][0]["duration"]["value"]) #traffic time
    lines[14] = str(trafficTime)
    mainDictionary['trafficTime'] = int(lines[14])

    #arrival time from 0:00 in seconds
    arrivalTime = int(lines[12])*60*60 + int(lines[13])*60
    timeToWakeUp = arrivalTime - int(lines[14]) - int(lines[5])*60
    timeToWakeUpHours = math.trunc(timeToWakeUp/3600)
    timeToWakeUpMinutes = int(math.floor(((timeToWakeUp/3600.0)-timeToWakeUpHours)*60.0))
    print str(math.trunc(mainDictionary['temperature']))
    print str(timeToWakeUpHours)
    print str(timeToWakeUpMinutes)
    ser.write('a')
    ser.write(",")
    ser.write(str(math.trunc(mainDictionary["temperature"])))
    ser.write(",")
    ser.write(str(timeToWakeUpHours))
    ser.write(",")
    ser.write(str(timeToWakeUpMinutes))
    ser.write(",")
    ser.write('a')
    ser.write("\n")

    print 'written'

    with open('base.txt', 'w') as file:
        file.writelines(lines)
    time.sleep(3)
