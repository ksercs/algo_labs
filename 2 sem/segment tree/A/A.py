fin = open("sum0.in", "r")
fout = open("sum0.out", "w")

n, x, y, a0 = [int(x) for x in fin.readline().split()]
a = []
m, z, t, b0 = [int(x) for x in fin.readline().split()]
b = []
pref = []
s = 0
c = []

a.append(a0)
b.append(b0)
pref.append(a0)
for i in range(1, n):
    a.append((a[i-1] * x + y) % (1 << 16))
    pref.append(pref[i-1] + a[i])
    #print(pref[i])

for i in range(1, 2*m):
    b.append((z * b[i-1] + t) % (1 << 30))
    #print(b)

for i in range(0, 2*m):
    c.append(b[i] % n)
    #print(c[i])
    if (i%2 and c[i-1] > c[i]):
        c[i-1], c[i] = c[i], c[i-1]
    if (i%2):
        if (c[i-1] > 0):
            s += pref[c[i]] - pref[c[i-1] - 1]
        else :
            s += pref[c[i]]

print(s, file = fout)
fout.close()

