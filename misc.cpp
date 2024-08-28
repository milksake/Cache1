#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

void printMat(const vvi& A)
{
    for (auto& v : A)
    {
        for (auto e : v)
        {
            cout << e << ' ';
        }
        cout << '\n';
    }
}

void createRandMat(vvi& A, int lim)
{
    for (auto& v : A)
    {
        for (auto& e : v)
        {
            e = rand() % lim;
        }
    }
}

void createRandMat(vi& A, int lim)
{
    for (auto& v : A)
    {
        v = rand() % lim;
    }
}

bool equalMat(const vi& A, const vi& B)
{
    bool ans = true;
    for (int i = 0; i < A.size(); i++)
    {
        ans = ans && A[i] == B[i];
    }
    return ans;
}

void matElementOp(const vvi& A, const vvi& B, vvi& C, int(*op)(int, int) = [](int x, int y) { return x + y; })
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < B[0].size(); j++)
        {
            C[i][j] = op(A[i][j], B[i][j]);
        }
    }
}

void matQuadElementOp(const vvi& A, int qa, const vvi& B, int qb, vvi& C, int(*op)(int, int) = [](int x, int y) { return x + y; })
{
    int k = B.size() / 2;
    int offax = ((bool)(qa & 1)) * k;
    int offbx = ((bool)(qb & 1)) * k;
    int offay = ((bool)(qa & 2)) * k;
    int offby = ((bool)(qb & 2)) * k;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] = op(A[offay + i][offax + j], B[offby + i][offbx + j]);
        }
    }
}

void matMult(const vvi& A, const vvi& B, vvi& C)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < B[0].size(); j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < B.size(); k++)
            {
                C[i][j] = (C[i][j] + ((A[i][k]) * (B[k][j])));
            }
        }
    }
}

void matMult(const vi& A, const vi& B, vi& C, int l, int m, int n)
{
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i * n + j] = 0;
            for (int k = 0; k < m; k++)
            {
                C[i * n + j] = (C[i * n + j] + ((A[i * m + k]) * (B[k * n + j])));
            }
        }
    }
}

int subs(int x, int y)
{
    return x - y;
}

void strassenMatMult(const vvi& A, const vvi& B, vvi& C)
{
	if (B.size() == 1)
    {
		matMult(A, B, C);
        return;
	}

	int k = B.size() / 2;

	vvi A11(k, vi(k));
	// vvi A12(k, vi(k));
	// vvi A21(k, vi(k));
	vvi A22(k, vi(k));
	vvi B11(k, vi(k));
	// vvi B12(k, vi(k));
	// vvi B21(k, vi(k));
	vvi B22(k, vi(k));


	for (unsigned int i = 0; i < k; i++)
    {
		for (unsigned j = 0; j < k; j++)
        {
			A11[i][j] = A[i][j];
			// A12[i][j] = A[i][k + j];
			// A21[i][j] = A[k + i][j];
			A22[i][j] = A[k + i][k + j];
			B11[i][j] = B[i][j];
			// B12[i][j] = B[i][k + j];
			// B21[i][j] = B[k + i][j];
			B22[i][j] = B[k + i][k + j];
		}
	}

    vvi P1(k, vi(k));
    vvi P2(k, vi(k));
    vvi P3(k, vi(k));
    vvi P4(k, vi(k));
    vvi P5(k, vi(k));
    vvi P6(k, vi(k));
    vvi P7(k, vi(k));

    vvi S1(k, vi(k));
    vvi S2(k, vi(k));

	matQuadElementOp(B, 1, B, 3, S1, subs);
	strassenMatMult(A11, S1, P1);

	matQuadElementOp(A, 0, A, 1, S1);
	strassenMatMult(S1, B22, P2);

	matQuadElementOp(A, 2, A, 3, S1);
	strassenMatMult(S1, B11, P3);

	matQuadElementOp(B, 2, B, 0, S1, subs);
	strassenMatMult(A22, S1, P4);

	matQuadElementOp(A, 0, A, 3, S1);
	matQuadElementOp(B, 0, B, 3, S2);
	strassenMatMult(S1, S2, P5);
    
	matQuadElementOp(A, 1, A, 3, S1, subs);
	matQuadElementOp(B, 2, B, 3, S2);
	strassenMatMult(S1, S2, P6);

	matQuadElementOp(A, 0, A, 2, S1, subs);
	matQuadElementOp(B, 0, B, 1, S2);
	strassenMatMult(S1, S2, P7);

	vvi C11(k, vi(k)); matElementOp(P5, P4, C11); matElementOp(C11, P2, C11, subs); matElementOp(C11, P6, C11);				// P5 + P4 - P2 + P6
	vvi C12(k, vi(k)); matElementOp(P1, P2, C12);								// P1 + P2
	vvi C21(k, vi(k)); matElementOp(P3, P4, C21);								// P3 + P4
	vvi C22(k, vi(k)); matElementOp(P1, P5, C22); matElementOp(C22, P3, C22, subs); matElementOp(C22, P7, C22, subs);				// P1 + P5 - P3 - P7

	for (unsigned int i = 0; i < k; i++)
    {
		for (unsigned int j = 0; j < k; j++)
        {

			C[i][j] = C11[i][j];
			C[i][j + k] = C12[i][j];
			C[k + i][j] = C21[i][j];
			C[k + i][k + j] = C22[i][j];
		}
	}
}

void matMultBlocks(const vi& A, const vi& B, vi& C, int l, int m, int n, int s)
{
    for (int ii = 0; ii < l; ii += s)
    {
        for (int jj = 0; jj < n; jj += s)
        {
            for (int kk = 0; kk < m; kk += s)
            {
                int ie = ii + s;
                if (ie > l)
                    ie = l;
                int je = jj + s;
                if (je > n)
                    je = n;
                int ke = kk + s;
                if (ke > m)
                    ke = m;
                for (int i = ii; i < ie; ++i)
                {
                    for (int j = jj; j < je; ++j)
                    {
                        int sum = 0;
                        for (int k = kk; k < ke; ++k) {
                            sum += *(&A[0] + i * m + k) * *(&B[0] + k * n + j);
                        }
                        *(&C[0] + i * n + j) += sum;
                    }
                }
            }
        }
    }
}

int main()
{
    cout << "i\tn\tEq?\tT1\tT2\tDiff\n";

    for (int i = 1, n = 50; i <= 20; i++, n += 50)
    {        
        vi A(n * n); createRandMat(A, 10);
        vi B(n * n); createRandMat(B, 10);

        vi C1(n * n);
        vi C2(n * n);

        auto beg = chrono::high_resolution_clock::now();
        matMult(A, B, C1, n, n, n);
        auto end = chrono::high_resolution_clock::now();
        auto t1 = chrono::duration_cast<chrono::microseconds>(end - beg);
        
        beg = chrono::high_resolution_clock::now();
        matMultBlocks(A, B, C2, n, n, n, 25);
        end = chrono::high_resolution_clock::now();
        auto t2 = chrono::duration_cast<chrono::microseconds>(end - beg);

        if (equalMat(C1, C2))
        {
            cout << i << '\t' << n << "\tY\t" << t1.count() << '\t' << t2.count() << '\t' << t2.count() - t1.count() << '\n';
        }
        else
        {
            cout << i << '\t' << n << "\tN\t-\t-\t-\n";
        }
    }
}