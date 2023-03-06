
#include "pokedex.h"
#include <iostream>
#include <string>
using namespace std;

ostream &operator<<(ostream &out, const Pokedex &pdx)
{
    out << "[";
    if (!pdx.empty())
    {
        out << pdx.at(0);
    }
    for (int i = 1; i < pdx.size(); ++i)
    {
        out << ", " << pdx.at(i);
    }
    out << "]";
    return out;
}

Pokedex::Pokedex()
{
}

int Pokedex::size() const
{ // returns the size of pokemons, basically just returning msize
    return msize;
}

int Pokedex::max_size()
{ // returns the max size of pokemons which is initialized in .h file
    return MAX;
}

bool Pokedex::empty() const
{ // this function checks if the array is empty or not. If the size of pokemons is 0 then pokemons is empty otherwise not
    if (msize == 0)
    {
        return true;
    }
    return false;
}

const string &Pokedex::at(int n) const
{ // this function returns the element at index n
    if (n >= 0 && n < msize)
    {
        return pokemons[n];
    }
    else
    {
        return "";
    }
}

const string &Pokedex::front() const
{ // returns the first element of pokemons
    return pokemons[0];
}

const string &Pokedex::back() const
{ // returns last element of pokemons
    return pokemons[msize - 1];
}

void Pokedex::insert(const string &pokemon)
{ // inserts the pokemon and keep pokemons sorted. If pokemons is full, it returns.
    string new_pokemon = pokemon;
    if (msize != MAX)
    {
        for (int i = 0; i <= msize; i++)
        {
            if (new_pokemon <= pokemons[i])
            {
                for (int j = msize; j > i; j--)
                {
                    pokemons[j] = pokemons[j - 1];
                }
                pokemons[i] = new_pokemon;
                msize++;
                return;
            }
            else if (i == msize)
            {
                pokemons[i] = new_pokemon;
                msize++;
                return;
            }
        }
    }
    else
    {
        return;
    }
}

void Pokedex::pop_back()
{ // removes the last element and reduces the size of pokemons by 1
    pokemons[msize - 1] = "";
    msize--;
}

void Pokedex::erase(int n)
{ // erases the element on n^th index, shifts the remaining elements, and reduces the size of pokemons by 1
    for (int i = 0; i < msize; i++)
    {
        if (pokemons[i] == pokemons[n])
        {
            pokemons[n] = "";
            pokemons[i] = pokemons[i + 1];
        }
    }
    msize--;
}