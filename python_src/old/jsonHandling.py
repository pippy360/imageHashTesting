import json

def getTheJsonObjFromString(tempString):
	tempString = tempString.replace("'", "\\\"")
	jsonObj = json.loads(tempString)
	xCoords = jsonObj['xcoords']
	yCoords = jsonObj['ycoords']

	xCoords = json.loads(xCoords)
	yCoords = json.loads(yCoords)

	finCoords = []
	for i in range(len(xCoords)):
		c = (int(xCoords[i]), int(yCoords[i]))
		finCoords.append( c )

	jsonObj['coords'] = finCoords
	return jsonObj


def getTheJsonObjs(thehash, redisVar):
	theList = redisVar.lrange(thehash, 0, -1)
	if theList == []:
		return None

	ret = []
	for theString in theList:
		ret.append(getTheJsonObjFromString(theString))
	return ret

def getTheJsonString(imgName, hash1, area, tri):
	xCoords = []
	yCoords = []
	for coord in tri:
		xCoords.append( str(int(coord[0])) )
		yCoords.append( str(int(coord[1])) )

	tempString =  '{ "imageName" : "'+imgName+\
				'", "hash":"' + str(hash1) + \
				'", "area":'+ str(area) + \
				', "xcoords":"'+json.dumps(xCoords).replace('"', "'")+\
				'", "ycoords":"'+json.dumps(yCoords).replace('"', "'")+\
				'" }'

	return tempString 