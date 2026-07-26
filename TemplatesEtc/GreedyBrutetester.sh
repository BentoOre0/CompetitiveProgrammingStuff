# Compile with chmod +x tester.sh
# And then run ./tester.sh on terminal

# The ! Operator

# Purpose: In Bash, the ! operator negates the exit status of the command that follows it.

# Behavior:

# If the command returns 0 (indicating success, or in this case, that the files are identical), then ! converts that into a failure (non-zero exit status). This means the condition becomes false, and the block inside then is skipped.

# If the command returns a nonzero value (indicating failure, or that the files differ), then ! converts that into success (an exit status of 0). This means the condition becomes true, and the code inside the then block is executed.


g++ greedy.cpp -o greedy
g++ bruteforcer.cpp -o brute

for i in {1..100}
do
    echo "testing $i"
    pypy3 testmaker.py <<< $i > test.in

    ./greedy < test.in > greedy.out
   
    ./brute < test.in > brute.out

    if ! diff -q greedy.out brute.out; then
        echo "files differ"
        break
    fi
done

