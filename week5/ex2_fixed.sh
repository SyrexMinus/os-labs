touch file

if [ -z "$(grep -Eo '^[0-9]+$' file | tail -1)" ]
then
  echo "\n0" >> file
fi

while [ 1 = 1 ]
do
  if ln file file.lock
  then
    next_num=$(($(grep -Eo '^[0-9]+$' file.lock | tail -1)+1))
    echo "$next_num" >> file.lock
    rm file.lock
  fi
done
