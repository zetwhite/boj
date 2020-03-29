git pull
git add -A
while true
do
git status
echo -n "Do you want to continue (y/n)?";
read answer
	case $answer in
	[yY]* ) echo -n "enter commit message : "
		read msg 
		git commit -m "${msg}"
		git push origin master
		break;;
	[nN]* ) git reset 
		echo "cancelled..."
		exit;;
	*) echo "please enter y or n";
	esac
done
