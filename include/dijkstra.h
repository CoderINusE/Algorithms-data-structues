#ifndef __DIJKSTRA__
#define __DIJKSTRA__

#include <inc_libs.h>

namespace alg {
	template <typename T>
	class DJpath {
		public:
			static vi<T> run(const vii<T> & g, const T init) {
				int n = g.size();

				vi<T> d(n, PINF<int>);
				//p(n);
				d[ init ] = 0;
				std::vector<char> u(n);

				for(int i = 0; i < n; ++i) {
					int v = -1;
					for(size_t j = 0; j < n; ++j) {
						if(!u[j] && (v == -1 || d[j] < d[v]))
							v = j;
						if(d[v] == PINF<int>) break;
						u[v] = true;

						for(size_t j = 0; j < g[v].size(); ++j) {
							int to = g[v][j].first,
							len = g[v][i].second;

							if(d[v] + len < d[to]) {
								d[to] = d[v] + len;
								//p[to] = v;
							}

						}
					}
				}

				return d;

			}
	};


}

#endif