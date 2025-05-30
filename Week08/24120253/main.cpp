#include<iostream>
#include<fstream>
#include<stack>
#include<queue>
#include<vector>
#include<sstream>

using namespace std;

// 1. Hàm chuyển ma trận kề sang danh sách kề 
vector<vector<int>> convertMatrixToList(const string& filename) {
	ifstream infile(filename);
	if (!infile.is_open()) { // ktra file 
		cout << "Cannot open inputfile !!!" << endl;
	}
	// đọc số lượng phần tử 
	int n;
	infile >> n;

	vector<vector<int>> aList(n); // danh sách kề kết quả 
	vector<vector<int>> aMatrix(n,vector<int>(n)); //ma trận đọc từ file 

	// đọc file 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			infile >> aMatrix[i][j];
		}
	}

	// Chuyển từ ma trận kề sang danh sách kề 
	for (int i = 0; i < n; i++) {
		int numEgde = 0;
		for (int j = 0; j < n; j++) {
			if (aMatrix[i][j] != 0) {
				numEgde++;
				aList[i].push_back(j);
			}
		}
		aList[i].insert(aList[i].begin(), numEgde);
	}

	infile.close();
	return aList;
}

//2. Hàm chuyển danh sách kề sang ma trận kề
vector<vector<int>> convertListToMatrix(const string& filename) {
	ifstream infile(filename);
	if (!infile.is_open()) {
		cout << "Cannot open inputfile !!!" << endl;
		
	}
	int n;
	infile >> n; // đọc cấp của ma trận 
	vector<vector<int>> aList(n); //  danh sách kề 
	vector<vector<int>> aMatrix(n, vector<int>(n)); // ma trận kề

	// đọc danh sách 
	for (int i = 0; i < n; i++) {
		int numEgde = 0; // đọc số lượng đỉnh
		infile >> numEgde; 
		for (int j = 0; j < numEgde; j++) {
			int temp;
			infile >> temp;  // đọc vị trí các đỉnh thôi 
			aList[i].push_back(temp);
		}
	}

	// chuyển sang ma trận kề: lúc khai báo ma trận kề thì tất cả các phần tử đã được khai báo giá trị 0
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < aList[i].size(); j++) {
			aMatrix[i][aList[i][j]] = 1; // các vị trí đỉnh là 1; 
		}
	}

	infile.close();
	return aMatrix;
}

//3. Kiểm tra đồ thị có hướng hay vô hướng: 
// Vô hướng => ma trận có dạng đối xứng vif a[i][j] = a[j][i]
// Có hướng=> ma trận ko đối xứng 
bool isDirected(const vector<vector<int>>& adjMatrix) {
	for (int i = 0; i < adjMatrix.size(); i++) {
		for (int j = 0; j < adjMatrix[i].size(); j++) {
			if (adjMatrix[i][j] != adjMatrix[j][i]) return true; // có hướng khi không đối xứng 
		}
	}
	return false;
}

//Hàm đếm số đỉnh của đồ thị 
int countVertices(const vector<vector<int>>& adjMatrix) {
	return adjMatrix.size();
}

// Hàm đếm số cạnh của đồ thị 
int countEdges(const vector<vector<int>>& adjMatrix) {
	int res = 0;
	if (isDirected(adjMatrix)) { // nếu là có hướng thì mỗi phần tử !=0 đều là 1 cạnh vì đều dần đến 1 đỉnh khác  
		for (int i = 0; i < adjMatrix.size(); i++) {
			for (int j = 0; j < adjMatrix[i].size(); j++) {
				if (adjMatrix[i][j] != 0) {
					res += 1;
				}
			}
		}
	}
	else { // nếu vô hướng thì ta cộng tất cả rồi chia đôi vì 2 đỉnh nối nhau sẽ có 2 chiều 
		for (int i = 0; i < adjMatrix.size(); i++) {
			for (int j = 0; j < adjMatrix[i].size(); j++) {
				if (adjMatrix[i][j] != 0) {
					res += 1;
				}
			}
		}
		res = res / 2; 
	}
	return res;
}


//Hàm check có bị cô lập hay không: 
bool isIsolated(vector<vector<int>> aMatrix, int vertice) {
	for (int i = 0; i < aMatrix.size(); i++) { // check theo hàng dọc 
		if (aMatrix[i][vertice] != 0) return false; // có cạnh thì không bị cô lập 
	}
	for (int i = 0; i < aMatrix[vertice].size(); i++) {
		if (aMatrix[vertice][i] != 0) return false; // check theo hàng ngang 
	}

	return true;
}

