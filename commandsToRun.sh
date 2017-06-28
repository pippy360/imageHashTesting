sudo apt-get install git cmake g++ redis-server libboost-all-dev -y
sudo apt-get install opencv #replace with actual command

git clone git://github.com/pippy360/imageHashTesting
rm ./CMakeCache.txt
#cmake now works

#remove annoying opencv error
sudo ln /dev/null /dev/raw1394

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
