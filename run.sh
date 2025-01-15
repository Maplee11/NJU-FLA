cd build && make && cd ../bin

./fla ../pda/anbn.pda aaaaaabbbbbb
./fla ../pda/anbn.pda aaabbb
./fla ../pda/anbn.pda aabb
./fla ../pda/anbn.pda ab
echo -----
./fla ../pda/anbn.pda aaabb
./fla ../pda/anbn.pda abbb
./fla ../pda/anbn.pda ba
./fla ../pda/anbn.pda a
./fla ../pda/anbn.pda b
./fla ../pda/anbn.pda ""
echo -----
./fla ../pda/anbn.pda 
./fla ../pda/anbn.pda acb
./fla ./pda/anbn.pda ab
./fla ./pda/anbn.pd ab

echo ---CASE---

./fla ../pda/case.pda ""
./fla ../pda/case.pda "()"
./fla ../pda/case.pda "(())"
./fla ../pda/case.pda "(()()()())()(())()"
./fla ../pda/case.pda "((()()()())()(())())(((()()((())()))(())())())()((()))()"
echo -----
./fla ../pda/case.pda "("
./fla ../pda/case.pda ")"
./fla ../pda/case.pda "())"
./fla ../pda/case.pda "((()()()))(()(())())())()((())()"
./fla ../pda/case.pda "((()()()()()(())()((()()(((()))(())())())()((()))()"
echo -----
./fla ../pda/case.pda "(a)()"
./fla ../pda/case.pda "-"