//Hàm list những đỉnh bị cô lập
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
	vector<int> res;
	for (int i = 0; i < adjMatrix.size(); i++) {
		if (isIsolated(adjMatrix, i)) { // nếu đúng bị cô lập 
			res.push_back(i);
		}
	}
	return res; 
}


//Hàm check Complete Graph : là completeGraph khi thỏa 1 đỉnh đều có cạnh nối với tất cả các đỉnh còn lại 
bool isCompleteGraph(const vector<vector<int>>& adjMatrix) { 
	
	for (int i = 0; i < adjMatrix.size(); i++) {
		for (int j = 0; j < adjMatrix[i].size(); j++) {
			if (j == i) {
				if (adjMatrix[i][j] != 0) return false; // tại i=j thì phải là  0 
			}
			else if (adjMatrix[i][j] != 1) return false; // các vị trí khác thì phải là 1 hết để đồ thị là complete
		}
	}
	return true;
}


// Hàm kiểm tra đồ thị lưỡng phần: sử dụng bfs để tô màu,,  
//Bipartite : không có cạnh giữa các đỉnh trong 1 tập 
bool isBipartite(vector<vector<int>>& adjMatrix) {
	vector<int > visit(adjMatrix.size(), -1); // khởi tạo vector visit ứng với vị trí các đỉnh, chưa duyệt là -1 
    
	for (int i = 0; i < adjMatrix.size(); i++) {
		queue<int> q; // queue để chứa chỉ số các đỉnh 
		if (visit[i] == -1) { // chưa duyệt qua đỉnh này 
			q.push(i);
			visit[i] = 0; // duyệt qua rồi cập nhật bằng 0; 
			while (!q.empty()) { // Nếu queue không rỗng thì xử lí 
				int temp = q.front(); // chỉ số node đầu queue 
				q.pop(); // bỏ ra khỏi q 

				for (int j = 0; j < adjMatrix[temp].size(); j++) { // duyêt các node kề của temp 
					if (adjMatrix[temp][j] == 1) { // tức là có cạnh từ temp->j
						if (visit[j] == -1) { // đỉnh j vẫn chưa được duyệt 
							visit[j] = 1 - visit[temp]; // cập nhật là đã duyệt nhưng phải đối lập temp 
							q.push(j);
						}
						else if (visit[j] == visit[temp]) { // trường hợp 2 node kề giống nhau 
							return false; // sẽ không phải là bipartite
						}
					}

				}
			}
	    }
	}
	return true;
}

// Hàm check phải completeBipartite không: 
// CompleteBipartite: TẤT CẢ 1 đỉnh trong tập này nối toàn bộ đỉnh tập kia 

bool isCompleteBipartite(vector<vector<int>>& adjMatrix) {
	vector<int > visit(adjMatrix.size(), -1); // khởi tạo vector visit ứng với vị trí các đỉnh, chưa duyệt là -1 

    // Kiểm tra lưỡng phân 
	for (int i = 0; i < adjMatrix.size(); i++) {
		queue<int> q; // queue để chứa chỉ số các đỉnh 
		if (visit[i] == -1) { // chưa duyệt qua đỉnh này 
			q.push(i);
			visit[i] = 0; // duyệt qua rồi cập nhật bằng 0; 
			while (!q.empty()) { // Nếu queue không rỗng thì xử lí 
				int temp = q.front(); // chỉ số node đầu queue 
				q.pop(); // bỏ ra khỏi q 

				for (int j = 0; j < adjMatrix[temp].size(); j++) { // duyêt các node kề của temp 
					if (adjMatrix[temp][j] == 1) { // tức là có cạnh từ temp->j
						if (visit[j] == -1) { // đỉnh j vẫn chưa được duyệt 
							visit[j] = 1 - visit[temp]; // cập nhật là đã duyệt nhưng phải đối lập temp 
							q.push(j);
						}
						else if (visit[j] == visit[temp]) { // trường hợp 2 node kề giống nhau 
							return false; // sẽ không phải là bipartite
						}
					}

				}
			}
		}
	}

	// Sau khi kiểm tra, phân chia tập U và V
	vector<int> setU, setV;
	for (int i = 0; i < adjMatrix.size(); ++i) {
		if (visit[i] == 0) setU.push_back(i);
		else setV.push_back(i);
	}

	// Kiểm tra hoàn toàn: mọi đỉnh U nối với mọi đỉnh V
	for (int u : setU) {
		for (int v : setV) {
			if (adjMatrix[u][v] == 0 && adjMatrix[v][u] == 0) {
				// Nếu không có cạnh giữa u và v (cả hai chiều) thì không hoàn toàn
				return false;
			}
		}
	}

	return true;
}


