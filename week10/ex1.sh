rm _ex1_1.txt
rm _ex1_2.txt
echo Makar > _ex1.txt
link _ex1.txt _ex1_1.txt
link _ex1.txt _ex1_2.txt
echo $(ls -i _ex1.txt) > ex1.txt
echo $(ls -i _ex1_1.txt) >> ex1.txt
echo $(ls -i _ex1_2.txt) >> ex1.txt
