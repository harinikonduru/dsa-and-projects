n1=input('enter a name: ').lower()
n1=n1.replace(" ", "")
n2=input('enter a name: ').lower()
n2=n2.replace(" ", "")
l1=list(n1)
l2=list(n2)
for i in l1.copy():
    for j in l2.copy():
        if i==j:
            l1.remove(i)
            l2.remove(j)
            break
c=len(l1+l2)
result=['friends', 'love', 'affection', 'marriage', 'enemies', 'sex']
while len(result)>1:
    split=(c%len(result))-1
    if split>=0:
        result=result[split+1:]+result[:split]
    else:
        result=result[:-1]
print(result[0])