sudo apt-get install git
git clone git://github.com/pippy360/imageHashTesting
sudo apt-get install cmake
rm ./CMakeCache.txt
sudo apt-get install g++
sudo apt-get install redis-server
sudo apt-get install libboost-all-dev
#remove annoying opencv error
sudo ln /dev/null /dev/raw1394

#cmake now works

#now lets do the python server
cd ~
git clone git://github.com/pippy360/pippy360.github.io
#copy the app file to bin folder
sudo apt-get install python-pip
sudo pip install flask
sudo pip install flask_cors
sudo su
export FLASK_APP=app.py
python -m flask run
