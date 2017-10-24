import matplotlib.pyplot as plt

filename = 'output.txt'

x = []
y = []
colors = ['ro-', 'bo-', 'ko-', 'go-']

#read from file
with open(filename, 'r') as file:
	curX = []
	curY = []
	for line in file:
		if line == '---\n':
			x.append(curX)
			y.append(curY)
			curX = []
			curY = []
		else:
			sp = line.split(" ")
			curX.append(sp[0])
			curY.append(sp[1][0:-1])

#calc average values
averageX = []
averageY = []
justY = []
for i in range(0, len(x[0])):
	justY.append(0.59)
	curAvX = 0
	curAvY = 0
	for j in range(0, len(x)):
		curAvX = curAvX + float(x[j][i])
		curAvY = curAvY + float(y[j][i])
	averageX.append(curAvX / len(x))
	averageY.append(curAvY / len(x))
x.append(averageX);
y.append(averageY);



# calc 1/x^k
ys = []
k = 1.85
for i in range(0, len(x[0])):
	xs = float(x[0][i])
	ys.append(1.0 / pow(xs, k))


# drawing

# draw values
for i in range(0, len(x)):
	if i == len(x) - 1:
		plt.plot(x[i], y[i], colors[i], linewidth=3.0)
	else:
		plt.plot(x[i], y[i], colors[i])

# draw dispertion
# plt.plot(x[0][10:], y[0][10:], 'ro-')
# plt.plot(x[0][10:], ys[10:], 'go-')

plt.show()