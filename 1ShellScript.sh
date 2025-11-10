create()
{
echo "*************************Create Database***************************"
db=student
touch $db
echo "Database Created Successfully";
}

insert()
{
db=student
echo "*************************Insert Records****************************"

echo "How many Records do you want to insert?"
read no

while [ $no -gt 0 ]
do

echo "Enter the name of the student"
read name
echo "Enter the Department of the student"
read dept
echo "Enter the Address of the student"
read addr
echo "Enter the contact of the student"
read contact

record="||$name ||$dept ||$addr ||$contact||"
echo $record >> $db

echo "Insertion successful";
no=$(($no-1))
echo "**********************************************************************"
done
}

display()
{
db=student
echo "*************************Display Records**************************"
cat $db
echo "**********************************************************************"
}

search()
{
db=student
echo "*************************Search Records**************************"
echo "Enter the name of the student to search record";
read name

grep -i "$name" "$db"

if [ $? -eq 0 ]
then
echo "Records found"
else
echo "Record is not found"
fi
echo "**********************************************************************"

}

delete()
{
db=student
echo "*************************Display Records**************************"
echo "Enter the name of the student to delete the record"
read name

if grep "$name" "$db"
then 
grep -v "$name" "$db" > temp
mv temp $db

echo "Record deleted successfully"
else
echo "Record is not exist";
fi
echo "**********************************************************************"

}

modify()
{
db=student
echo "*************************Modify Records**************************"
echo "Enter the name of the student to modify"
read name

if grep "$name" "$db"
then 
sed -i "/$name/d" $db
echo "Enter Name, Department, Address, contact"
read name dept addr contact

record="||$name ||$dept ||$addr ||$contact||"
echo $record >> $db

echo "Record modified success"
else
echo "Record doesn't exist"
fi
echo "**********************************************************************"

}


echo "***********************Student Address BOOK*****************************"
menu="1)Create Database
2)Insert Records
3)Display Records
4)Search Records
5)Delete Records
6)Modify Records
7)exit"


while [ true ]
do
echo "$menu"
echo "Enter your choice"
read ch

case $ch in 

1)create ;;
2)insert ;;
3)display ;;
4)search ;;
5)delete ;;
6)modify ;;
7)exit ;;
*)  echo "Invalid choice please enter valid number from 1 to 7" ;;
esac
done



