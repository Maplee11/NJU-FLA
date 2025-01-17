#Q = {halt_accept,halt_reject,cp,erase1,erase2,start,find_b,write,move_right,0,check_a,check_b,reject,erase,write_illegal1,write_illegal2,write_illegal3,write_illegal4,write_illegal5,write_illegal6,write_illegal7,write_illegal8,write_illegal9,write_illegal10,write_illegal11,write_illegal12,write_illegal13}

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
check_b __ __ l* cp
check_b a_ a_ ** reject

reject *_ *_ r* reject
reject __ __ l* erase

erase *_ __ l* erase
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

cp a_ aa lr cp
cp b_ bb lr cp
cp __ __ rl erase1

erase1 ** _* r* erase1
erase1 _* _* ** start

start _a __ *l find_b
start _b _b ** erase2

find_b _a _a *l find_b
find_b _b _b ** write

write _b cb rl write
write __ __ *r move_right

move_right _* _* *r move_right
move_right __ __ *l start

erase2 _* __ *l erase2
erase2 __ __ lr halt_accept
