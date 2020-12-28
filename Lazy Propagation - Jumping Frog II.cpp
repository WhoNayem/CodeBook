#include <bits/stdc++.h>
using namespace std;
#define __Mammamia__                ios_base :: sync_with_stdio(false);
#define ll                          long long
#define MAXN                        100007

int vec[MAXN], lazy[MAXN << 2], tree[MAXN << 2];

void propagate(int node)
{
    int left = node << 1, right = left | 1;
    lazy[left] += lazy[node];
    lazy[right] += lazy[node];
    lazy[node] = 0;
}

void update(int node, int b, int e, int i, int j, int val)
{
    if(b > j || e < i) return;
    if(b >= i && e <= j) {lazy[node] += val;return;}

    propagate(node);
    int mid = (b + e) >> 1, left = node << 1, right = left | 1;

    update(left, b, mid, i, j, val);
    update(right, mid + 1, e, i, j, val);

    tree[node] = min(tree[left] + lazy[left], tree[right] + lazy[right]);
}

int query(int node, int b, int e, int i, int j)
{
    if(b > j || e < i) return 5;
    if(b >= i && e <= j) return tree[node] + lazy[node];

    propagate(node);
    int mid = (b + e) >> 1, left = node << 1, right = left | 1;

    int q1 = query(left, b, mid, i, j);
    int q2=query(right, mid + 1, e, i, j);

    tree[node] = min(tree[left] + lazy[left], tree[right] + lazy[right]);
    return min(q1, q2);
}

int main()
{
    __Mammamia__

    int test_case, case_no = 0; cin >> test_case;
    while(test_case--)
    {
        memset(lazy,0,sizeof lazy);
        memset(tree,0,sizeof tree);

        int n, q; cin >> n >> q;
        for(int i = 1; i <= n; ++i)
        {
            cin >> vec[i];
            update(1, 1, n + 1, i + 1, min(n + 1, i + vec[i]), 1);
        }

        cout << "Case " << ++case_no << ":" << endl;
        while(q--)
        {
            int type; cin >> type;
            if(type == 1)
            {
                int p, s; cin >> p >> s;
                update(1, 1, n + 1, p + 1, min(n + 1, p + vec[p]), -1);
                vec[p] = s;
                update(1, 1, n + 1, p + 1, min(n + 1, p + vec[p]), 1);
            }
            else
            {
                int s; cin >> s;
                if(s >= n + 1) cout<<"yes" << endl;
                else if(query(1, 1, n + 1, s + 1, n + 1) == 0)cout<<"no" << endl;
                else cout << "yes" << endl;
            }
        }
    }
    return 0;
}
