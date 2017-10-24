#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <fstream>

struct node {
	bool left;
	bool right;
	bool up;
	bool down;
	bool forward;
	bool backward;

	int x, y, z;
	node(int x, int y, int z, bool left, bool right, bool up, bool down, bool forward, bool backward) {
		this->x = x;
		this->y = y;
		this->z = z;
		update(left, right, up, down, forward, backward);
	}

	void update(bool left, bool right, bool up, bool down, bool forward, bool backward) {
		this->left = left;
		this->right = right;
		this->up = up;
		this->down = down;
		this->forward = forward;
		this->backward = backward;
	}

	bool getByDir(int dir){
		switch(dir) {
			case 0: return left;
			case 1: return up;
			case 2: return right;
			case 3: return down;
			case 4: return forward;
			case 5: return backward;
		}
	}

	void setByDir(int dir, bool value) {
		switch(dir) {
			case 0: left = value; return;
			case 1: up = value; return;
			case 2: right = value; return;
			case 3: down = value; return;
			case 4: forward = value; return;
			case 5: backward = value; return;
		}
	}

	friend bool operator==(const node& left, const node& right);

	std::string str() {
		std::stringstream ss;
		ss << x << " " << y << " " << left << " " << right << " " << up << " " << down << " " << forward << " " + backward;
		return ss.str();
	}
};

bool operator==(const node& left, const node& right) {
    return (left.x == right.x && left.y == right.y && left.z == right.z);
}

typedef std::vector<std::vector<std::vector<node> > > nodes_t;

void print(nodes_t& nodes) {
	for(int i = 0; i < nodes.size(); i++) {
		for(int j = 0; j < nodes[0].size(); j++) {
			for(int k = 0; k < nodes[0][0].size(); k++) {
				printf("%d %d %d %d %d %d\n", nodes[i][j][k].left, nodes[i][j][k].right, nodes[i][j][k].up,
				 nodes[i][j][k].down, nodes[i][j][k].forward, nodes[i][j][k].backward);
			}
		}
	}
	printf("\n");
}
static bool isPathFound;
static std::vector<int> path;
static int bfsCount = 0;


