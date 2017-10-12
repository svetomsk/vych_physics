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

struct node {
	bool left;
	bool right;
	bool up;
	bool down;

	int x, y;
	node(int x, int y, bool left, bool right, bool up, bool down) {
		this->x = x;
		this->y = y;
		update(left, right, up, down);
	}

	void update(bool left, bool right, bool up, bool down) {
		this->left = left;
		this->right = right;
		this->up = up;
		this->down = down;
	}

	bool getByDir(int dir){
		switch(dir) {
			case 0: return left;
			case 1: return up;
			case 2: return right;
			case 3: return down;
		}
	}

	void setByDir(int dir, bool value) {
		switch(dir) {
			case 0: left = value; return;
			case 1: up = value; return;
			case 2: right = value; return;
			case 3: down = value; return;
		}
	}

	friend bool operator==(const node& left, const node& right);

	std::string str() {
		std::stringstream ss;
		ss << x << " " << y << " " << left << " " << right << " " << up << " " << down;
		return ss.str();
	}
};

bool operator==(const node& left, const node& right) {
    return (left.x == right.x && left.y == right.y);
}

typedef std::vector<std::vector<node> > nodes_t;

void print(nodes_t& nodes) {
	for(int i = 0; i < nodes.size(); i++) {
		for(int j = 0; j < nodes.size(); j++) {
			printf("%d %d %d %d\n", nodes[i][j].left, nodes[i][j].right, nodes[i][j].up, nodes[i][j].down);
		}
	}
	printf("\n");
}
static bool isPathFound;
static std::vector<int> path;

bool isPathExists(nodes_t &nodes, node& start) {
	int size = nodes.size();
	if(!isPathFound) {
		std::queue<node> q;
		q.push(start);
		std::vector<int> used(size * size + 1, 1);
		std::vector<int> parent(size * size + 1);
		path.clear();
		parent[start.x * size + start.y] = -1;
		used[start.x * size + start.y] = 0;
		while(q.size()) {
			node cur = q.front();
			q.pop();
			int x = cur.x;
			int y = cur.y;
			if(y == size - 1) {
				for(int v = x * size + y;  v != -1; v = parent[v]) {
					path.push_back(v);
				}
				reverse(path.begin(), path.end());
				isPathFound = true;
				return true;
			}
			if(cur.left && y - 1 >= 0 && used[x * size + y - 1] == 1) {
				q.push(nodes[x][y - 1]);
				used[x* size + y - 1] = 0;
				parent[x* size + y - 1] = x * size + y;
			}

			if(cur.up && x - 1 >= 0 && used[(x - 1) * size + y] == 1) {
				q.push(nodes[x - 1][y]);
				used[(x - 1) * size + y] = 0;
				parent[(x - 1) * size + y] = x * size + y;
			}

			if(cur.down && x + 1 < size && used[(x + 1) * size + y] == 1) {
				q.push(nodes[x + 1][y]);
				used[(x + 1) * size + y] = 0;
				parent[(x + 1) * size + y] = x * size + y;
			}
			
			if(cur.right && y + 1 < size && used[x * size + y + 1] == 1) {
				q.push(nodes[x][y + 1]);
				used[x* size + y + 1] = 0;
				parent[x * size + y + 1] = x * size + y;
			}
		}
		if(start.x < size - 1) {
			return isPathExists(nodes, nodes[start.x + 1][0]);
		}
		return false;
	} else {
		for(int i = 0; i < path.size() - 1; i++) {
			int x = path[i] / size;
			int y = path[i] % size;

			int x1 = path[i + 1] / size;
			int y1 = path[i + 1] % size;

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

			int check = nodes[x][y].getByDir(dir);
			if(!check) {
				isPathFound = false;
				return isPathExists(nodes, start);
			}
		}

		return true;
	}
}

void removeEdge(nodes_t& nodes, int x, int y, int dir) {
	nodes[x][y].setByDir(dir, false);
	int size = nodes.size();
	if(dir == 0 && y > 0) nodes[x][y - 1].setByDir(2, false);
	if(dir == 1 && x > 0) nodes[x - 1][y].setByDir(3, false);
	if(dir == 2 && y < size - 1) nodes[x][y + 1].setByDir(0, false);
	if(dir == 3 && x < size - 1) nodes[x + 1][y].setByDir(1, false);
}

void removeNode(nodes_t& nodes, int x, int y) {
	for(int dir = 0; dir < nodes.size(); dir++) {
		removeEdge(nodes, x, y, dir);
	}
}

void resetData(int size, nodes_t& nodes) {
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			bool left = j - 1 >= 0;
			bool right = j < size - 1;
			bool up = i - 1 >= 0;
			bool down = i < size - 1;

			nodes[i][j].update(left, right, up, down);
		}
	}
}

int main() 
{
	nodes_t data;
	int size;
	int maxSize = 50;
	int minSize = 3;
	int repeats = 300;
	for(int k = minSize; k < maxSize; k += 1) {
		srand (time(NULL));
		data.clear();
		size = k;
		for(int i = 0; i < size; i++) {
			std::vector<node> tmp;
			for(int j = 0; j < size; j++) {
				bool left = j - 1 >= 0;
				bool right = j < size - 1;
				bool up = i - 1 >= 0;
				bool down = i < size - 1;

				tmp.push_back(node(i, j, left, right, up, down));
			}
			data.push_back(tmp);
		}

		std::vector<int> results;
		int count = 0;
		for(int i = 0; i < repeats; i++) {
			while(isPathExists(data, data[0][0])) {
				count++;
				while(1) {
					int x = rand() % size; // 0..size-1
					int y = rand() % size; // 0..size-1
					if(data[x][y].left || data[x][y].right || data[x][y].up || data[x][y].down) {
						removeNode(data, x, y);
						break;
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

		// std::cout << sum / results.size();
		std::cout <<  "(" << size << ";" << (1.0 - (double)(sum / results.size()) / (double)(size * size)) << ") ";
	}
	return 0;
}