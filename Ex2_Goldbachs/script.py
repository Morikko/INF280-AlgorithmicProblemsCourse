primes = open("primes.txt", "r")
tab = open("tab", "w")

tab.write("primes[] = { ")
line = 0
for temp in primes:
    line = line + 1
    temp = temp[:-1]
    tab.write(temp, )
    tab.write(", ")
tab.write("};")

print line

primes.close();
tab.close()

