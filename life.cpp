#include <iostream>
#include <array>
#include <random>
#include <ostream>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#define WIDTH 8
#define HEIGHT 8

namespace Color
{
    enum Code
    {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };

    class Modifier
    {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream& operator<<(std::ostream& os, const Modifier& mod)
        {
            return os << "\033[" << mod.code << "m";
        }
    };
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
static void Print(const std::array<std::array<bool, WIDTH>, HEIGHT> &cells)
{
    Color::Modifier green(Color::BG_GREEN);
    Color::Modifier def(Color::BG_DEFAULT);

    for ( auto ii = 0u; ii < HEIGHT; ++ii )
    {
        for ( auto jj = 0u; jj < WIDTH; ++jj )
        {
            if ( cells[ii][jj] )
                std::cout << green << "  ";
            else
                std::cout << def << "  ";
        }
        std::cout << def << "\n";
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int main()
{
    std::array<std::array<bool, WIDTH>, HEIGHT> cells;

    // seed
    for ( auto ii = 0u; ii < HEIGHT; ++ii )
    {
        srand(clock());
        for ( auto jj = 0u; jj < WIDTH; ++jj )
        {
            cells[ii][jj] = (rand() % 2 == 0);
        }
    }

    auto temp = cells;

    auto probeNeighbours = [&temp](int x, int y, int &numAlive, int& numDead)
    {
        for (auto ii = -1; ii <= 1; ii += 2 )
        {
            auto r = x + ii;
            if ( r < 0 || r >= HEIGHT )
                continue;
            for (auto jj = -1; jj <= 1; jj += 2 )
            {
                auto c = y + jj;
                if ( c < 0 || c >= WIDTH )
                    continue;

                if ( temp[r][c] )
                    ++numAlive;
                else
                    ++numDead;
            }
        }
    };

    Print(cells);
    std::cout << "\n";

    auto numGens = 5u;
    for ( auto gen = 0u; gen < numGens; ++gen )
    {
        temp = cells;
        for ( auto ii = 0u; ii < HEIGHT; ++ii )
        {
            for ( auto jj = 0u; jj < WIDTH; ++jj )
            {
                int numAlive = 0;
                int numDead = 0;
                probeNeighbours(ii, jj, numAlive, numDead);
                if ( temp[ii][jj] && (numAlive == 2 || numAlive == 3) )
                {
                    cells[ii][jj] = true;
                }
                else if ( !temp[ii][jj] && numAlive == 3 )
                {
                    cells[ii][jj] = true;
                }
                else
                {
                    cells[ii][jj] = false;
                }
            }
        }

        Print(cells);
        std::cout << "\n";
    }

    return 0u;
}
