# Tester

How to run

cd into minishell_tester

./tester
./tester syntax
./tester os_specific

## Test case only

Test 1: ❌ echo hello world
Test 2: ❌ echo "hello world"
Test 3: ❌ echo 'hello world'
Test 4: ❌ echo hello'world'
Test 5: ❌ echo hello""world
Test 6: ❌ echo ''
Test 7: ❌ echo "$PWD"
Test 8: ❌ echo '$PWD'
Test 9: ❌ echo "aspas ->'"
Test 10: ❌ echo "aspas -> ' "
Test 11: ❌ echo 'aspas ->"'
Test 12: ❌ echo 'aspas -> " '
Test 13: ❌ echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<"
Test 14: ❌ echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<'
Test 15: ❌ echo "exit_code ->$? user ->$USER home -> $HOME"
Test 16: ❌ echo 'exit_code ->$? user ->$USER home -> $HOME'
Test 17: ❌ echo "$"
Test 18: ❌ echo '$'
Test 19: ❌ echo $

Test 20: ❌ echo $?
Gets the exit status of last ocmmand

Test 21: ❌ echo $?HELLO
Gets the exit status of last command+HELLO

Test 22: ❌ pwd
Test 23: ❌ pwd oi
Test 24: ❌ export hello
Test 25: ❌ export HELLO=123
Test 26: ❌ export A-
Test 27: ❌ export HELLO=123 A
Test 28: ❌ export HELLO="123 A-"
Test 29: ❌ export hello world
Test 30: ❌ export HELLO-=123
Test 31: ❌ export =
Test 32: ❌ export 123
Test 33: ❌ unset
Test 34: ❌ unset HELLO
Test 35: ❌ unset HELLO1 HELLO2
Test 36: ❌ unset HOME
Test 37: ❌ unset PATH
Test 38: ❌ unset SHELL
Test 39: ❌ cd $PWD
Test 40: ❌ cd $PWD hi
Test 41: ❌ cd 123123
Test 42: ❌ exit 123
Test 43: ❌ exit 298
Test 44: ❌ exit +100
Test 45: ❌ exit "+100"
Test 46: ❌ exit +"100"
Test 47: ❌ exit -100
Test 48: ❌ exit "-100"
Test 49: ❌ exit -"100"
Test 50: ❌ exit hello
Test 51: ❌ exit 42 world
Test 52: ❌  
Test 53: ❌ env | sort | grep -v SHLVL | grep -v ^_
Test 54: ❌ cat ./test_files/infile_big | grep oi
Test 55: ❌ cat minishell.h | grep ");"$
Test 56: ❌ export GHOST=123 | env | grep GHOST
Test 57: ❌ grep hi <./test_files/infile
Test 58: ❌ grep hi "<infile" <         ./test_files/infile
Test 59: ❌ echo hi < ./test_files/infile bye bye
Test 60: ❌ grep hi <./test_files/infile_big <./test_files/infile
Test 61: ❌ echo <"./test_files/infile" "bonjour       42"
Test 62: ❌ cat <"./test_files/file name with spaces"
Test 63: ❌ cat <./test_files/infile_big ./test_files/infile
Test 64: ❌ cat <"1""2""3""4""5"
Test 65: ❌ echo <"./test_files/infile" <missing <"./test_files/infile"
Test 66: ❌ echo <missing <"./test_files/infile" <missing
Test 67: ❌ cat <"./test_files/infile"
Test 68: ❌ echo <"./test_files/infile_big" | cat <"./test_files/infile"
Test 69: ❌ echo <"./test_files/infile_big" | cat "./test_files/infile"
Test 70: ❌ echo <"./test_files/infile_big" | echo <"./test_files/infile"
Test 71: ❌ echo hi | cat <"./test_files/infile"
Test 72: ❌ echo hi | cat "./test_files/infile"
Test 73: ❌ cat <"./test_files/infile" | echo hi
Test 74: ❌ cat <"./test_files/infile" | grep hello
Test 75: ❌ cat <"./test_files/infile_big" | echo hi
Test 76: ❌ cat <missing
Test 77: ❌ cat <missing | cat
Test 78: ❌ cat <missing | echo oi
Test 79: ❌ cat <missing | cat <"./test_files/infile"
Test 80: ❌ echo <123 <456 hi | echo 42
Test 81: ❌ ls >./outfiles/outfile01
Test 82: ❌ ls >         ./outfiles/outfile01
Test 83: ❌ echo hi >         ./outfiles/outfile01 bye
Test 84: ❌ ls >./outfiles/outfile01 >./outfiles/outfile02
Test 85: ❌ ls >./outfiles/outfile01 >./test_files/invalid_permission
Test 86: ❌ ls >"./outfiles/outfile with spaces"
Test 87: ❌ ls >"./outfiles/outfile""1""2""3""4""5"
Test 88: ❌ ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02"
Test 89: ❌ ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission
Test 90: ❌ cat <"./test_files/infile" >"./outfiles/outfile01"
Test 91: ❌ echo hi >./outfiles/outfile01 | echo bye
Test 92: ❌ echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye
Test 93: ❌ echo hi | echo >./outfiles/outfile01 bye
Test 94: ❌ echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02
Test 95: ❌ echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02
Test 96: ❌ echo hi >./test_files/invalid_permission | echo bye
Test 97: ❌ echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye
Test 98: ❌ echo hi | echo bye >./test_files/invalid_permission
Test 99: ❌ echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission
Test 100: ❌ echo hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01
Test 101: ❌ cat <"./test_files/infile" >./test_files/invalid_permission
Test 102: ❌ cat >./test_files/invalid_permission <"./test_files/infile"
Test 103: ❌ cat <missing >./outfiles/outfile01
Test 104: ❌ cat >./outfiles/outfile01 <missing
Test 105: ❌ cat <missing >./test_files/invalid_permission
Test 106: ❌ cat >./test_files/invalid_permission <missing
Test 107: ❌ cat >./outfiles/outfile01 <missing >./test_files/invalid_permission
Test 108: ❌ ls >>./outfiles/outfile01
Test 109: ❌ ls >>      ./outfiles/outfile01
Test 110: ❌ ls >>./outfiles/outfile01 >./outfiles/outfile01
Test 111: ❌ ls >./outfiles/outfile01 >>./outfiles/outfile01
Test 112: ❌ ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02
Test 113: ❌ ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02
Test 114: ❌ ls >>./outfiles/outfile01 >>./outfiles/outfile02
Test 115: ❌ ls >>./test_files/invalid_permission
Test 116: ❌ ls >>./test_files/invalid_permission >>./outfiles/outfile01
Test 117: ❌ ls >>./outfiles/outfile01 >>./test_files/invalid_permission
Test 118: ❌ ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02
Test 119: ❌ ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02
Test 120: ❌ ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing
Test 121: ❌ echo hi >>./outfiles/outfile01 | echo bye
Test 122: ❌ echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye
Test 123: ❌ echo hi | echo >>./outfiles/outfile01 bye
Test 124: ❌ echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02
Test 125: ❌ echo hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02
Test 126: ❌ echo hi >>./test_files/invalid_permission | echo bye
Test 127: ❌ echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye
Test 128: ❌ echo hi | echo bye >>./test_files/invalid_permission
Test 129: ❌ echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission
Test 130: ❌ cat <minishell.h>./outfiles/outfile
Test 131: ❌ cat <minishell.h|ls
Test 132: ❌  
Test 133: ❌ $PWD
Test 134: ❌ $EMPTY
Test 135: ❌ $EMPTY echo hi
Test 136: ❌ ./test_files/invalid_permission
Test 137: ❌ ./missing.out
Test 138: ❌ missing.out
Test 139: ❌ "aaa"
Test 140: ❌ test_files
Test 141: ❌ ./test_files
Test 142: ❌ /test_files
Test 143: ❌ minishell.h
Test 144: ❌ $
Test 145: ❌ $?
Test 146: ❌ README.md
