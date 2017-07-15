#include <iostream>
#include <cstring>
#include <stack>
#include <climits>
#include <algorithm>

constexpr int NUM = 16;
int dp[1 << NUM];
int cost[NUM][NUM + 1];//[�X�e�[�W][����] = �v���R�X�g

int main() {
	int n;
	while (std::cin >> n && n) {
		std::memset(dp, 0, sizeof(dp));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n + 1; j++) {
				std::cin >> cost[i][j];
			}
		}

		int min = INT_MAX;
		std::stack<std::pair<int, int>> s; //first:�N���A�ς݃X�e�[�W second:�R�X�g
		s.push(std::make_pair(0, 0));
		while (!s.empty()) {
			auto node = s.top(); s.pop();
			for (int i = 0; i < n; i++) { //�X�e�[�W�I��
				if ((node.first >> i) & 1) continue; //�U���ς�
				for (int j = 0; j < n + 1; j++) { //����I��
					//���킪�Ȃ�
					if (j && !((node.first >> (j - 1)) & 1)) continue;

					auto next = node;
					next.second += cost[i][j];
					next.first |= 1 << i;

					if (dp[next.first] && dp[next.first] <= next.second) continue;
					dp[next.first] = next.second;

					s.push(next);

					if (next.first == (1 << n) - 1) {
						min = std::min(min, next.second);
					}
				}
			}
		}
		std::cout << min << std::endl;
	}

	return 0;
}