//4. chuyển có hướng sang vô hướng: kiểm tra phần tử đối xứng tại phần tử nào != 0 
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
	vector<vector<int>> res(adjMatrix.size(), vector<int>(adjMatrix.size())); // vector kết quả 
	
	for (int i = 0; i < adjMatrix.size(); i++) {
		for (int j = 0; j < adjMatrix[i].size(); j++) {
				res[i][j] = adjMatrix[i][j]; // lấy mảng
		}
	}

	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res[i].size(); j++) {
			if (res[i][j] == 1) {
				res[j][i] = 1; // nếu bằng 1 thì đối xứng cũng bằng 1 để tạo cạnh 2 chiều 
			}
		}
	}

	return res;
}


//5. chuyển đồ thị vô huóng gốc thành đồ thị bù 
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
	vector<vector<int>> res(adjMatrix.size(), vector<int>(adjMatrix.size())); // vector kết quả 

	for (int i = 0; i < adjMatrix.size(); i++) {
		for (int j = 0; j < adjMatrix[i].size(); j++) {
			res[i][j] = adjMatrix[i][j]; // lấy mảng
		}
	}

	for (int i = 0; i < adjMatrix.size(); i++) {
		for (int j = 0; j < adjMatrix[i].size(); j++) {
			if (i == j) {
				continue; 
			}
			else {
				if (res[i][j] == 0) {
					res[i][j] = 1; 
				}
				else {
					res[i][j] = 0;
				}
			}
		}
	}
	return res;
}

//6. using Hierholzer’s Algorithm để tìm chu trình Euler 
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
	vector<int> res;
	int start = -1; 
	stack<int> s; 

	vector<vector<int>> graph = adjMatrix;        // ma trận phụ để thay đổi 

	// tìm đỉnh bắt đầu chu trình 
	for (int i = 0; i < graph.size(); i++) {
		if (start == -1) { // nếu chưa tìm được 
			for (int j = 0; j < graph.size(); j++) {
				if (graph[i][j] != 0) {
					start = i;
					break; // tìm được thì break 
				}
			}
		}
		else {
			break; 
		}
	}

	if (start == -1) { // nếu không tìm thấy đỉnh bắt đầu thì đồ thị rỗng 
		return {};
	}

	s.push(start);

	while (!s.empty()) {
		int top = s.top();
		
		bool found = false;  // bién cờ xem có cạnh từ top tới đỉnh khác hay là ngõ cụt, false là chưa có cạnh nào 

		//Xét từ top đến các đỉnh kề nó 
		for (int j = 0; j < graph.size(); j++) {
			if (graph[top][j] == 1) { // có cạnh từ top đến j chưa duyệt 
				found = true; // đánh dấu đã duyệt 
				graph[top][j] = 0; 
				graph[j][top] = 0; // vì chỉ đi qua 1 lần nên bỏ luon các cạnh đã qua 
				s.push(j);
				break; // tìm được đỉnh mới rồi thì không xét ở đỉnh hiện tại nữa 
			}
		}
		if (found == false) { // không tìm thấy đỉnh để nó đi đến 
			res.push_back(top);
			s.pop();
		}

	}
	reverse(res.begin(), res.end()); // đảo ngược đẻe có kết quả đúng 
	return res;
}

//7. spaning tree với bfs: 
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	vector<int> visit(adjMatrix.size(), -1); // tạo vector kiểm tra đỉnh 
	vector<vector<int>> res(adjMatrix.size(), vector<int> (adjMatrix.size(),0)); // khởi tạo ma trận spanning tree 

	
		queue<int>	q; 
		q.push(start);
		visit[start] = 0; // duyệt qua rồi 

		while (!q.empty()) {
			int temp = q.front();
			q.pop(); 

			// xét các đỉnh kề của temp 
			for (int i = 0; i < adjMatrix[temp].size(); i++) {
				if (adjMatrix[temp][i] == 1) { // có cạnh từ temp đến i 
					if (visit[i] == -1) { // chưa được duyệt 
						visit[i] = 0; // đánh đấu duyệt 
						q.push(i);
						
						res[i][temp] = 1; // cập nhật cạnh spanning tree 
						res[temp][i] = 1;
					}

				}
			}
		}
	
	return res; 
}


