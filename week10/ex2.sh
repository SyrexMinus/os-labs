rm -rf week01
mkdir week01
echo Makar > week01/file.txt
rm -rf week10
mkdir week10
link week01/file.txt week10/_ex2.txt
inode=$(ls -i week01/file.txt)
inode=${inode%% *}
echo $(find week10 -inum $inode) > ex2.txt
echo $(find week10 -inum $inode -exec rm {} \;) >> ex2.txt
