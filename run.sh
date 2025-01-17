cd build && make && cd ../bin
echo ========== ANBN ==============
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
echo ========== CASE1 ==============
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
echo =========== PALINDROME =============
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
echo -----
./fla ../tm/palindrome_detector_2tapes.tm 10000140001
./fla ../tm/palindrome_detector_2tapes.tm a0000140001
echo =========== CASE1 =============
./fla ../tm/case1.tm ab
./fla ../tm/case1.tm aabb
./fla ../tm/case1.tm aaabb
./fla ../tm/case1.tm aaaabbb
echo -----
./fla ../tm/case1.tm ""
./fla ../tm/case1.tm abc
./fla ../tm/case1.tm abbba
./fla ../tm/case1.tm bab
./fla ../tm/case1.tm aba
echo ========== CASE2 ==============
./fla ../tm/case2.tm ""
./fla ../tm/case2.tm 111
./fla ../tm/case2.tm 11111
./fla ../tm/case2.tm 11111111
./fla ../tm/case2.tm 11111111111
./fla ../tm/case2.tm 1111111111111
./fla ../tm/case2.tm 111111111111111111111111111
./fla ../tm/case2.tm 1111111111111111111111111111111111111
echo -----
./fla ../tm/case2.tm 1
./fla ../tm/case2.tm 1111
./fla ../tm/case2.tm 111111111
./fla ../tm/case2.tm 1111111111111111
./fla ../tm/case2.tm 1111111111111111111111111
./fla ../tm/case2.tm 111111111111111111111111111111111111
./fla ../tm/case2.tm 1111111111111111111111111111111111111111111111111
echo =============== TEST DONE ===============
# ./fla -v -h p
# ./fla -v ../tm/case2.tm 11111111
# ./fla -v ../pda/anbn.pda aaaaaaaaaabbbbbbbbbb
# ./fla -v ../pda/case.pda "((()()()())()(())())(((()()((())()))(())())())()((()))()"
# ./fla -v ../pda/case.pda "((()()()()()(())()((()()(((()))(())())())()((()))()"
