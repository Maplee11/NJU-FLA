#Q = {0,check_a,check_b,reject,done_check,erase,halt_reject,write_illegal1,write_illegal2,write_illegal3,write_illegal4,write_illegal5,write_illegal6,write_illegal7,write_illegal8,write_illegal9,write_illegal10,write_illegal11,write_illegal12,write_illegal13}

#S = {a,b}

#G = {a,b,c,i,l,e,g,n,p,u,t,_}

#q0 = 0

#B = _

#F = {halt_accept}

#N = 2

0 a_ a_ r* check_a
0 b_ b_ ** reject
0 __ __ ** reject

check_a a_ a_ r* check_a
check_a b_ b_ r* check_b
check_a __ __ ** reject

check_b b_ b_ r* check_b
check_b __ __ l* done_check
check_b a_ a_ ** reject

reject a_ a_ r* reject
reject b_ b_ r* reject
reject __ __ l* erase

erase a_ __ l* erase
erase b_ __ l* erase
erase __ __ r* write_illegal1

write_illegal1 __ i_ r* write_illegal2
write_illegal2 __ l_ r* write_illegal3
write_illegal3 __ l_ r* write_illegal4
write_illegal4 __ e_ r* write_illegal5
write_illegal5 __ g_ r* write_illegal6
write_illegal6 __ a_ r* write_illegal7
write_illegal7 __ l_ r* write_illegal8
write_illegal8 __ __ r* write_illegal9
write_illegal9 __ i_ r* write_illegal10
write_illegal10 __ n_ r* write_illegal11
write_illegal11 __ p_ r* write_illegal12
write_illegal12 __ u_ r* write_illegal13
write_illegal13 __ t_ ** halt_reject
