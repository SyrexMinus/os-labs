sudo chmod 777 lofsdisk
cd lofsdisk

echo Makar > ./file1
echo Shevchenko > ./file2

gcc ../ex2.c -o ./ex2.out

mkdir bin
mkdir lib
mkdir lib64
mkdir ./lib/x86_64-linux-gnu
cp -v /bin/bash ./bin
cp -v /bin/cat ./bin
cp -v /bin/echo ./bin
cp -v /bin/ls ./bin
list="$(ldd /bin/bash | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp -v "$i" ".${i}"; done
list="$(ldd /bin/cat | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp -v "$i" ".${i}"; done
list="$(ldd /bin/echo | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp -v "$i" ".${i}"; done
list="$(ldd /bin/ls | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp -v "$i" ".${i}"; done

sudo chroot . ./ex2.out > ../ex2.txt
./ex2.out >> ../ex2.txt
