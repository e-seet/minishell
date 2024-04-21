# Test case and expected

Test   1: ❌ echo hello world

Test   2: ❌ echo "hello world"
mini output = ()
bash output = (hello world)
mini exit code =
bash exit code = 0
Test   3: ❌ echo 'hello world'
mini output = ()
bash output = (hello world)
mini exit code =
bash exit code = 0
Test   4: ❌ echo hello'world'
mini output = ()
bash output = (helloworld)
mini exit code =
bash exit code = 0
Test   5: ❌ echo hello""world
mini output = ()
bash output = (helloworld)
mini exit code =
bash exit code = 0
Test   6: ❌ echo ''
mini exit code =
bash exit code = 0
Test   7: ❌ echo "$PWD"
mini output = ()
bash output = (/Users/eddieseet/MDesktop/Curr/minishell/minishell_tester)
mini exit code =
bash exit code = 0
Test   8: ❌ echo '$PWD'
mini output = ()
bash output = ($PWD)
mini exit code =
bash exit code = 0
Test   9: ❌ echo "aspas ->'"
mini output = ()
bash output = (aspas ->')
mini exit code =
bash exit code = 0
Test  10: ❌ echo "aspas -> ' "
mini output = ()
bash output = (aspas -> ' )
mini exit code =
bash exit code = 0
Test  11: ❌ echo 'aspas ->"'
mini output = ()
bash output = (aspas ->")
mini exit code =
bash exit code = 0
Test  12: ❌ echo 'aspas -> " '
mini output = ()
bash output = (aspas -> " )
mini exit code =
bash exit code = 0
Test  13: ❌ echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<"
mini output = ()
bash output = (> >> < README.md bash.supp bash_outfiles bonus bonus_bonus builtins extras local.supp loop.out manual_tests mini_outfiles os_specific outfiles pipes redirects syntax test_files tester wildcards ? [ ] | ; [ ] || && ( ) & # $ <<)
mini exit code =
bash exit code = 0
Test  14: ❌ echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<'
mini output = ()
bash output = (> >> < README.md bash.supp bash_outfiles bonus bonus_bonus builtins extras local.supp loop.out manual_tests mini_outfiles os_specific outfiles pipes redirects syntax test_files tester wildcards ? [ ] | ; [ ] || && ( ) & # $ <<)
mini exit code =
bash exit code = 0
Test  15: ❌ echo "exit_code ->$? user ->$USER home -> $HOME"
mini output = ()
bash output = (exit_code ->0 user ->eddieseet home -> /Users/eddieseet)
mini exit code =
bash exit code = 0
Test  16: ❌ echo 'exit_code ->$? user ->$USER home -> $HOME'
mini output = ()
bash output = (exit_code ->$? user ->$USER home -> $HOME)
mini exit code =
bash exit code = 0
Test  17: ❌ echo "$"
mini output = ()
bash output = ($)
mini exit code =
bash exit code = 0
Test  18: ❌ echo '$'
mini output = ()
bash output = ($)
mini exit code =
bash exit code = 0
Test  19: ❌ echo $
mini output = ()
bash output = ($)
mini exit code =
bash exit code = 0
Test  20: ❌ echo $?
mini output = ()
bash output = (0)
mini exit code =
bash exit code = 0
Test  21: ❌ echo $?HELLO
mini output = ()
bash output = (0HELLO)
mini exit code =
bash exit code = 0
Test  22: ❌ pwd
mini output = ()
bash output = (/Users/eddieseet/MDesktop/Curr/minishell/minishell_tester)
mini exit code =
bash exit code = 0
Test  23: ❌ pwd oi
mini output = ()
bash output = (/Users/eddieseet/MDesktop/Curr/minishell/minishell_tester)
mini exit code =
bash exit code = 0
Test  24: ❌ export hello
mini exit code =
bash exit code = 0
Test  25: ❌ export HELLO=123
mini exit code =
bash exit code = 0
Test  26: ❌ export A-
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( not a valid identifier)
Test  27: ❌ export HELLO=123 A
mini exit code =
bash exit code = 0
Test  28: ❌ export HELLO="123 A-"
mini exit code =
bash exit code = 0
Test  29: ❌ export hello world
mini exit code =
bash exit code = 0
Test  30: ❌ export HELLO-=123
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( not a valid identifier)
Test  31: ❌ export =
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( not a valid identifier)
Test  32: ❌ export 123
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( not a valid identifier)
Test  33: ❌ unset
mini exit code =
bash exit code = 0
Test  34: ❌ unset HELLO
mini exit code =
bash exit code = 0
Test  35: ❌ unset HELLO1 HELLO2
mini exit code =
bash exit code = 0
Test  36: ❌ unset HOME
mini exit code =
bash exit code = 0
Test  37: ❌ unset PATH
mini exit code =
bash exit code = 0
Test  38: ❌ unset SHELL
mini exit code =
bash exit code = 0
Test  39: ❌ cd $PWD
mini exit code =
bash exit code = 0
Test  40: ❌ cd $PWD hi
mini exit code =
bash exit code = 0
Test  41: ❌ cd 123123
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test  42: ❌ exit 123
mini exit code =
bash exit code = 123
Test  43: ❌ exit 298
mini exit code =
bash exit code = 42
Test  44: ❌ exit +100
mini exit code =
bash exit code = 100
Test  45: ❌ exit "+100"
mini exit code =
bash exit code = 100
Test  46: ❌ exit +"100"
mini exit code =
bash exit code = 100
Test  47: ❌ exit -100
mini exit code =
bash exit code = 156
Test  48: ❌ exit "-100"
mini exit code =
bash exit code = 156
Test  49: ❌ exit -"100"
mini exit code =
bash exit code = 156
Test  50: ❌ exit hello
mini exit code =
bash exit code = 255
mini error = ()
bash error = ( numeric argument required)
Test  51: ❌ exit 42 world
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( too many arguments)
Test  52: ❌  
mini exit code =
bash exit code = 0
———————————— pipes
Test  53: ❌ env | sort | grep -v SHLVL | grep -v ^_
mini output = ()
bash output = (COLORTERM=truecolor COMMAND_MODE=unix2003 DISPLAY=/private/tmp/com.apple.launchd.qva57YjSrv/org.xquartz:0 GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh HOME=/Users/eddieseet LANG=en_US.UTF-8 LOGNAME=eddieseet LaunchInstanceID=48049B82-ADA8-4161-ABEE-3E6BCFFD17B8 MallocNanoZone=0 ORIGINAL_XDG_CURRENT_DESKTOP=undefined PATH=/Users/eddieseet/.amplify/bin:/Applications/Xcode.app/Contents/Developer:/Users/eddieseet/.amplify/bin:/usr/local/bin:/opt/homebrew/bin:/opt/homebrew/bin:/opt/homebrew/bin:/usr/local/homebrew/bin:/usr/local/opt/llvm/bin:/usr/local/opt/llvm/bin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applications/VMware Fusion.app/Contents/Public:/usr/local/go/bin:/opt/X11/bin:/Library/Apple/usr/bin:/Users/eddieseet/.amplify/bin:/Applications/Xcode.app/Contents/Developer:/opt/homebrew/bin:/usr/local/homebrew/bin:/usr/local/opt/llvm/bin:/Users/eddieseet/.venv/bin:/Users/eddieseet/.venv/bin PWD=/Users/eddieseet/MDesktop/Curr/minishell/minishell_tester SECURITYSESSIONID=186b4 SHELL=/bin/bash SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.u23bLGNmT5/Listeners TERM=xterm-256color TERM_PROGRAM=vscode TERM_PROGRAM_VERSION=1.88.0 TMPDIR=/var/folders/bh/g_rls6lj401fkpk11gl6_hf00000gn/T/ USER=eddieseet VSCODE_GIT_ASKPASS_EXTRA_ARGS= VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Plugin).app/Contents/MacOS/Code Helper (Plugin) VSCODE_GIT_IPC_HANDLE=/var/folders/bh/g_rls6lj401fkpk11gl6_hf00000gn/T/vscode-git-712e6909de.sock XPC_FLAGS=0x0 XPC_SERVICE_NAME=0)
mini exit code =
bash exit code = 0
Test  54: ❌ cat ./test_files/infile_big | grep oi
mini output = ()
bash output = (was going to happen next. First, she tried to look down and make out disappointment it was empty: she did not like to drop the jar for fear not going to do _that_ in a hurry. “No, I’ll look first,” she said, “and see whether it’s marked ‘_poison_’ or not”; for she had read bottle marked “poison,” it is almost certain to disagree with you, However, this bottle was _not_ marked “poison,” so Alice ventured to brightened up at the thought that she was now the right size for going waited for a few minutes to see if she was going to shrink any further: said Alice to herself, “in my going out altogether, like a candle. I After a while, finding that nothing more happened, she decided on going Rabbit came near her, she began, in a low, timid voice, “If you please, to repeat it, but her voice sounded hoarse and strange, and the words now about two feet high, and was going on shrinking rapidly: she soon dropped it hastily, just in time to avoid shrinking away altogether. “Not like cats!” cried the Mouse, in a shrill, passionate voice. “Would trembling voice, “Let us get to the shore, and then I’ll tell you my “What I was going to say,” said the Dodo in an offended tone, “was, “But who is to give the prizes?” quite a chorus of voices asked. “Why, _she_, of course,” said the Dodo, pointing to Alice with one The next thing was to eat the comfits: this caused some noise and the others all joined in chorus, “Yes, please do!” but the Mouse only doesn’t suit my throat!” and a Canary called out in a trembling voice doing out here? Run home this moment, and fetch me a pair of gloves and at once in the direction it pointed to, without trying to explain the “How queer it seems,” Alice said to herself, “to be going messages for gloves, and was just going to leave the room, when her eye fell upon a she heard a voice outside, and stopped to listen. “Mary Ann! Mary Ann!” said the voice. “Fetch me my gloves this moment!” Next came an angry voice—the Rabbit’s—“Pat! Pat! Where are you?” And then a voice she had never heard before, “Sure then I’m here! Digging rumbling of little cartwheels, and the sound of a good many voices all then the Rabbit’s voice along—“Catch him, you by the hedge!” then silence, and then another confusion of voices—“Hold up his head—Brandy Last came a little feeble, squeaking voice, (“That’s Bill,” thought “We must burn the house down!” said the Rabbit’s voice; and Alice addressed her in a languid, sleepy voice. came different!” Alice replied in a very melancholy voice. By the use of this ointment—one shilling the box— going to dive in among the leaves, which she found to be nothing but Pigeon, raising its voice to a shriek, “and just as I was thinking I going to be, from one minute to another! However, I’ve got back to my are; secondly, because they’re making such a noise inside, no one could noise going on within—a constant howling and sneezing, and every now “Oh, _please_ mind what you’re doing!” cried Alice, jumping up and down (In which the cook and the baby joined): ear and left foot, so as to prevent its undoing itself,) she carried it No, there were no tears. “If you’re going to turn into a pig, my dear,” eyes, “Of course, of course; just what I was going to remark myself.” quarrelled last March—just before _he_ went mad, you know—” (pointing hoarse, feeble voice: “I heard every word you fellows were saying.” The Dormouse had closed its eyes by this time, and was going off into a neither of the others took the least notice of her going, though she voice, “Why the fact is, you see, Miss, this here ought to have been a you see, Miss, we’re doing our best, afore she comes, to—” At this “And who are _these?_” said the Queen, pointing to the three gardeners “Get up!” said the Queen, in a shrill, loud voice, and the three turning to the rose-tree, she went on, “What _have_ you been doing “May it please your Majesty,” said Two, in a very humble tone, going “Come on, then!” roared the Queen, and Alice joined the procession, “It’s—it’s a very fine day!” said a timid voice at her side. She was “Get to your places!” shouted the Queen in a voice of thunder, and had got its neck nicely straightened out, and was going to give the going to begin again, it was very provoking to find that the hedgehog “How do you like the Queen?” said the Cat in a low voice. “Who _are_ you talking to?” said the King, going up to Alice, and Alice thought she might as well go back, and see how the game was going on, as she heard the Queen’s voice in the distance, screaming with a large crowd collected round it: there was a dispute going on between thing before, and he wasn’t going to begin at _his_ time of life. startled when she heard her voice close to her ear. “You’re thinking “The game’s going on rather better now,” she said, by way of keeping up But here, to Alice’s great surprise, the Duchess’s voice died away, “A fine day, your Majesty!” the Duchess began in a low, weak voice. about half no time! Take your choice!” The Duchess took her choice, and was gone in a moment. As they walked off together, Alice heard the King say in a low voice, sea. The master was an old Turtle—we used to call him Tortoise—” “Why did you call him Tortoise, if he wasn’t one?” Alice asked. “We called him Tortoise because he taught us,” said the Mock Turtle Fainting in Coils.” two sobs choked his voice. “Same as if he had a bone in his throat,” the back. At last the Mock Turtle recovered his voice, and, with tears “Change lobsters again!” yelled the Gryphon at the top of its voice. Turtle, suddenly dropping his voice; and the two creatures, who had “There’s a porpoise close behind us, and he’s treading on my tail. They are waiting on the shingle—will you come and join the dance? Will you, won’t you, will you, won’t you, will you join the dance? Will you, won’t you, will you, won’t you, won’t you join the dance? Said he thanked the whiting kindly, but he would not join the dance. Would not, could not, would not, could not, would not join the dance. Would not, could not, would not, could not, could not join the dance. Then turn not pale, beloved snail, but come and join the dance. Will you, won’t you, will you, won’t you, will you join the dance? Will you, won’t you, will you, won’t you, won’t you join the dance?” “Boots and shoes under the sea,” the Gryphon went on in a deep voice, running on the song, “I’d have said to the porpoise, ‘Keep back, wise fish would go anywhere without a porpoise.” and told me he was going a journey, I should say ‘With what porpoise?’” Alice a little timidly: “but it’s no use going back to yesterday, “Stand up and repeat ‘’_Tis the voice of the sluggard_,’” said the “’Tis the voice of the Lobster; I heard him declare, His voice has a timid and tremulous sound.] wrong, and she went on in a trembling voice:— The Mock Turtle sighed deeply, and began, in a voice sometimes choked they doing?” Alice whispered to the Gryphon. “They can’t have anything “Stupid things!” Alice began in a loud, indignant voice, but she “I’m a poor man, your Majesty,” the Hatter began, in a trembling voice, The King looked anxiously at the White Rabbit, who said in a low voice, nearly out of sight, he said in a deep voice, “What are tarts made of?” “Treacle,” said a sleepy voice behind her. little voice, the name “Alice!” “The trial cannot proceed,” said the King in a very grave voice, “until verdict,” he said to the jury, in a low, trembling voice. “Why, there they are!” said the King triumphantly, pointing to the “Off with her head!” the Queen shouted at the top of her voice. Nobody looking up into hers—she could hear the very tones of her voice, and shared their never-ending meal, and the shrill voice of the Queen cries to the voice of the shepherd boy—and the sneeze of the baby, the shriek of the Gryphon, and all the other queer noises, would change unenforceability of any provision of this agreement shall not void the)
mini exit code =
bash exit code = 0
Test  55: ❌ cat minishell.h | grep ");"$
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test  56: ❌ export GHOST=123 | env | grep GHOST
mini exit code =
bash exit code = 1
———————————— redirects
Test  57: ❌ grep hi <./test_files/infile
mini output = ()
bash output = (hi)
mini exit code =
bash exit code = 0
Test  58: ❌ grep hi "<infile" <         ./test_files/infile
mini exit code =
bash exit code = 2
mini error = ()
bash error = ( No such file or directory)
Test  59: ❌ echo hi < ./test_files/infile bye bye
mini output = ()
bash output = (hi bye bye)
mini exit code =
bash exit code = 0
Test  60: ❌ grep hi <./test_files/infile_big <./test_files/infile
mini output = ()
bash output = (hi)
mini exit code =
bash exit code = 0
Test  61: ❌ echo <"./test_files/infile" "bonjour       42"
mini output = ()
bash output = (bonjour 42)
mini exit code =
bash exit code = 0
Test  62: ❌ cat <"./test_files/file name with spaces"
mini output = ()
bash output = (😈 😈 😈 This will break your minishell 😈 😈 😈)
mini exit code =
bash exit code = 0
Test  63: ❌ cat <./test_files/infile_big ./test_files/infile
mini output = ()
bash output = (hi hello world 42)
mini exit code =
bash exit code = 0
Test  64: ❌ cat <"1""2""3""4""5"
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test  65: ❌ echo <"./test_files/infile" <missing <"./test_files/infile"
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test  66: ❌ echo <missing <"./test_files/infile" <missing
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test  67: ❌ cat <"./test_files/infile"
mini output = ()
bash output = (hi hello world 42)
mini exit code =
bash exit code = 0
Test  68: ❌ echo <"./test_files/infile_big" | cat <"./test_files/infile"
mini output = ()
bash output = (hi hello world 42)
mini exit code =
bash exit code = 0
Test  69: ❌ echo <"./test_files/infile_big" | cat "./test_files/infile"
mini output = ()
bash output = (hi hello world 42)
mini exit code =
bash exit code = 0
Test  70: ❌ echo <"./test_files/infile_big" | echo <"./test_files/infile"
mini exit code =
bash exit code = 0
Test  71: ❌ echo hi | cat <"./test_files/infile"
mini output = ()
bash output = (hi hello world 42)
mini exit code =
bash exit code = 0
Test  72: ❌ echo hi | cat "./test_files/infile"
mini output = ()
bash output = (hi hello world 42)
mini exit code =
bash exit code = 0
Test  73: ❌ cat <"./test_files/infile" | echo hi
mini output = ()
bash output = (hi)
mini exit code =
bash exit code = 0
mini error = ()
bash error = ( Broken pipe)
Test  74: ❌ cat <"./test_files/infile" | grep hello
mini output = ()
bash output = (hello)
mini exit code =
bash exit code = 0
Test  75: ❌ cat <"./test_files/infile_big" | echo hi
mini output = ()
bash output = (hi)
mini exit code =
bash exit code = 0
mini error = ()
bash error = ( Broken pipe)
Test  76: ❌ cat <missing
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test  77: ❌ cat <missing | cat
mini exit code =
bash exit code = 0
mini error = ()
bash error = ( No such file or directory)
Test  78: ❌ cat <missing | echo oi
mini output = ()
bash output = (oi)
mini exit code =
bash exit code = 0
mini error = ()
bash error = ( No such file or directory)
Test  79: ❌ cat <missing | cat <"./test_files/infile"
mini output = ()
bash output = (hi hello world 42)
mini exit code =
bash exit code = 0
mini error = ()
bash error = ( No such file or directory)
Test  80: ❌ echo <123 <456 hi | echo 42
mini output = ()
bash output = (42)
mini exit code =
bash exit code = 0
mini error = ()
bash error = ( No such file or directory)
Test  81: ❌ ls >./outfiles/outfile01
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code =
bash exit code = 0
Test  82: ❌ ls >         ./outfiles/outfile01
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code =
bash exit code = 0
Test  83: ❌ echo hi >         ./outfiles/outfile01 bye
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
hi bye
mini exit code =
bash exit code = 0
Test  84: ❌ ls >./outfiles/outfile01 >./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code =
bash exit code = 0
Test  85: ❌ ls >./outfiles/outfile01 >./test_files/invalid_permission
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test  86: ❌ ls >"./outfiles/outfile with spaces"
Only in ./bash_outfiles: outfile with spaces
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code =
bash exit code = 0
Test  87: ❌ ls >"./outfiles/outfile""1""2""3""4""5"
Only in ./bash_outfiles: outfile12345
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code =
bash exit code = 0
Test  88: ❌ ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02"
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test  89: ❌ ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test  90: ❌ cat <"./test_files/infile" >"./outfiles/outfile01"
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
hi
hello
world
42
mini exit code =
bash exit code = 0
Test  91: ❌ echo hi >./outfiles/outfile01 | echo bye
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
hi
mini output = ()
bash output = (bye)
mini exit code =
bash exit code = 0
Test  92: ❌ echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
hi
mini output = ()
bash output = (bye)
mini exit code =
bash exit code = 0
Test  93: ❌ echo hi | echo >./outfiles/outfile01 bye
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
bye
mini exit code =
bash exit code = 0
Test  94: ❌ echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
bye
mini exit code =
bash exit code = 0
Test  95: ❌ echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
hi
bye
mini exit code =
bash exit code = 0
Test  96: ❌ echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
mini output = ()
bash output = (bye)
mini exit code =
bash exit code = 0
mini error = ()
bash error = ( Permission denied)
Test  97: ❌ echo hi >./test_files/invalid_permission | echo bye
mini output = ()
bash output = (bye)
mini exit code =
bash exit code = 0
mini error = ()
bash error = ( Permission denied)
Test  98: ❌ echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye
mini output = ()
bash output = (bye)
mini exit code =
bash exit code = 0
mini error = ()
bash error = ( Permission denied)
Test  99: ❌ echo hi | echo bye >./test_files/invalid_permission
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 100: ❌ echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 101: ❌ echo hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 102: ❌ cat <"./test_files/infile" >./test_files/invalid_permission
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 103: ❌ cat >./test_files/invalid_permission <"./test_files/infile"
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 104: ❌ cat <missing >./outfiles/outfile01
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test 105: ❌ cat >./outfiles/outfile01 <missing
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test 106: ❌ cat <missing >./test_files/invalid_permission
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test 107: ❌ cat >./test_files/invalid_permission <missing
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 108: ❌ cat >./outfiles/outfile01 <missing >./test_files/invalid_permission
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test 109: ❌ ls >>./outfiles/outfile01
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code =
bash exit code = 0
Test 110: ❌ ls >>      ./outfiles/outfile01
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code =
bash exit code = 0
Test 111: ❌ ls >>./outfiles/outfile01 >./outfiles/outfile01
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code =
bash exit code = 0
Test 112: ❌ ls >./outfiles/outfile01 >>./outfiles/outfile01
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code =
bash exit code = 0
Test 113: ❌ ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code =
bash exit code = 0
Test 114: ❌ ls >>./outfiles/outfile01 >>./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code =
bash exit code = 0
Test 115: ❌ ls >>./test_files/invalid_permission
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 116: ❌ ls >>./test_files/invalid_permission >>./outfiles/outfile01
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 117: ❌ ls >>./outfiles/outfile01 >>./test_files/invalid_permission
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 118: ❌ ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 119: ❌ ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test 120: ❌ ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 121: ❌ echo hi >>./outfiles/outfile01 | echo bye
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
hi
mini output = ()
bash output = (bye)
mini exit code =
bash exit code = 0
Test 122: ❌ echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
hi
mini output = ()
bash output = (bye)
mini exit code =
bash exit code = 0
Test 123: ❌ echo hi | echo >>./outfiles/outfile01 bye
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
bye
mini exit code =
bash exit code = 0
Test 124: ❌ echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
bye
mini exit code =
bash exit code = 0
Test 125: ❌ echo hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
hi
bye
mini exit code =
bash exit code = 0
Test 126: ❌ echo hi >>./test_files/invalid_permission | echo bye
mini output = ()
bash output = (bye)
mini exit code =
bash exit code = 0
mini error = ()
bash error = ( Permission denied)
Test 127: ❌ echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye
mini output = ()
bash output = (bye)
mini exit code =
bash exit code = 0
mini error = ()
bash error = ( Permission denied)
Test 128: ❌ echo hi | echo bye >>./test_files/invalid_permission
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 129: ❌ echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: ./mini_outfiles/*: No such file or directory
bash outfiles:
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 130: ❌ cat <minishell.h>./outfiles/outfile
mini exit code =
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test 131: ❌ cat <minishell.h|ls
mini output = ()
bash output = (README.md bash.supp bash_outfiles bonus bonus_bonus builtins extras local.supp loop.out manual_tests mini_outfiles os_specific outfiles pipes redirects syntax test_files tester wildcards)
mini exit code =
bash exit code = 0
mini error = ()
bash error = ( No such file or directory)
———————————— extras
Test 132: ❌  
mini exit code =
bash exit code = 0
Test 133: ❌ $PWD
mini exit code =
bash exit code = 126
mini error = ()
bash error = ( is a directory)
Test 134: ❌ $EMPTY
mini exit code =
bash exit code = 0
Test 135: ❌ $EMPTY echo hi
mini output = ()
bash output = (hi)
mini exit code =
bash exit code = 0
Test 136: ❌ ./test_files/invalid_permission
mini exit code =
bash exit code = 126
mini error = ()
bash error = ( Permission denied)
Test 137: ❌ ./missing.out
mini exit code =
bash exit code = 127
mini error = ()
bash error = ( No such file or directory)
Test 138: ❌ missing.out
mini exit code =
bash exit code = 127
mini error = ()
bash error = ( command not found)
Test 139: ❌ "aaa"
mini exit code =
bash exit code = 127
mini error = ()
bash error = ( command not found)
Test 140: ❌ test_files
mini exit code =
bash exit code = 127
mini error = ()
bash error = ( command not found)
Test 141: ❌ ./test_files
mini exit code =
bash exit code = 126
mini error = ()
bash error = ( is a directory)
Test 142: ❌ /test_files
mini exit code =
bash exit code = 127
mini error = ()
bash error = ( No such file or directory)
Test 143: ❌ minishell.h
mini exit code =
bash exit code = 127
mini error = ()
bash error = ( command not found)
Test 144: ❌ $
mini exit code =
bash exit code = 127
mini error = ()
bash error = ( command not found)
Test 145: ❌ $?
mini exit code =
bash exit code = 127
mini error = ()
bash error = ( command not found)
Test 146: ❌ README.md
mini exit code =
bash exit code = 127
mini error = ()
bash error = ( command not found)
