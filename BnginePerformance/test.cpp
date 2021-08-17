#include "lib/hayai/src/hayai.hpp"
#include "../Bngine/include/util/math/Mat.h"

using namespace Mat;

class MatFixture : public ::hayai::Fixture
{
public:
    virtual void SetUp()
    {
        this->v2a = V2f(10, 20);
        this->v2b = V2f(25.131, -35.293);
        this->v3a = V3f(123,23.230, -2.32);
        this->v3b = V3f(34,-39,40.40321);
        this->v4a = V4f(3932, 3239, 3, 1);
        this->v4b = V4f(39, 31, 220, 1);
        this->m22a = M22f({ {1.5f, 3.5f}, {5.5f, 7.5f} });
        this->m22b = M22f({ {5.785f, -15.3f}, {5.5f, 12.36f} });
        this->m33a = M33f({ {1.5f, -0.5f, 56.3f}, {8.5f, 1.2f, -15.8f}, {8.7f, 9.2f, 0.5f} });
        this->m33b = M33f({ {12.5f, 3.0f, 0.5f}, {4.56342f, 4.325f, 3.32f}, {1.5f, 2.5f, 6.435f} });
        this->m44a = M44f({ {0.5f, 0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f, 0.5f} });
        this->m44b = M44f({ {-1.1f, 1.1f, 3.3f, 1.1f}, {12.12f, 0.897f, 356.5f, 1.5f}, {1337.68f, 420.69f, 12.12f, 113.112f}, {153.7f, 156.5f, 8.5f, -0.5f} });
        this->m23a = M23f({ 123.5f, 43.3f, 32.232f, 12.32f, 87.6f, 5.4f });
        this->m23b = M23f({ 5.344f, 2.34f, 1.5325f, 4.53f, 0.25f, 23.53f });
        this->m34a = M34f({ 43.3f, 342.21f, 33.5f, 4.6f, 2.1f, 3.0f, 35.3f, -322.3f, 324.12f, 4.32f, -230.0f, 123.3f });
        this->m34b = M34f({ 2.3545f, 1.0f, 0.5f, 34.35f, 9.32185f, 8.45f, 867.655f, 235.25f, 6.77f, 5.5f, 4.5f, 3.5f });
    }
    virtual void TearDown()
    {

    }
    V2f v2a, v2b;
    V3f v3a, v3b;
    V4f v4a, v4b;
    M22f m22a, m22b;
    M33f m33a, m33b;
    M44f m44a, m44b;
    M23f m23a, m23b;
    M34f m34a, m34b;
};

// -------------------------
// V2f

BENCHMARK_F(MatFixture, V2faddition, 20, 500)
{
    v2a + v2b;
}

BENCHMARK_F(MatFixture, V2fsubtraction, 20, 500)
{
    v2a - v2b;
}

BENCHMARK_F(MatFixture, V2fscalar, 20, 500)
{
    v2a * 3.51;
}

BENCHMARK_F(MatFixture, V2fequal, 20, 500)
{
    v2a == v2b;
}

BENCHMARK_F(MatFixture, V2fdot, 20, 500)
{
    v2a.dot(v2b);
}

BENCHMARK_F(MatFixture, V2fnorm, 20, 500)
{
    v2a.norm();
}

BENCHMARK_F(MatFixture, V2fnormalized, 20, 500)
{
    v2a.normalized();
}

// -------------------------
// V3f

BENCHMARK_F(MatFixture, V3faddition, 20, 500)
{
    v3a + v3b;
}

BENCHMARK_F(MatFixture, V3fsubtraction, 20, 500)
{
    v3a - v3b;
}

BENCHMARK_F(MatFixture, V3fscalar, 20, 500)
{
    v3a * 3.51;
}

BENCHMARK_F(MatFixture, V3fequal, 20, 500)
{
    v3a == v3b;
}

BENCHMARK_F(MatFixture, V3fdot, 20, 500)
{
    v3a.dot(v3b);
}

BENCHMARK_F(MatFixture, V3fcross, 20, 500)
{
    v3a.cross(v3b);
}

BENCHMARK_F(MatFixture, V3fnorm, 20, 500)
{
    v3a.norm();
}

BENCHMARK_F(MatFixture, V3fnormalized, 20, 500)
{
    v3a.normalized();
}

// -------------------------
// V4f

BENCHMARK_F(MatFixture, V4faddition, 20, 500)
{
    v4a + v4b;
}

BENCHMARK_F(MatFixture, V4fsubtraction, 20, 500)
{
    v4a - v4b;
}

