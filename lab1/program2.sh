# Name: Andrew Knaus
# Date: Thursday 2:15 09-24-2020
# Title: Lab1 – task # Description: This program computes ...
# the area of a circle.
#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "andrewknaus" ]
then
        echo "Now you can proceed!"
else
        echo "Check who logged in!" 
        exit 1
fi

response="Yes"
while [ $response != "No" ]
do
        echo "Enter the radius of a circle : "
        read radius
        area=$(echo "scale=2;3.14 * ($radius * $radius)" | bc)
        echo "The area of the circle is $area"

        echo "Would you like to repeat for another circle [Yes/No]?"
        read response

done