// spanning với dfs: 
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	vector<int> visit(adjMatrix.size(), -1); 
	vector<vector<int>> res(adjMatrix.size(), vector<int>(adjMatrix.size(), 0));

	stack<int> s;
	s.push(start); // đẩy đỉnh đầu tiên 
	visit[start] = 0; // cập nhật đã đuyệt 
	while (!s.empty()) {
		int temp = s.top();
		s.pop();
		
		// đưa tất cả các đinhr kề của top stack vào stack
		for (int i = 0; i < adjMatrix[temp].size(); i++) {
			if (adjMatrix[temp][i] == 1) { // có cạnh 
				if (visit[i] == -1) { // chưa được duyệt 
					s.push(i);
					visit[i] = 0;
					res[i][temp] = 1;
					res[temp][i] = 1;
				}
			}
		}
	}
	return res; 
}


//8. Nhận diện giữa 2 đỉnh có cạnh hay không (trực tiếp và gián tiếp )
bool Connected(int u, int v, const vector<vector<int>>& adjMatrix) {

	//nối trực tiếp 
	if (adjMatrix[u][v] == 1 || adjMatrix[v][u] == 1) return true;


	vector<int> visit(adjMatrix.size(), -1); // vector check đỉnh đã duyệt 
	queue<int> q; 
	q.push(u);
	visit[u] = 0;

	while (!q.empty()) {
		int temp = q.front();
		q.pop();
		if (temp == v) return true;
		for (int i = 0; i < adjMatrix[temp].size(); i++) {
			if (adjMatrix[temp][i] == 1) { // có cạnh 
				if (visit[i] == -1) { // chưa được duyệt 
					q.push(i);
					visit[i] = 0;
				}
			}
		}
	}

	return false; 
}
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
	if (Connected(u, v, adjMatrix) == 1 && Connected(v, u, adjMatrix) == 1) return true;
	return false;
}

//9. Find the shortest path between two vertices of a given graph using (*Weighted Graph):

// dijkstra's algorithm 
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> dist(n, INT_MAX);   // dist[i]: khoảng cách ngắn nhất từ start đến i, ban đầu gán khoảng cách từ 
									// từ đỉnh đầu cho đến các đỉnh là vô cùng 
	vector<int> parent(n, -1);      // cho biết đỉnh trước của đỉnh đang xét, u->v : parent[v]=u
	vector<bool> visited(n, false); // đánh dấu đỉnh đã xử lý

	dist[start] = 0;

	// Hàng đợi ưu tiên chứa (khoảng cách, đỉnh), tự động sắp xếp tăng dần theo khoảng cách
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({ 0, start });

	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();

		if (visited[u]) continue; // duyệt rồi bỏ qua 
		visited[u] = true;

		for (int v = 0; v < n; ++v) {
			int weight = adjMatrix[u][v]; // trọng số từ u đến v 
			if (weight > 0 && !visited[v]) { // có cạnh và đỉnh v vẫn chưa được duyệt 
				if (dist[u] + weight < dist[v]) { // xét đường đi mới có ngắn hơn đường đi cũ 
					dist[v] = dist[u] + weight; // cập nhật đường đi mới 
					parent[v] = u;   
					pq.push({ dist[v], v });
				}
			}
		}
	}

	if (dist[end] == INT_MAX) return {}; // Cuối cùng nếu end vẫn bằng vô cùng thì không có đường đi

	// Truy vết đường đi từ end về start
	vector<int> path;
	for (int v = end; v != -1; v = parent[v])
		path.push_back(v);
	reverse(path.begin(), path.end());

	
	return path;
}

// BellmanFord's algorithm 
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> edges; // Mỗi phần tử: {u, v, weight}

	// Tạo danh sách cạnh từ ma trận kề có trọng số
	for (int u = 0; u < n; ++u) {
		for (int v = 0; v < n; ++v) {
			if (adjMatrix[u][v] != 0) {
				edges.push_back({ u, v, adjMatrix[u][v] });
			}
		}
	}

	vector<int> dist(n, INT_MAX); // khởi tạo khoảng cách từ đỉnh start đén các đỉnh khác là vô cùng 
	vector<int> parent(n, -1); // cho biết đỉnh trước nối với đỉnh hiện tại 
	dist[start] = 0;

	// Lặp n-1 lần
	for (int i = 0; i < n - 1; ++i) {
		for (const auto& edge : edges) {
			int u = edge[0], v = edge[1], w = edge[2];
			if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				parent[v] = u;
			}
		}
	}

	// Kiểm tra chu trình âm
	for (const auto& edge : edges) {
		int u = edge[0], v = edge[1], w = edge[2];
		if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
			cout << "Do thi co chu trinh am !!!" << endl;
			return {};
		}
	}

	// Truy vết đường đi từ end về start
	if (dist[end] == INT_MAX) return {}; // Không có đường đi

	vector<int> path;
	for (int v = end; v != -1; v = parent[v])
		path.push_back(v);
	reverse(path.begin(), path.end());
	return path;
}