BENCHMARK_F(MatFixture, V4fscalar, 20, 500)
{
    v4a * 3.51;
}

BENCHMARK_F(MatFixture, V4fequal, 20, 500)
{
    v4a == v4b;
}

BENCHMARK_F(MatFixture, V4fdot, 20, 500)
{
    v4a.dot(v4b);
}

BENCHMARK_F(MatFixture, V4fcross, 20, 500)
{
    v4a.cross(v4b);
}

BENCHMARK_F(MatFixture, V4fnorm, 20, 500)
{
    v4a.norm();
}

BENCHMARK_F(MatFixture, V4fnormalized, 20, 500)
{
    v4a.normalized();
}

// -------------------------
// M22f

BENCHMARK_F(MatFixture, M22faddition, 20, 500)
{
    m22a + m22b;
}

BENCHMARK_F(MatFixture, M22fsubtraction, 20, 500)
{
    m22a - m22b;
}

BENCHMARK_F(MatFixture, M22fscalar, 20, 500)
{
    m22a * 3.51;
}

BENCHMARK_F(MatFixture, M22fvector, 20, 500)
{
    m22a * v2a;
}

BENCHMARK_F(MatFixture, M22fmatrix, 20, 500)
{
    m22a* m22b;
}

BENCHMARK_F(MatFixture, M22ftrace, 20, 500)
{
    m22a.trace();
}

BENCHMARK_F(MatFixture, M22fdet, 20, 500)
{
    m22a.det();
}

BENCHMARK_F(MatFixture, M22ft, 20, 500)
{
    m22a.t();
}

// -------------------------
// M33f

BENCHMARK_F(MatFixture, M33faddition, 20, 500)
{
    m33a + m33b;
}

BENCHMARK_F(MatFixture, M33fsubtraction, 20, 500)
{
    m33a - m33b;
}

BENCHMARK_F(MatFixture, M33fscalar, 20, 500)
{
    m33a * 3.51;
}

BENCHMARK_F(MatFixture, M33fvector, 20, 500)
{
    m33a* v3a;
}

BENCHMARK_F(MatFixture, M33fmatrix, 20, 500)
{
    m33a* m33b;
}

BENCHMARK_F(MatFixture, M33ftrace, 20, 500)
{
    m33a.trace();
}

BENCHMARK_F(MatFixture, M33fdet, 20, 500)
{
    m33a.det();
}

BENCHMARK_F(MatFixture, M33ft, 20, 500)
{
    m33a.t();
}

// -------------------------
// M44f

BENCHMARK_F(MatFixture, M44faddition, 20, 500)
{
    m44a + m44b;
}

BENCHMARK_F(MatFixture, M44fsubtraction, 20, 500)
{
    m44a - m44b;
}

BENCHMARK_F(MatFixture, M44fscalar, 20, 500)
{
    m44a * 3.51;
}

BENCHMARK_F(MatFixture, M44fvector, 20, 500)
{
    m44a* v4a;
}

BENCHMARK_F(MatFixture, M44fmatrix, 20, 500)
{
    m44a* m44b;
}

BENCHMARK_F(MatFixture, M44ftrace, 20, 500)
{
    m44a.trace();
}

BENCHMARK_F(MatFixture, M44fdet, 20, 500)
{
    m44a.det();
}

BENCHMARK_F(MatFixture, M44ft, 20, 500)
{
    m44a.t();
}

// -------------------------
// M23f

BENCHMARK_F(MatFixture, M23faddition, 20, 500)
{
    m23a + m23b;
}

BENCHMARK_F(MatFixture, M23fsubtraction, 20, 500)
{
    m23a - m23b;
}

BENCHMARK_F(MatFixture, M23fscalar, 20, 500)
{
    m23a * 3.51;
}

BENCHMARK_F(MatFixture, M23fvector, 20, 500)
{
    m23a* v3a;
}

// -------------------------
// M34f

BENCHMARK_F(MatFixture, M34faddition, 20, 500)
{
    m34a + m34b;
}

BENCHMARK_F(MatFixture, M34fsubtraction, 20, 500)
{
    m34a - m34b;
}

BENCHMARK_F(MatFixture, M34fscalar, 20, 500)
{
    m34a * 3.51;
}

BENCHMARK_F(MatFixture, M34fvector, 20, 500)
{
    m34a* v4a;
}

int main()
{
    hayai::ConsoleOutputter consoleOutputter;

    hayai::Benchmarker::AddOutputter(consoleOutputter);
    hayai::Benchmarker::RunAllTests();
    return 0;
}