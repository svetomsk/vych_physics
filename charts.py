import matplotlib.pyplot as plt

filename = 'output.txt'

x = []
y = []
colors = ['ro-', 'bo-', 'ko-', 'go-']
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
for i in range(0, len(x)):
	if i == len(x) - 1:
		plt.plot(x[i], y[i], colors[i], linewidth=3.0)
	else:
		plt.plot(x[i], y[i], colors[i])
plt.plot(x[0], justY, 'ro-')
plt.show()