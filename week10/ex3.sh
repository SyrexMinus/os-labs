echo Makar > _ex3.txt
echo $(chmod a-x _ex3.txt) > ex3.txt
echo $(chmod uo+rwx _ex3.txt) >> ex3.txt
echo $(chmod g=u _ex3.txt) >> ex3.txt
ans='660, 775 and 777 are modes, numerical representations of access permissions to the file system objects. In mode the three rightmost digits define permissions for the file user, the group, and others. 660 means that owner and group can read and edit; the rest are not allowed to take any action. 775 means that the user and the group can read, edit and run for execution, but others can only read and run for execution. 777 means that each user can read, edit and run for execution'
echo ans >> ex3.txt