bool isPathExists(nodes_t &nodes, std::vector<node> & startVertexes, int index) {
	int sizeX = nodes.size();
	int sizeY = nodes[0].size();
	int sizeZ = nodes[0][0].size();

	if(!isPathFound) {
		bfsCount++;
		if(index == startVertexes.size())  {
			return false;
		}
		node tmp = startVertexes[index];
		node start = nodes[tmp.x][tmp.y][tmp.z];
		std::queue<node> q;
		q.push(start);
		std::vector<int> used(sizeX * sizeY * sizeZ + 1, 1);
		std::vector<int> parent(sizeX * sizeY * sizeZ + 1);
		path.clear();
		parent[start.z * sizeX * sizeY + start.x * sizeY + start.y] = -1;
		used[start.z * sizeX * sizeY + start.x * sizeY + start.y] = 0;
		while(q.size()) {
			node cur = q.front();
			q.pop();
			int x = cur.x;
			int y = cur.y;
			int z = cur.z;
			if(y == sizeY - 1) {
				for(int v = z * sizeX * sizeY + x * sizeY + y;  v != -1; v = parent[v]) {
					path.push_back(v);
				}
				reverse(path.begin(), path.end());
				// for(int i = 0; i < path.size(); i++) {
				// 	std::cout << path[i] << " ";
				// }
				// std::cout << std::endl;
				isPathFound = true;
				return true;
			}
			if(cur.left && y - 1 >= 0 && used[z * sizeX * sizeY + x * sizeY + y - 1] == 1) {
				q.push(nodes[x][y - 1][z]);
				used[z * sizeX * sizeY + x * sizeY + y - 1] = 0;
				parent[z * sizeX * sizeY + x * sizeY + y - 1] = z * sizeX * sizeY + x * sizeY + y;
			}

			if(cur.up && x - 1 >= 0 && used[z * sizeX * sizeY + (x - 1) * sizeY + y] == 1) {
				q.push(nodes[x - 1][y][z]);
				used[z * sizeX * sizeY + (x - 1) * sizeY + y] = 0;
				parent[z * sizeX * sizeY + (x - 1) * sizeY + y] = z * sizeX * sizeY + x * sizeY + y;
			}

			if(cur.down && x + 1 < sizeX && used[z * sizeX * sizeY + (x + 1) * sizeY + y] == 1) {
				q.push(nodes[x + 1][y][z]);
				used[z * sizeX * sizeY + (x + 1) * sizeY + y] = 0;
				parent[z * sizeX * sizeY + (x + 1) * sizeY + y] = z * sizeX * sizeY + x * sizeY + y;
			}
			
			if(cur.right && y + 1 < sizeY && used[z * sizeX * sizeY + x * sizeY + y + 1] == 1) {
				q.push(nodes[x][y + 1][z]);
				used[z * sizeX * sizeY + x * sizeY + y + 1] = 0;
				parent[z * sizeX * sizeY + x * sizeY + y + 1] = z * sizeX * sizeY + x * sizeY + y;
			}

			if(cur.forward && z + 1 < sizeZ && used[(z + 1) * sizeX * sizeY + x * sizeY + y] == 1) {
				q.push(nodes[x][y][z + 1]);
				used[(z + 1) * sizeX * sizeY + x * sizeY + y] = 0;
				parent[(z + 1) * sizeX * sizeY + x * sizeY + y] = z * sizeX * sizeY + x * sizeY + y;
			}

			if(cur.backward && z - 1 >= 0 && used[(z - 1) * sizeX * sizeY + x * sizeY + y] == 1) {
				q.push(nodes[x][y][z - 1]);
				used[(z - 1) * sizeX * sizeY + x * sizeY + y] = 0;
				parent[(z - 1) * sizeX * sizeY + x * sizeY + y] = z * sizeX * sizeY + x * sizeY + y;
			}
		}
		
		return isPathExists(nodes, startVertexes, index + 1);	
	} else {
		for(int i = 0; i < path.size() - 1; i++) {
			int y = path[i] % sizeY;
			int z = path[i] / (sizeX * sizeY);
			int x = (path[i] - z * sizeX * sizeY - y) / sizeY;

			int y1 = path[i + 1] % sizeY;
			int z1 = path[i + 1] / (sizeX * sizeY);
			int x1 = (path[i + 1] - z1 * sizeX * sizeY - y1) / sizeY;

			int dz = z - z1;
			int dx = x - x1;
			int dy = y - y1;
			int dir;
			if(dx == 1) // up
				dir = 1;
			if(dx == -1) // down
				dir = 3;
			if(dy == 1) // left
				dir = 0;
			if(dy == -1) // right
				dir = 2;
			if(dz == 1) // backward
				dir = 5;
			if(dz == -1) // forward
				dir = 4;

			int check = nodes[x][y][z].getByDir(dir);
			if(!check) {
				// std::cout << "fail to step\n";
				isPathFound = false;
				return isPathExists(nodes, startVertexes, 0);
			}
		}

		return true;
	}
}

void removeEdge(nodes_t& nodes, int x, int y, int z, int dir) {
	nodes[x][y][z].setByDir(dir, false);
	int sizeX = nodes.size();
	int sizeY = nodes[0].size();
	int sizeZ = nodes[0][0].size();
	if(dir == 0 && y > 0) nodes[x][y - 1][z].setByDir(2, false);
	if(dir == 1 && x > 0) nodes[x - 1][y][z].setByDir(3, false);
	if(dir == 2 && y < sizeY - 1) nodes[x][y + 1][z].setByDir(0, false);
	if(dir == 3 && x < sizeX - 1) nodes[x + 1][y][z].setByDir(1, false);
	if(dir == 4 && z < sizeZ - 1) nodes[x][y][z + 1].setByDir(5, false);
	if(dir == 5 && z > 0) nodes[x][y][z - 1].setByDir(4, false);
}

void removeNode(nodes_t& nodes, int x, int y, int z) {
	int size = nodes.size();
	for(int dir = 0; dir < 6; dir++) {
		removeEdge(nodes, x, y, z, dir);
	}
}

