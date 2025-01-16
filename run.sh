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
echo -----
./fla ../tm/palindrome_detector_2tapes.tm 1
./fla ../tm/palindrome_detector_2tapes.tm 0
./fla ../tm/palindrome_detector_2tapes.tm 101
./fla ../tm/palindrome_detector_2tapes.tm 111
./fla ../tm/palindrome_detector_2tapes.tm 1001
./fla ../tm/palindrome_detector_2tapes.tm 1111
./fla ../tm/palindrome_detector_2tapes.tm 10001
./fla ../tm/palindrome_detector_2tapes.tm 10101
./fla ../tm/palindrome_detector_2tapes.tm 100001
./fla ../tm/palindrome_detector_2tapes.tm 111111
./fla ../tm/palindrome_detector_2tapes.tm 1000001
./fla ../tm/palindrome_detector_2tapes.tm 1010101
./fla ../tm/palindrome_detector_2tapes.tm 111000111
./fla ../tm/palindrome_detector_2tapes.tm 1001001
./fla ../tm/palindrome_detector_2tapes.tm 101010101
./fla ../tm/palindrome_detector_2tapes.tm 100010001
./fla ../tm/palindrome_detector_2tapes.tm 111010111
./fla ../tm/palindrome_detector_2tapes.tm 101000101
./fla ../tm/palindrome_detector_2tapes.tm 10011001
./fla ../tm/palindrome_detector_2tapes.tm 10101010101
./fla ../tm/palindrome_detector_2tapes.tm 10000000001
./fla ../tm/palindrome_detector_2tapes.tm 110000011
./fla ../tm/palindrome_detector_2tapes.tm ""
echo -----
./fla ../tm/palindrome_detector_2tapes.tm 1000010001
./fla ../tm/palindrome_detector_2tapes.tm 111011111
./fla ../tm/palindrome_detector_2tapes.tm 101110101
./fla ../tm/palindrome_detector_2tapes.tm 101001101
./fla ../tm/palindrome_detector_2tapes.tm 111100111
./fla ../tm/palindrome_detector_2tapes.tm 111001111
./fla ../tm/palindrome_detector_2tapes.tm 10010001
./fla ../tm/palindrome_detector_2tapes.tm 010110
./fla ../tm/palindrome_detector_2tapes.tm 11100
./fla ../tm/palindrome_detector_2tapes.tm 10
./fla ../tm/palindrome_detector_2tapes.tm 01
./fla ../tm/palindrome_detector_2tapes.tm 110
./fla ../tm/palindrome_detector_2tapes.tm 01101
./fla ../tm/palindrome_detector_2tapes.tm 11111111111110
echo ========================
./fla ../tm/palindrome_detector_2tapes.tm 1001001
