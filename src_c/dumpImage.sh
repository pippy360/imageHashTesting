mkdir ../inputImages/$1
cp ../input/$1.jpg ../inputImages/$1
sudo python ../src/dumpImage.py $1