void resetData(int size, nodes_t& nodes) {
	int sizeX = nodes.size();
	int sizeY = nodes[0].size();
	int sizeZ = nodes[0][0].size();
	for(int i = 0; i < sizeX; i++) {
		for(int j = 0; j < sizeY; j++) {
			for(int k = 0; k < sizeZ; k++) {
				bool left = j - 1 >= 0;
				bool right = j < sizeY - 1;
				bool up = i - 1 >= 0;
				bool down = i < sizeX - 1;
				bool forward = k < sizeZ - 1;
				bool backward = k - 1 >= 0;
				nodes[i][j][k].update(left, right, up, down, forward, backward);
			}
		}
	}
}

int main() 
{
	nodes_t data;
	int size;
	bool mode3D = false;
	bool modeEdge = false;

	int sizeZ = 1;
	int maxSize = 70;
	int minSize = 2;
	int step = 2;

	int minRepeats = 25;
	int maxRepeats = minRepeats + 3;
	int repStep = 1;

	std::ofstream file;
	file.open("output.txt");

	std::vector<double> disp;
	for(int r = minRepeats; r < maxRepeats; r+=repStep) {
		for(int k = minSize; k < maxSize; k += step) {
			size = k;
			if(mode3D)
				sizeZ = k;
			srand (time(NULL));
			data.clear();

			for(int i = 0; i < size; i++) {
				std::vector<std::vector<node> > row;
				for(int j = 0; j < size; j++) {
					std::vector<node> tmp;
					for(int k = 0; k < sizeZ; k++) {
						bool left = j - 1 >= 0;
						bool right = j < size - 1;
						bool up = i - 1 >= 0;
						bool down = i < size - 1;
						bool forward = k < sizeZ - 1;
						bool backward = k - 1 >= 0;
						tmp.push_back(node(i, j, k, left, right, up, down, forward, backward));
					}
					row.push_back(tmp);
				}
				data.push_back(row);
			}
			std::vector<node> startVertexes;
			for(int j = 0; j < sizeZ; j++){
				for(int i = 0; i < size; i++) {
					startVertexes.push_back(data[i][0][j]);
				}
			}
			std::vector<int> results;
			int count = 0;

			for(int i = 0; i < r; i++) {			

				while(isPathExists(data, startVertexes, 0)) {
					count++;
					while(1) {
						int x = rand() % size; // 0..size-1
						int y = rand() % size; // 0..size-1
						int z = rand() % sizeZ; // 0..size-1
						if(data[x][y][z].left || data[x][y][z].right || data[x][y][z].up || data[x][y][z].down ||
							data[x][y][z].forward || data[x][y][z].backward) {
							if(!modeEdge) {
								removeNode(data, x, y, z);
								break;
							}
							else {
								int dir = rand() % 6;
								if(data[x][y][z].getByDir(dir)) {
									// std::cout << x << " " << y << " " << z << " " << data[x][y][z].getByDir(dir) << " " << dir << "\n";
									removeEdge(data, x, y, z, dir);
									break;
								}
							}
						}
					}

				}

				results.push_back(count);
				count = 0;
				resetData(size, data);			
			}
			int sum = 0;
			for(int i = 0; i < results.size(); i++) {
				sum += results[i];
			}
			// std::cout << sum << " " << (sum / results.size()) << " " << 2 * size * (size - 1) << std::endl;
			double value;
			double average = sum / results.size();
			if(!modeEdge)
				value = 1.0 - average / (double)(size * size * sizeZ);
			else {
				value = 1.0 - average / (double)(2.0 * (size - 1) * size);
			}
			double curDisp = 0;
			for(int i = 0; i < results.size(); i++) {
				double cur = (1.0 - results[i] / (double)(size * size * sizeZ));
				curDisp += (cur - value) * (cur - value);
			}			
			curDisp /= results.size();
			disp.push_back(curDisp);
			// file <<  "(" << size << ";" << value << ") ";
			file << size << " " << value << "\n";
			// file << size << " " << curDisp << "\n";
		}
		file << "---\n";
	}
	// file << "---\n";
	file.close();		
	return 0;
}