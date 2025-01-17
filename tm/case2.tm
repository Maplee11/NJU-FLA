#Q = {0,erase,add1,add2,move_left,accept0,accept1,accept2,accept3,halt_accept,reject0,reject1,reject2,reject3,reject4,halt_reject}

#S = {1}

#G = {1,_,t,r,u,e,f,a,l,s}

#F = {halt_accept}

#q0 = 0

#B = _

#N = 2

0 __ __ ** reject0
0 1_ 11 ** erase

erase 11 _1 rr erase
erase __ __ ** accept0
erase _1 __ ** reject0
erase 1_ 1_ ** add1

add1 1_ 11 *r add2
add2 1_ 11 ** move_left

move_left ** ** *l move_left
move_left *_ *_ *r erase

reject0 __ f_ r* reject1
reject1 __ a_ r* reject2
reject2 __ l_ r* reject3
reject3 __ s_ r* reject4
reject4 __ e_ ** halt_reject

accept0 __ t_ r* accept1
accept1 __ r_ r* accept2
accept2 __ u_ r* accept3
accept3 __ e_ ** halt_accept
