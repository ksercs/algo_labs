fin = open('formation.in', 'r')
fout = open('formation.out', 'w')

num = [1]
str = fin.readline()
n, m = str.split()
n = int(n)
m = int(m)

for i in range(m): 
	s = fin.readline()
	if s[2] == "f" :
		con, a, b = s.split()
		a = int(a)
		b = int(b)
		ind = num.index(b)
		num = num[:ind]+[a]+num[ind:]
	if s[0] == "r" :
		con, a, b = s.split()
		a = int(a)
		b = int(b)
		ind = num.index(b)
		num = num[:ind+1]+[a]+num[ind+1:]
	if s[2] == "a" :
		con, a = s.split()
		a = int(a)
		num.remove(a)
	if s[0] == "n" :
		con, a = s.split()
		a = int(a)
		ind = num.index(a)
		if len(num) == 1 :
			print(0, 0, file=fout)
		elif ind == 0 :
			print(0, num[ind+1], file=fout)
		elif ind == len(num)-1 : 
			print(num[ind-1], 0, file=fout)
		else :
			print(num[ind-1], num[ind+1], file=fout)
fout.close()