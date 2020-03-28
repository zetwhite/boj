number=$1
type=$2
file="boj${1}.${2}"
echo $number
echo $file
python submit.py $number $file
