mkdir ../inputImages/$1
cp ../input/$1.jpg ../inputImages/$1
sudo python ./dumpImage.py $1